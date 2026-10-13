// Example test for the Simple ORM project.
// Build it against your submission.zip with the CMake setup in README.md.
// Run it in an empty directory: it deletes and recreates the json files it uses.

#include "simple_orm.hpp"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

static int failures = 0;

#define CHECK(cond)                                                       \
    do {                                                                  \
        if (!(cond)) {                                                    \
            std::cerr << __FILE__ << ':' << __LINE__ << ": CHECK failed: " \
                      << #cond << '\n';                                   \
            ++failures;                                                   \
        }                                                                 \
    } while (0)

static std::vector<std::string> read_lines(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<std::string> lines;
    for (std::string line; std::getline(in, line);) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

struct Student : public DBTableType {
    StringType student_id_{"student_id"};
    StringType student_name_{"student_name"};

    Student() : DBTableType(PrimaryKey(&student_id_), &student_name_) {}
    constexpr static std::string_view name() {
        return "Student";
    }
};

struct Classroom : public DBTableType {
    StringType room_number_{"room_number"};
    StringType building_{"building"};
    IntType capacity_{"capacity"};

    Classroom() : DBTableType(PrimaryKey(&room_number_), &building_, &capacity_) {}
    constexpr static std::string_view name() {
        return "Classroom";
    }
};

struct Class : public DBTableType {
    IntType id_ = DBManager<Class>::get_next_key("id");
    StringType class_name_{"class_name"};
    ForeignKey<Classroom> classroom_{"classroom"};
    ForeignKeyVector<Student> students_{"students"};

    Class() : DBTableType(PrimaryKey(&id_), &class_name_, &classroom_, &students_) {}
    constexpr static std::string_view name() {
        return "Class";
    }
};

struct Exam : public DBTableType {
    IntType id_ = DBManager<Exam>::get_next_key("id");
    FloatType score_{"score"};
    DateType date_{"date"};

    Exam() : DBTableType(PrimaryKey(&id_), &score_, &date_) {}
    constexpr static std::string_view name() {
        return "Exam";
    }
};

static Student* add_student(const std::string& id, const std::string& name) {
    Student* student = DBManager<Student>::create();
    student->student_id_ = id;
    student->student_name_ = name;
    student->save();
    return student;
}

int main() {
    for (const char* file : {"Student.json", "Classroom.json", "Class.json", "Exam.json"}) {
        std::filesystem::remove(file);
    }

    // Creating, saving and the JSON format
    Student* kim = add_student("2028140080", "Kim Hajun");
    add_student("2028140081", "Yun Jia");
    add_student("2028140082", "Go Yuri");
    Student* hong = add_student("2028140083", "Hong gil-dong");
    add_student("2028140084", "Say \"hi\"\n홍길동");

    std::vector<std::string> lines = read_lines("Student.json");
    CHECK(lines.size() == 5);
    CHECK(lines[0] == R"({"student_id": "2028140080", "student_name": "Kim Hajun"})");
    CHECK(lines[4] == R"({"student_id": "2028140084", "student_name": "Say \"hi\"\n홍길동"})");

    // Search by key
    CHECK(DBManager<Student>::search("2028140083") == hong);
    CHECK(DBManager<Student>::search("2028140083") == DBManager<Student>::search("2028140083"));
    CHECK(DBManager<Student>::search("0000000000") == nullptr);
    CHECK(hong->student_name_.get() == "Hong gil-dong");

    // Changing a saved object replaces its line
    hong->student_name_ = "Hong Gildong";
    hong->save();
    hong->save();
    lines = read_lines("Student.json");
    CHECK(lines.size() == 5);
    CHECK(lines[3] == R"({"student_id": "2028140083", "student_name": "Hong Gildong"})");

    // Saving a different object with an existing key throws
    Student* duplicate = DBManager<Student>::create();
    duplicate->student_id_ = "2028140080";
    duplicate->student_name_ = "Someone Else";
    bool thrown = false;
    try {
        duplicate->save();
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    CHECK(thrown);
    CHECK(read_lines("Student.json").size() == 5);
    duplicate->student_id_ = "2028140085";
    duplicate->save();

    // Foreign keys
    Classroom* classroom = DBManager<Classroom>::create();
    classroom->room_number_ = "B039";
    classroom->building_ = "Engineering Hall";
    classroom->capacity_ = 120;
    classroom->save();

    Class* cls = DBManager<Class>::create();
    CHECK(cls->id_.get() == 1);
    cls->class_name_ = "OOP and DS";
    cls->classroom_ = classroom;
    cls->students_.push_back(hong);
    cls->students_.push_back(kim);
    cls->save();

    Class* empty_cls = DBManager<Class>::create();
    CHECK(empty_cls->id_.get() == 2);
    empty_cls->class_name_ = "Empty";
    empty_cls->save();

    lines = read_lines("Class.json");
    CHECK(lines.size() == 2);
    CHECK(lines[0] == R"({"id": 1, "class_name": "OOP and DS", "classroom": "B039", "students": ["2028140083", "2028140080"]})");
    CHECK(lines[1] == R"({"id": 2, "class_name": "Empty", "classroom": null, "students": []})");

    CHECK(DBManager<Class>::search(1) == cls);
    CHECK(DBManager<Class>::search(3) == nullptr);
    std::vector<Student*> students = cls->students_.get();
    CHECK(students.size() == 2 &&students[0] == hong && students[1] == kim);
    CHECK(cls->classroom_.get() == classroom);
    CHECK(empty_cls->classroom_.get() == nullptr);
    CHECK(empty_cls->students_.get().empty());

    // A failed search must not use up a key
    Class* next_cls = DBManager<Class>::create();
    CHECK(next_cls->id_.get() == 3);

    // FloatType and DateType
    using namespace std::chrono;
    Exam* exam = DBManager<Exam>::create();
    exam->score_ = 0.1;
    exam->date_ = 2026y / October / 13;
    exam->save();
    lines = read_lines("Exam.json");
    CHECK(lines.size() == 1);
    CHECK(lines[0] == R"({"id": 1, "score": 0.1, "date": "2026-10-13"})");

    // Advanced search and order
    Result<Student> found =
        DBManager<Student>::search("student_name", AND(GREATER_THAN_OR_EQUAL_TO("Go Yuri"), LESS_THAN_OR_EQUAL_TO("Huh June")))
            .order_by("student_id", Ordering::Descending);
    std::vector<std::string> ids;
    for (Student* student : found) {
        ids.push_back(student->student_id_.get());
    }
    CHECK((ids == std::vector<std::string>{"2028140083", "2028140082"}));

    CHECK(DBManager<Student>::search("student_name", EQUAL_TO("Yun Jia")).size() == 1);
    CHECK(DBManager<Student>::search("student_name", NOT(EQUAL_TO("Yun Jia"))).size() == 5);
    CHECK(DBManager<Student>::search("student_name", OR(EQUAL_TO("Yun Jia"), EQUAL_TO("Go Yuri"))).size() == 2);
    CHECK(DBManager<Student>::search("student_name", GREATER_THAN("zzz")).size() == 0);
    CHECK(DBManager<Classroom>::search("capacity", LESS_THAN(121)).size() == 1);

    if (failures == 0) {
        std::cout << "All checks passed\n";
    }
    return failures == 0 ? 0 : 1;
}

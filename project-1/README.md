# Simple ORM

In this project, you are asked to implement a simple ORM where data is saved in `json` format.

You are allowed to use AI models (e.g., ChatGPT, Claude, Gemini, GitHub Copilot) for this project. However, you are responsible for everything you submit.

## Requirements

### `DBManager<T>` class
You are asked to design a `DBManager<T>` class that has the following member functions.
```cpp
template<typename T>
class DBManager {
public:
    // ...
    static void save(); // saves every T object in memory to the json file
    static void load(); // loads every object in the json file into memory
};
```
The `json` file is named `T::name()` followed by `.json` (e.g., if `T::name()` is `Student`, it is `Student.json`).

The `json` file stores one object per line. For example, `Student.json` can be
```
{"student_id": "2028140080", "student_name": "Kim Hajun"}
{"student_id": "2028140081", "student_name": "Yun Jia"}
{"student_id": "2028140082", "student_name": "Minami Sang"}
```

Saving and loading work as follows:
- `obj->save()` saves one object, and `DBManager<T>::save()` saves every `T` object in memory.
- Saving writes the object's current values. If the object is not in the file yet, its line is appended. If it is, its line is replaced, so the file always has exactly one line per key. Saving an object that has not changed since it was last saved leaves the file unchanged.
- If a *different* object of the same table already has the same key, in memory or in the file, saving throws `std::invalid_argument` and leaves the file unchanged.
- `DBManager<T>::load()` loads every object in the file into memory. An object that is already in memory is kept as it is (same pointer, in-memory values). Calling `load()` is optional: `search` reads the file by itself when it needs to.
- Nothing is saved automatically. Objects that are not saved before the program ends are lost.


### Users should be able to define a new DB table

```cpp
struct Student : public DBTableType {
    StringType student_id_{"student_id"};
    StringType student_name_{"student_name"};

    Student() : DBTableType(PrimaryKey(&student_id_), &student_name_) {}
    constexpr static std::string_view name() {
        return "Student";
    }
};

int main() {
    // ...
    Student* student = DBManager<Student>::create();
    student->student_id_ = "2028140083";
    student->student_name_ = "Hong gil-dong";
    student->save(); // appends {"student_id": "2028140083", "student_name": "Hong gil-dong"} to "Student.json" file
    // ...
}
```

Objects of a table can only be created through `DBManager<T>::create()` (or loaded through `DBManager<T>::search()`). Creating them in any other way must not compile:

```cpp
Student student;              // compile error
Student* p = new Student();   // compile error
```

### Supported fields
The following fields should be supported:

* IntType (for `std::int64_t`)
* FloatType (for `double`)
* StringType (for `std::string`)
* DateType (for `std::chrono::year_month_day`)

Also, the following foreign key types should be supported:

* ForeignKey<T> (for a single T)
* ForeignKeyVector<T> (for multiple T)

Each of `IntType`, `FloatType`, `StringType` and `DateType` holds one value and supports:
- assignment from its value type (`student->student_name_ = "Hong gil-dong";`, `classroom->capacity_ = 120;`),
- `get()`, which returns the value (`std::int64_t`, `double`, `const std::string&` or `std::chrono::year_month_day`),
- `operator<<` to a `std::ostream`, which prints the value (a `DateType` prints as `YYYY-MM-DD`).

```cpp
if (student->student_name_.get() == "Hong gil-dong") { /* ... */ }
```

A field that has never been assigned holds `0`, `0.0`, `""` or `1970-01-01`.

The primary key must be an `IntType` or a `StringType`. The primary key of an object must not change after the object has been saved or loaded (this is not tested).

### JSON format
Each line is a JSON object of the form `{"name": value, "name": value}`:
- Fields appear in the order they are passed to the `DBTableType` constructor, so the primary key comes first.
- A name and its value are separated by `": "`, and fields by `", "`. There is no other whitespace.
- `IntType` is a JSON integer.
- `FloatType` is a JSON number, written as the shortest form that reads back to the same `double` (as `std::to_chars` does). NaN and infinities are not tested.
- `StringType` is a JSON string. `"`, `\` and control characters (e.g., a newline) are escaped, and non-ASCII text is written as is in UTF-8.
- `DateType` is a JSON string `"YYYY-MM-DD"`.
- `ForeignKey<T>` is the key of the referenced object, or `null`.
- `ForeignKeyVector<T>` is a JSON array of keys, with elements separated by `", "` (`[]` if empty).

The tests may write `T.json` files themselves before running your code. They always use this format.

### Retrieve an object using its key

```cpp
Student* student = DBManager<Student>::search("2028140083");
std::cout << student->student_name_ << '\n'; // prints "Hong gil-dong"
```

If there is no object with the given key, `search` returns `nullptr`.

`DBManager` owns every object returned by `create` and `search`, so you must not `delete` them; the pointers stay valid until the program ends.
If the object with the given key is already in memory, `search` returns that same object (even if it has not been saved yet) instead of loading a second copy from the file.

### Saving foreign fields

```cpp
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
```

`ForeignKey<T>` holds a reference to at most one object of table `T`, and `ForeignKeyVector<T>` holds references to any number of them. A `ForeignKey<T>` is assigned a `T*` (or `nullptr` to clear it), and `ForeignKeyVector<T>::push_back` only accepts a `T*`, so adding an object from a different table does not compile.

`DBManager<Class>::get_next_key("id")` returns an `IntType` named `"id"` whose value is one larger than the largest `id` saved in `Class.json` (or `1` if there is none), and each call returns a new value.

Then,

```cpp
auto* classroom = DBManager<Classroom>::create();
classroom->room_number_ = "B039";
classroom->building_ = "Engineering Hall";
classroom->capacity_ = 120;
classroom->save();

auto* student = DBManager<Student>::search("2028140083");
auto* cls = DBManager<Class>::create();
cls->class_name_ = "OOP and DS";
cls->classroom_ = classroom;
cls->students_.push_back(student);
cls->students_.push_back(DBManager<Student>::search("2028140080"));
cls->save();
```

saves the following line to `Class.json` (if classes with ids 1 to 3 are already saved):

```
{"id": 4, "class_name": "OOP and DS", "classroom": "B039", "students": ["2028140083", "2028140080"]}
```

Note that we only want to save the key of the classroom and of each student. A `ForeignKey<T>` is saved as a single key, or as `null` if it does not refer to any object; a `ForeignKeyVector<T>` is always saved as an array (`[]` if it is empty).

### Retrieving foreign fields

The saved keys do not say which table they belong to, but the field's type does, so `get()` needs no template argument:

```cpp
auto* cls = DBManager<Class>::search(4);
for (Student* student : cls->students_.get()) {
    std::cout << student->student_name_ << '\n'; // prints "Hong gil-dong", then "Kim Hajun"
}
```

`get()` returns a `std::vector<Student*>` in the order the keys were added, loading each student with `DBManager<Student>::search` if it is not already in memory. A key that is stored more than once appears that many times, and a key whose object is no longer in the referenced table is skipped.

Similarly, `ForeignKey<T>::get()` returns a `T*`, or `nullptr` if the field is `null` or its key is no longer in the referenced table:

```cpp
Classroom* classroom = cls->classroom_.get();
std::cout << classroom->building_ << '\n'; // prints "Engineering Hall"
```

Two tables may refer to each other. For example, `Student` could have a `ForeignKeyVector<Class>` field while `Class` has a `ForeignKeyVector<Student>` field:

```cpp
struct Class; // forward declaration

struct Student : public DBTableType {
    // ...
    ForeignKeyVector<Class> classes_{"classes"};
    // ...
};

struct Class : public DBTableType {
    // ...
    ForeignKeyVector<Student> students_{"students"};
    // ...
};
```

Here `Class` is still an incomplete type when `Student` is defined, so this must compile. In other words, declaring a `ForeignKey<T>` or `ForeignKeyVector<T>` member must not require `T` to be a complete type; `T` only needs to be complete where its member functions (`push_back`, `get`, `save`, ...) are used.

### Advanced search and order

The following should work.
```cpp
Result<Student> students = 
    DBManager<Student>::search("student_name", AND(GREATER_THAN_OR_EQUAL_TO("Go Yuri"), LESS_THAN_OR_EQUAL_TO("Huh June"))).
    order_by("student_id", Ordering::Descending);

for(Student* student: students) {
    std::cout << student->student_name_ << '\n';
}
```

`students` is a `Result<Student>`. It can be used in a range-based `for` loop and has `size()`. The following comparison and logical operators should be supported:
- `EQUAL_TO`
- `GREATER_THAN`
- `LESS_THAN`
- `GREATER_THAN_OR_EQUAL_TO`
- `LESS_THAN_OR_EQUAL_TO`
- `AND` (two conditions)
- `OR` (two conditions)
- `NOT` (one condition)

Searching works as follows:
- Comparisons are numeric for `IntType` and `FloatType`, byte-wise lexicographic for `StringType` (as `std::string`'s `<`), and chronological for `DateType`.
- The value in a comparison must match the field: a string for `StringType`, an integer for `IntType`, a number for `FloatType`, and a `std::chrono::year_month_day` for `DateType`.
- If the field name does not exist or the value does not match the field, `search` throws `std::invalid_argument`.
- Searching on `ForeignKey` or `ForeignKeyVector` fields is not required.
- The search covers every object in the file and every object in memory, including unsaved ones. An object in memory is matched using its in-memory values.
- The pointers in a `Result<T>` are the same objects that `DBManager<T>::search(key)` returns.

`order_by` is optional, and without it the order is unspecified. `Ordering::Descending` and `Ordering::Ascending` are its only two options. Objects with equal values are ordered by their primary key in ascending order. `order_by` is called at most once on a `Result<T>`.

## Submission
Submit a single `zip` file to LearnUs.

The `zip` file is used directly by the test code through CMake's `FetchContent`, without any modification:

```cmake
include(FetchContent)
FetchContent_Declare(
    simple_orm
    URL ${CMAKE_CURRENT_SOURCE_DIR}/submission.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(simple_orm)

add_executable(test_orm test_orm.cpp)
target_link_libraries(test_orm PRIVATE simple_orm)
```

So your `zip` file must satisfy the following:
- `CMakeLists.txt` is at the root of the `zip` file (or inside a single top-level directory).
- It defines a library target named exactly `simple_orm`, which requires C++20. The library can be header-only (`INTERFACE`) or have source files (`STATIC`).
- The test code includes your library with `#include "simple_orm.hpp"`, so `simple_orm.hpp` must be in the include directories of the `simple_orm` target.
- Your own `main` function, tests, or examples must not be built when the project is used through `FetchContent`. Build them only if `PROJECT_IS_TOP_LEVEL` is true.
- The project must build without network access, so do not fetch other dependencies.

> [!CAUTION]
> **If the test code fails to configure or compile with your `zip` file through CMake as described above, your score is 0, with no exceptions.** Before submitting, check that your `zip` file builds with the test setup above.

For example, a header-only submission can be structured as follows:

```
submission.zip
├── CMakeLists.txt
└── include/
    └── simple_orm.hpp
```

```cmake
cmake_minimum_required(VERSION 3.24)
project(simple_orm LANGUAGES CXX)

add_library(simple_orm INTERFACE)
target_include_directories(simple_orm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(simple_orm INTERFACE cxx_std_20)

if(PROJECT_IS_TOP_LEVEL)
    # your own tests or examples go here
endif()
```


## Evaluation
You are asked to cover all possible edge cases. Also, the speed of saving, loading, and searching will be taken into account. The tests use up to 100,000 objects per table.

Some examples of edge cases (this list is not exhaustive):
- `T.json` does not exist yet, or is empty.
- A string field contains special characters such as `"`, `\`, a newline, or non-ASCII text (e.g., `"홍길동"`).
- An `IntType` field holds a negative number or a large value (e.g., `-1`, `9223372036854775807`).
- `search` is called with a key that does not exist; it must return `nullptr`.
- `search` is called twice with the same key; both calls must return the same object.
- An object is created but not saved, and then searched by its key.
- The same object is saved more than once, or its fields are changed after it has been saved.
- `search` fails or loads an object; this must not use up a key from `get_next_key`.
- A `ForeignKey` does not refer to any object.
- A `ForeignKeyVector` is empty, or contains the same object more than once.
- A `ForeignKey` or `ForeignKeyVector` contains a key whose object is no longer in the referenced table.
- An advanced search matches no objects, or matches every object.

All `json` files should be valid. You can check their validity using `jq`.

### Example test
[`test_orm_example.cpp`](test_orm_example.cpp) shows how the tests use your library. The hidden tests use only the classes, functions and operators described in this README. Before submitting, build this file against your `zip` file with the CMake setup in [Submission](#submission) and make sure it passes.
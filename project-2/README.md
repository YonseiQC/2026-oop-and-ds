# Project 2: Mini Spreadsheet

In this project, you will implement a spreadsheet engine in C++20. A cell may contain a number or a formula referring to other cells. When a cell changes, the engine must update dependent results correctly and efficiently.

You are allowed to use AI models, including ChatGPT, Claude, Gemini, and GitHub Copilot. However, you are responsible for everything you submit. **Your submission must include tests.**

The main challenge is maintaining consistency as formulas are added, replaced, cleared, rejected, and evaluated. Implementing an expression evaluator alone is not sufficient.

## 1. Scope

Implement a reusable, in-memory C++ library. You do not need a graphical interface, file persistence, or compatibility with Excel or Google Sheets.

The required features are:

- Numeric cells and arithmetic formulas.
- Cell references and rectangular ranges in `SUM`.
- Dependency tracking and cycle detection.
- Atomic formula replacement: a rejected edit leaves the sheet unchanged.
- Cached evaluation with selective invalidation and lazy recalculation.
- Recoverable evaluation errors.

Text cells, multiple sheets, relative/absolute-reference copying, undo/redo, concurrency, and functions other than `SUM` are outside the required scope and will not be tested.

## 2. Public interface

Your library must be available through `#include "mini_spreadsheet.hpp"` and provide the following interface in namespace `mini_sheet`:

```cpp
#include <cstddef>
#include <string>
#include <string_view>
#include <variant>

namespace mini_sheet {

enum class Error {
    DivisionByZero,
    Numeric
};

using Value = std::variant<double, Error>;

class Spreadsheet {
public:
    Spreadsheet();
    ~Spreadsheet();

    void set(std::string_view address, std::string_view input);
    void clear(std::string_view address);

    Value get(std::string_view address) const;
    std::string source(std::string_view address) const;
    std::size_t size() const noexcept;

    std::size_t evaluation_count() const noexcept;
    void reset_evaluation_count() noexcept;

    // Private representation and helper members are your choice.
};

} // namespace mini_sheet
```

Additional private members, helper classes, and headers are allowed. The displayed class is an interface specification, not a complete implementation. Copying and moving `Spreadsheet` objects are not required and will not be tested. Multiple independently constructed sheets must not share cell data or evaluation counters.

The library must own any strings or other data it retains after an API call. A caller may destroy or modify the strings passed to `set` immediately after it returns.

## 3. Addresses and empty cells

### Cell addresses

Addresses consist of one to three uppercase ASCII letters followed by a row number:

- Columns range from `A` through `ZZZ`, using spreadsheet column numbering: `A = 1`, `Z = 26`, `AA = 27`, and so on.
- Rows range from `1` through `1000000`.
- Leading zeroes are not allowed.
- Addresses are case-sensitive. `a1`, `A0`, `A01`, `AAAA1`, and `A1000001` are invalid.
- An address passed directly to an API method must not contain whitespace. For example, `get(" A1 ")` is invalid.

The same address rules apply inside formulas. An address is a single token, so `A 1` is invalid.

Invalid addresses passed to `set`, `clear`, `get`, or `source` cause `std::invalid_argument`. These calls must not change the sheet or its evaluation counter.

### Empty cells

A cell that has never been assigned, or that has been cleared, is empty:

- `get` returns the `double` value `0.0`.
- `source` returns an empty string.
- Empty cells are not included in `size()`.
- Reading an empty cell does not create a nonempty cell.

A reference to an empty cell is valid. The dependency must remain tracked so that assigning a value to that cell later invalidates its dependents.

## 4. Cell contents and formula syntax

### Input strings

For `set`, remove leading and trailing ASCII whitespace: space, tab, carriage return, and newline.

- An empty result means `clear(address)`.
- A result starting with `=` is a formula. Parse the remainder as an expression.
- Otherwise, the entire result must be a signed numeric literal. Arithmetic without a leading `=` is invalid.

For example:

| Input | Meaning |
| --- | --- |
| `" 12.5 "` | Numeric cell with value `12.5` |
| `"-3"` | Numeric cell with value `-3` |
| `"=A1 + 2"` | Formula |
| `"=42"` | Formula evaluating to `42`, not a numeric cell |
| `""` or `"   "` | Clear the cell |
| `"A1"` or `"1 + 2"` | Invalid input |

`source(address)` returns the last successfully assigned input after trimming its outer whitespace. Preserve all remaining characters exactly, including the leading `=` and internal whitespace. It returns by value.

Setting a cell to exactly the same stored source is a no-op. It must not invalidate any caches. Otherwise, a valid replacement may invalidate dependents even if its numerical result happens to be unchanged.

### Numbers

Numeric literals use this grammar:

```text
digits   := digit { digit }
number   := (digits [ "." [ digits ] ] | "." digits)
            [ ("e" | "E") [ "+" | "-" ] digits ]
digit    := "0" | "1" | ... | "9"
```

Examples include `0`, `12.`, `.5`, `3.25`, `1e3`, and `2.5E-2`. A sign is a separate unary operator in formulas. A non-formula numeric input may have one immediately adjacent leading `+` or `-`.

Numbers use `double`. Convert the unsigned numeric token using `std::from_chars` with `std::chars_format::general`, then apply a separate sign when necessary. The entire token must be consumed. A conversion error, including `std::errc::result_out_of_range`, makes the input invalid. Hexadecimal numbers, `nan`, `inf`, digit separators, and locale-specific decimal separators are invalid.

### Expressions

The following grammar specifies the required formula language:

```text
expression := term { ("+" | "-") term }
term       := unary { ("*" | "/") unary }
unary      := ("+" | "-") unary | primary
primary    := number | cell | "(" expression ")" | sum
sum        := "SUM" "(" argument { "," argument } ")"
argument   := range | expression
range      := cell ":" cell
cell       := a valid cell address
```

The four ASCII whitespace characters listed above may appear between tokens in formulas, but not inside a token. Function names are uppercase and case-sensitive.

- Unary `+` and `-` bind more tightly than multiplication and division.
- Multiplication and division bind more tightly than addition and subtraction.
- Binary operators at the same precedence associate to the left.
- Parentheses override precedence.
- The entire formula must be parsed; trailing tokens are invalid.
- Implicit multiplication is not supported: `=2(A1)` is invalid.
- `SUM` requires at least one argument. `=SUM()` is invalid.
- A range is valid only as an entire `SUM` argument. `=A1:B2` and `=SUM(A1:B2 * 2)` are invalid.

Examples:

```text
=2 + 3 * 4                   -> 14
=(2 + 3) * 4                 -> 20
=8 / 4 / 2                   -> 1
=-2 * -3                     -> 6
=1--2                        -> 3
=SUM(A1:B2, C1 * 2, -5)      -> valid
=SUM(SUM(A1:A3), 2)          -> valid
```

### Ranges and SUM

Range endpoints may appear in either order. Normalize row and column bounds independently: `B3:A1` and `A1:B3` describe the same six cells.

Within a range, visit cells by increasing row, then increasing column. For `A1:B2`, this order is `A1`, `B1`, `A2`, `B2`.

Visit `SUM` arguments from left to right. Each scalar argument contributes one value; each range contributes its cells in the order above. Start with `0.0` and add contributions sequentially. Empty cells contribute zero.

Repeated references and overlapping ranges contribute repeatedly:

```cpp
sheet.set("A1", "2");
sheet.set("A2", "3");
sheet.set("B1", "=SUM(A1:A2, A2, A1)");
// B1 is 2 + 3 + 3 + 2 = 10.
```

For dependency tracking, however, each referenced cell is a single direct dependency regardless of how many times it occurs in the formula.

## 5. Dependency tracking and rejected edits

If formula cell `B1` refers to `A1`, then `B1` depends on `A1`. This includes references inside ranges, references to empty cells, and references in expressions such as `0 * A1`. Dependency analysis is based on syntax, not the current numerical result or the execution path taken before an evaluation error.

The sheet must never contain a dependency cycle. Reject direct and indirect cycles with `std::invalid_argument`.

### Atomic replacement

When replacing a formula, determine validity using the proposed new formula in place of the old one. Its old outgoing dependency edges must not remain part of the proposed graph.

If an edit is rejected because of invalid input or a cycle, all observable state must remain unchanged:

- Stored source and `size()`.
- Dependency relationships.
- Cached values and errors, including which caches remain valid.
- The evaluation counter.

Exception messages are not tested. Recovery from allocation failure is outside the tests.

The following sequence must work:

```cpp
sheet.set("A1", "1");
sheet.set("B1", "=A1 + 1");
sheet.set("B1", "10");          // Remove B1's old dependency on A1.
sheet.set("A1", "=B1 + 1");     // Valid.

try {
    sheet.set("B1", "=A1 + 1"); // Would create a cycle. Reject.
} catch (const std::invalid_argument&) {
}

// B1 still contains "10" and evaluates to 10.
// A1 still contains "=B1 + 1" and evaluates to 11.
```

Other cycle examples:

- `A1 = A1 + 1` is invalid.
- `A1 = SUM(A1:B3)` is invalid.
- `A1 = 0 * A1` is invalid.
- `A1 = B1`, `B1 = C1`, followed by `C1 = A1` rejects only the last edit.
- `A1 = A2` and `B1 = A2` is valid: sharing a dependency does not create a cycle.

Clearing a cell removes its own formula and its outgoing dependencies. It does not remove references from other formulas to that address.

## 6. Evaluation and errors

`get` returns either a `double` or an `Error`. Valid formulas that encounter arithmetic errors remain stored; `set` does not evaluate them and does not reject them for that reason.

| Situation | Required behavior |
| --- | --- |
| Malformed source, invalid reference, or cycle in `set` | Throw `std::invalid_argument`; preserve the old state |
| Division by positive or negative zero | Return `Error::DivisionByZero` |
| Arithmetic produces a non-finite result | Return `Error::Numeric` |
| Reference to a cell with an evaluation error | Propagate that error |
| Reference to an empty cell | Use `0.0` |

Do not return NaN or infinity as a successful numeric result. Finite arithmetic underflow to zero is allowed. Positive and negative zero are treated as equal when grading numerical results.

### Evaluation order and error precedence

Evaluate a binary expression's left operand first. If it is an error, return that error without evaluating the right operand. Otherwise, evaluate the right operand and propagate its error, if any. Perform the operator only when both operands are numeric.

For unary operators, evaluate the operand and propagate any error. For `SUM`, process contributions in the order specified above and stop at the first error, including a non-finite intermediate sum. These rules determine which error is returned when several errors are possible.

For example, `=(1 / 0) + (1e308 * 1e308)` returns `Error::DivisionByZero`, while the reversed expression returns `Error::Numeric`.

### Error recovery

Errors must not become permanent:

```cpp
sheet.set("A1", "0");
sheet.set("B1", "=10 / A1");
sheet.set("C1", "=B1 + 2");
// get("B1") and get("C1") return Error::DivisionByZero.

sheet.set("A1", "2");
// get("B1") now returns 5.0; get("C1") returns 7.0.
```

Grading compares errors exactly and compares numbers using:

```text
abs(actual - expected) <= 1e-9 * max(1.0, abs(expected))
```

## 7. Incremental recalculation

Use lazy evaluation:

1. `set` parses and validates the replacement, updates dependency information, and invalidates affected caches. It does not evaluate formulas.
2. `clear` updates dependencies and invalidates affected caches. It does not evaluate formulas.
3. `get` evaluates a formula only if its cached result is unavailable or invalid. It recursively or iteratively obtains the dependencies needed by the evaluation rules.
4. Cache both numeric results and errors.

A successful edit must invalidate the edited formula, if any, and all formula cells that transitively depend on the edited address. Previously valid caches outside that affected set must stay valid. Invalidating an already-invalid formula is harmless, but graph traversal must still reach all affected dependents.

Clearing an already-empty cell is a no-op. Exact-source reassignment is also a no-op, as specified above.

### Evaluation counter

`evaluation_count()` is the cumulative number of formula-cell evaluations since construction or the last `reset_evaluation_count()`.

- Increment it once whenever a formula cell is actually evaluated because its cache is missing or invalid, including evaluation resulting in an error.
- Reading a cached result, numeric cell, or empty cell does not increment it.
- Evaluating individual expression-tree nodes does not increment it separately.
- `set`, `clear`, `source`, and `size` do not increment it.
- `reset_evaluation_count()` resets only the counter. It does not clear caches or alter the sheet.
- The counter must report actual evaluations; do not adjust it to simulate caching that your implementation does not perform.

This counter makes selective recalculation observable without depending solely on wall-clock timing.

Example, starting with a fresh sheet:

```cpp
sheet.set("A1", "1");
sheet.set("B1", "=A1 + 1");
sheet.set("C1", "=B1 * 2");
sheet.set("D1", "=100 + 1");

sheet.get("C1");                   // Evaluate B1 and C1: counter = 2.
sheet.get("D1");                   // Evaluate D1: counter = 3.
sheet.reset_evaluation_count();    // Caches remain valid; counter = 0.

sheet.set("A1", "5");             // Invalidate B1 and C1 only; counter = 0.
sheet.get("D1");                   // Cached 101; counter = 0.
sheet.get("C1");                   // Recompute B1 and C1; returns 12; counter = 2.
sheet.get("B1");                   // Cached 6; counter = 2.
```

If two branches share a dependency, evaluate that dependency at most once before it is next invalidated. For example, with `B1 = A1 + 1`, `C1 = A1 + 2`, and `D1 = B1 + C1`, shared references must not cause repeated evaluation of an unchanged formula in `A1`.

## 8. Data structures and performance

You must implement formula parsing, expression representation/evaluation, dependency management, cycle detection, and invalidation yourself. AI-generated code is permitted under the same responsibility and verification requirements as other submitted code.

You may use C++ standard-library containers and algorithms, including `std::vector`, `std::map`, `std::unordered_map`, `std::set`, and `std::queue`. Do not use an external expression parser, spreadsheet engine, graph library, or external process to compute results.

Expected design properties:

- Store cells sparsely; do not allocate the full possible grid.
- Retain parsed formulas, so unchanged formulas do not need to be reparsed on each `get`.
- Track dependencies in a form that supports discovering dependents after edits.
- Reuse cached results on repeated reads.
- Limit invalidation traversal to affected dependents and their relevant edges, rather than scanning every unrelated formula.
- Avoid repeatedly evaluating shared dependencies.

Cycle detection may take `O(V + E)` per edit in the worst case, where `V` and `E` are the numbers of represented dependency vertices and distinct edges. An advanced dynamic graph algorithm is not required. Discuss cycle checking separately from invalidation and evaluation in your complexity analysis.

### Test limits

The tests stay within these bounds:

| Quantity | Maximum |
| --- | ---: |
| Nonempty cells at one time | 50,000 |
| Distinct addresses that are nonempty or referenced at one time | 100,000 |
| Distinct dependency edges at one time, after expanding ranges | 500,000 |
| Public API calls per test | 100,000 |
| Input length per `set`, in bytes | 4,096 |
| Cells in one rectangular range | 10,000 |
| References in one formula, counting expanded ranges and duplicates | 20,000 |
| Expression nesting depth, including unary operators | 128 |
| Length of a dependency chain, in cells | 10,000 |

Tests may include malformed inputs and cyclic edits within these size bounds. Behavior for inputs exceeding the size bounds is not tested; invalid addresses remain governed by Section 3. Tests will not require every maximum to occur together.

Performance cases will include repeated cached reads, many independent formulas, long dependency chains, shared dependencies, and repeated local edits. Recursive graph algorithms must handle the stated chain length without relying on an unusually large process stack.

## 9. Complete usage example

The following program demonstrates the required public interface:

```cpp
#include "mini_spreadsheet.hpp"
#include <cassert>
#include <stdexcept>
#include <variant>

int main() {
    using mini_sheet::Error;
    mini_sheet::Spreadsheet sheet;

    sheet.set("A1", "10");
    sheet.set("A2", "20");
    sheet.set("B1", "=SUM(A1:A2)");
    assert(std::get<double>(sheet.get("B1")) == 30.0);

    sheet.set("A1", "5");
    assert(std::get<double>(sheet.get("B1")) == 25.0);

    sheet.clear("A2");
    assert(std::get<double>(sheet.get("B1")) == 5.0);
    assert(sheet.source("A2").empty());
    assert(sheet.size() == 2);

    sheet.set("C1", "=B1 / A2");
    assert(std::get<Error>(sheet.get("C1")) == Error::DivisionByZero);

    sheet.set("A2", "5");
    assert(std::get<double>(sheet.get("C1")) == 2.0);

    bool rejected = false;
    try {
        sheet.set("A1", "=C1"); // A1 -> C1 -> B1 -> A1.
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
    assert(sheet.source("A1") == "5");
    assert(std::get<double>(sheet.get("C1")) == 2.0);
}
```

Passing this example is necessary but not sufficient. Hidden tests exercise combinations and longer operation sequences using only the specified interface and behavior.

## 10. Testing

Submit automated tests that cover sequences of operations, not only isolated formulas.

Your tests should cover at least these categories:

1. Parsing, precedence, unary operators, whitespace, and malformed inputs.
2. Empty cells, clearing, source preservation, and `size()`.
3. Formula replacement and removal of obsolete dependencies.
4. Direct, indirect, and range-based cycles; rollback after rejected edits.
5. Error propagation, error precedence, and recovery.
6. Cache reuse, selective invalidation, and shared dependencies.
7. Repeated and overlapping ranges.
8. Long chains, many unrelated cells, and repeated edits.

Include a small randomized test driver with a fixed, reported seed. It must generate operation sequences and compare your implementation against a simple reference model for small sheets. The reference model may reevaluate everything and rebuild the dependency graph after each edit. It must not simply call your production evaluator as its oracle. You may implement this test-only model in C++ or Python using the standard library.

At minimum, randomized checks must compare values/errors, stored source, `size()`, and acceptance or rejection of edits. Check evaluation-counter behavior separately with targeted deterministic tests. Generate some invalid edits as well as valid edits.

## 11. Submission

Submit one ZIP file to LearnUs. The grader will use it directly through CMake's `FetchContent`, without modifying its contents:

```cmake
cmake_minimum_required(VERSION 3.24)
project(test_mini_spreadsheet LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    mini_spreadsheet
    URL ${CMAKE_CURRENT_SOURCE_DIR}/submission.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(mini_spreadsheet)

add_executable(test_sheet test_sheet.cpp)
target_link_libraries(test_sheet PRIVATE mini_spreadsheet)
```

Your ZIP must satisfy the following:

- `CMakeLists.txt` is at the ZIP root or inside one top-level directory.
- It defines a library target named exactly `mini_spreadsheet`.
- The target exposes `mini_spreadsheet.hpp` through its include directories and requires C++20.
- The library may be header-only (`INTERFACE`) or compiled (`STATIC`).
- The project builds without network access and does not fetch dependencies.
- Your tests, examples, and any executable containing `main` are built only when `PROJECT_IS_TOP_LEVEL` is true.
- Include your automated tests, randomized test driver, and reference model, with commands for running them (for example, in a short `README.md`).

For example, a header-only library can use:

```cmake
cmake_minimum_required(VERSION 3.24)
project(mini_spreadsheet LANGUAGES CXX)

add_library(mini_spreadsheet INTERFACE)
target_include_directories(mini_spreadsheet INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(mini_spreadsheet INTERFACE cxx_std_20)

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
    # Define your test executables and add_test(...) calls here.
endif()
```

Before submitting, test the ZIP itself using the grader-style CMake setup above. A project that only builds from your development directory may still fail when imported. If the library cannot configure, compile, or link through this setup, the automated functional tests cannot award credit.

## 12. Evaluation

Proposed grading weights:

| Component | Weight | What is assessed |
| --- | ---: | --- |
| Correctness | 50% | Parsing, values, errors, and dependency changes |
| Edge case handling | 30% | Invalid input, cycle rejection, atomicity of rejected edits, error precedence, and combinations not listed explicitly |
| Incremental behavior and efficiency | 20% | Actual cache reuse, selective invalidation, sparse storage, and workload performance |

Hidden cases will follow the published semantics. You are expected to handle combinations not listed explicitly, such as a cleared cell inside an overlapping range after a failed cyclic edit. Extra features outside this specification do not compensate for incorrect required behavior.

# ASSIGNMENT 5 – CO5
## Reliable Software with Runtime Polymorphism and Exceptions
**Name:** G. Raju  
**Register Number:** __________________  
**Compiler:** g++ (GNU C++), C++17  
**Compile flags:** `-std=c++17 -Wall -Wextra`

> Note: The assignment asks for measured timings and sanitizer evidence. The included programs generate reproducible local outputs; record timings from your own machine because they depend on hardware, compiler version and system load. Do not report illustrative timings as universal results.

# PART A – DESIGN

## A1. Design the polymorphic bill hierarchy

### A1.1 Common interface
Every bill should provide `total() const`, `type() const`, and `print() const`. Common data: patient name/identifier and optionally bill number/date. `total()` returns the payable bill amount. `type()` identifies the concrete bill. `print()` displays the bill. Charges must be non-negative and validated when an object is created.

### A1.2 UML hierarchy
```text
                    <<abstract>> Bill
             --------------------------------
             # patient : string
             + total() const : double {pure virtual}
             + type() const : string {virtual}
             + print() const : void
             + ~Bill() {virtual}
                       / | \\
                      /  |  \\
             OutPatient InPatient DayCareBill EmergencyBill
             total()    total()   total()      total()
             type()     type()    type()       type()
```
`Bill::total()` is pure virtual (`= 0`), so `Bill` is abstract. Derived classes override `total()` and `type()`. `print()` can be a normal function that calls virtual functions. The destructor is virtual so deleting a derived object through `Bill*` destroys it correctly.

### A1.3 Pseudocode to total bills
```text
ALGORITHM CalculateDayTotal
INPUT: array bills[0..n-1] of Bill pointers
OUTPUT: dayTotal
BEGIN
    dayTotal ← 0
    FOR i ← 0 TO n-1 DO
        IF bills[i] IS NOT NULL THEN
            dayTotal ← dayTotal + bills[i].total()
        END IF
    END FOR
    RETURN dayTotal
END
```
Time is O(n), because each bill is visited once. Extra working space is O(1), excluding the input array.

### Alternative: type field and switch
Use a `BillRecord` structure with a type tag and all required fields. `total()` uses `switch(type)` to calculate the appropriate formula. Processing n bills is O(n), with one switch per bill. A tagged record may reserve space for fields not used by every type. Adding a bill type requires changing the switch and often the shared structure, which increases regression risk. With virtual functions, a new derived class can implement the interface without modifying the existing processing loop.

## A2. Understand runtime binding

### A2.1 Early and late binding
Early binding selects a function at compile time, usually for non-virtual functions. Late binding selects the overridden function at runtime for a virtual call through a base pointer/reference. Thus `Bill* b = new OutPatient(...); b->total()` calls `OutPatient::total()` when `total()` is virtual.

### A2.2 Conceptual vtables
```text
Bill vtable (abstract)
  total -> pure virtual entry
  type  -> Bill::type (if defined virtual)
  ~Bill  -> Bill::~Bill

OutPatient vtable
  total -> OutPatient::total
  type  -> OutPatient::type
  ~OutPatient -> OutPatient::~OutPatient

InPatient vtable
  total -> InPatient::total
  type  -> InPatient::type
  ~InPatient -> InPatient::~InPatient
```
Exact vtable layout is compiler/ABI-specific; this is a conceptual diagram. For `b->total()`, the object’s dynamic type determines the overridden entry used.

### A2.3 Virtual destructor
A base class deleted through a base pointer must have a virtual destructor when derived objects are involved. Otherwise, deleting the derived object through `Bill*` has undefined behavior and may skip derived cleanup. AddressSanitizer may diagnose problems, but undefined behavior is not guaranteed to produce the same report on every platform.

### A2 predicted output
For the supplied program, the expected output is:
```text
500 ~OPBill ~Bill
```
`show()` itself is non-virtual, but it calls virtual `total()`. The virtual call dispatches to `OPBill::total()` because the object is an `OPBill`. Destruction prints the derived destructor first, then the base destructor. If `~Bill` is made non-virtual, `delete b` has undefined behavior; do not rely on a specific output or sanitizer message.

### Alternative: dynamic_cast
If `total()` were non-virtual, code could test the dynamic type using `dynamic_cast<OPBill*>`, `dynamic_cast<InPatientBill*>`, etc., and call type-specific calculations. For k types, it may require up to k checks per bill (O(k) per bill, O(nk) overall), versus one virtual dispatch per bill (O(1) dispatch, O(n) overall). Objects using virtual functions commonly store a hidden vptr, often one pointer per polymorphic object; actual object sizes depend on ABI and alignment.

## A3. Design with abstract payer classes

```cpp
class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};
class SelfPay : public Payer { /* covers full amount */ };
class Insurance : public Payer { /* coverLimit and coPaymentPercent */ };
class GovernmentScheme : public Payer { /* package rates by bill type */ };
```
`SelfPay` can return the full bill amount. `Insurance` caps the covered portion at its policy limit and applies the co-payment percentage. `GovernmentScheme` looks up a fixed package rate for the bill category. A corporate tie-up can be added as `CorporatePayer : public Payer`, implementing `amountCovered()` without changing the existing payer classes or the processing loop.

### Alternative: function pointer / std::function
A policy function can be stored and invoked at runtime. Both a virtual call and a function-object call are O(1) for the dispatch itself. A payer class naturally stores structured data such as cover limit and co-payment percentage as members. A `std::function` may capture those values in a closure; its storage can be larger and may allocate dynamically, depending on the closure and implementation. An abstract class is clearer when each payer has multiple operations and persistent state.

## A4. Design the exception strategy

### A4.1 Error list and hierarchy
```text
std::exception
  └── std::runtime_error
       └── BillingError
            ├── InvalidChargeError
            ├── ClaimError
            ├── UnknownPackageError
            └── MissingPatientError
std::bad_alloc (standard allocation failure)
std::invalid_argument (invalid numeric text / argument)
```
Errors include negative charges, claim above cover, unknown package code, missing patient record, invalid text where a number is expected, and allocation failure. Validate inputs early and provide clear error messages.

### A4.2 Throwing and noexcept
Functions validating user input, calculating claims, looking up packages, parsing numbers and allocating memory may throw. A destructor should not throw; cleanup functions and simple accessors can be marked `noexcept` only when they truly cannot throw. Throwing from a destructor during stack unwinding can cause `std::terminate`. Avoid falsely marking potentially throwing operations `noexcept`, because an exception escaping them also terminates the program.

### Alternative: return status codes
A function can return `Status` plus an output parameter or an object containing status/message/value. Normal-path time is O(1) per validation and error-path time is also O(1) for simple checks. Return codes avoid exception-unwinding overhead but require every caller to inspect and propagate status and message data. Missing a check can silently ignore an error. Exceptions separate error handling from normal logic but are typically most suitable for exceptional conditions, not frequent expected rejections.

## A5. Recovery and rethrowing

### A5.1 Where to catch
- Low-level validation throws a specific exception and does not hide it.
- A service boundary may log context and use `throw;` to rethrow the same exception.
- The top-level request handler catches known exceptions and reports a safe message to the user.
- Unexpected exceptions are caught by a final `catch (...)` at the application boundary, logged, and converted into a safe failure response.

### A5.2 Stack unwinding and RAII
When an exception leaves a scope, C++ destroys local automatic objects in reverse construction order. RAII objects such as `std::string`, `std::vector`, `std::unique_ptr` and file streams release their resources in destructors. This prevents leaks when control leaves a function through an exception.

### A5 predicted output
```text
~f ~main caught 42
```
The `Guard g("f")` is destroyed first when `f()` throws. Then `Guard m("main")` is destroyed while unwinding the `try` scope. The `catch` prints `caught 42`. The statement `not printed` is skipped because the exception transfers control to the matching handler.

### Alternative: manual delete in catch blocks
Manual cleanup can have similar asymptotic time, but every exit/error path must release every resource. Adding a new throw point creates more places where cleanup can be missed. RAII centralizes cleanup in destructors and is safer and less error-prone.

# PART B – IMPLEMENTATION & EXPERIMENTAL INVESTIGATION

## B1. Polymorphic billing implementation

The completed program is in `Task01/billing.cpp`. It defines `Bill`, `OutPatient`, and `InPatient`; calls `print()` through base pointers; and sums totals. Expected output:
```text
OP Ravi: 1700
IP Meena: 47500
Total 49200
```
Manual check: OP = 500 + 1200 = 1700. IP = 3 × 2500 + 40000 = 47500. Day total = 1700 + 47500 = 49200. Removing `virtual` from `total()` while retaining `= 0` makes the declaration invalid: a pure virtual function must be virtual. If it becomes an ordinary non-virtual function instead, calls through `Bill*` do not dynamically dispatch to derived implementations.

## B2. Engineer error conditions

`Task02/claim_errors.cpp` completes the `approve()` and `settle()` TODOs. Expected output:
```text
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```
`throw;` rethrows the currently handled exception without changing its dynamic type. `throw e;` throws an expression copy whose static type may be the base reference type (`ClaimError` here is the caught type, so this example remains `ClaimError`; with a base-class reference it can slice the derived exception). Prefer `throw;` to preserve the original exception object.

The `Task02/error_tests.cpp` program checks negative values, excessive values, invalid numeric text, allocation failure handling (platform limits vary), and catch-all handling. An impossible allocation request is not guaranteed to throw on every operating system because overcommit policies vary; treat that test as environment-dependent.

### B2 predicted output program
```text
ok done caught negative [log too large] caught too large
```
The first value validates and prints `ok`, then `done`. The negative value throws `invalid_argument`; `process()` only catches `out_of_range`, so no log is printed there and the outer handler prints `caught negative`. The too-large value is logged in `process()` and rethrown; the outer handler prints `caught too large`.

### optional vs exceptions
`std::optional<double>` represents rejection as no value. For 1,000,000 claims, both approaches still inspect all claims: O(n). Return/optional results are generally suitable for frequent expected invalid claims; exceptions can be clearer when failures are rare. The exact time must be measured on the target machine. `optional<double>` needs space for a value plus a presence indicator (padding may apply); exception handling has runtime/library bookkeeping and exception-object storage only on the error path.

## B3. Virtual functions vs switch vs exceptions

`Task03/benchmark.cpp` compares a virtual hierarchy with a tagged record and switch, and measures return-code validation versus exceptions at 0%, 1% and 50% invalid rates. It also reports results for 1,000, 1,000,000 and 10,000,000 bills. Compile with `-O2`. Both billing approaches should produce the same total. Both are O(n); measured constants depend on compiler, CPU, data layout and optimization. Exceptions are commonly inexpensive on the normal path but costly when thrown frequently. Use exceptions for exceptional failures and status/optional results for routine validation outcomes.

### Alternative: std::variant and std::visit
Store bill alternatives in `std::variant<OutPatientBill, InPatientBill, ...>` and process each using `std::visit`. It avoids a base-class pointer/vtable dispatch and keeps alternatives in one container, but each element reserves enough storage for the largest alternative plus a discriminator and padding. Benchmark it on the same machine for a fair comparison. New alternatives may require updating visitor handling and the variant type.

## B4. Final engineering decision

`Task04/extension.cpp` demonstrates adding `EmergencyBill` and `CorporatePayer` while preserving existing classes. The processing code works through the existing abstract interfaces. For a system processing 200,000 bills/day and adding types regularly, polymorphic bill and payer interfaces provide maintainable extension points. Exceptions are appropriate for invalid input, missing records and infrastructure failures; expected claim rejections may be represented by status/optional results if they are frequent. Require automated tests, logging, input validation, ownership through RAII, CI builds with warnings, and AddressSanitizer testing before production deployment.

### Alternative: configuration plug-ins
Rate rules could be loaded from validated configuration data. Rule lookup can be O(1) with a suitable hash map or O(log r) with an ordered map for r rules; interpreting complex rules adds overhead. Configuration can make routine rate changes faster without recompilation but introduces risks from malformed, stale or unauthorized configuration. Keep rule schemas validated, versioned, audited and tested. C++ classes are more suitable when new behaviour requires complex algorithms; configuration is suitable for rate/package changes expressible as data.

## Build and run
From the assignment root, for each `.cpp` file:
```bash
g++ -std=c++17 -Wall -Wextra Task01/billing.cpp -o billing
./billing
```
For the benchmark:
```bash
g++ -std=c++17 -O2 -Wall -Wextra Task03/benchmark.cpp -o benchmark
./benchmark
```
For sanitizer checks (where supported):
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer Task02/error_tests.cpp -o error_tests
./error_tests
```

## Submission checklist
- Add your register number and GitHub repository URL.
- Commit each task separately; do not make one final bulk commit only.
- Upload source files, test inputs, actual output screenshots, predictions, timing results and sanitizer report.
- The PNGs in `Output_Screenshots` are terminal-style representations of the captured program output. For official evidence, run the programs on your own machine and take real terminal screenshots if required by your faculty.

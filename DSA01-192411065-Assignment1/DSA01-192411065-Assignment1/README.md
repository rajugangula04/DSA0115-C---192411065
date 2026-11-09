# DSA01-192411065-Assignment1

## Student Details
- Name: G. Raju
- Register Number: 192411065
- Department: CSE
- Assignment: Design, Implement and Validate the Fare Logic of a City Metro Smart-Card System
- Language: C++
- Standard: C++17

## Compiler
Check your installed compiler version using:
```bash
g++ --version
```

Compile each program from its task folder:
```bash
g++ -std=c++17 -Wall -Wextra filename.cpp -o program
```

Run on Windows:
```powershell
.\program.exe
```

Run on Linux/macOS:
```bash
./program
```

## Task Files
| Task | Source file | Description |
|---|---|---|
| Task01 | `object_analysis.cpp` | Passenger and SmartCard objects |
| Task02 | `constants.cpp` | Constants and enum class |
| Task03 | `datatypes.cpp` | Data types, sizes and limits |
| Task04 | `conversions.cpp` | Implicit and explicit conversions |
| Task05 | `operators.cpp` | Operators and precedence |
| Task06 | `control_structures.cpp` | Switch, if-else and loop |
| Task07 | `procedural_vs_oop.cpp` | Procedural and OOP comparison |
| Task08 | `input_output.cpp` | Validated input and formatted output |
| Task09 | `fare_testing.cpp` | Fare logic and test cases |
| Task10 | `scale_comparison.cpp` | Network scale and integer range |
| Task11 | `final_design.cpp` | Recommended three-zone design |
| Task12 | `updated_design.cpp` | Fourth zone, weekend discount and monthly pass |

## Important Assumptions
- Money is stored as integer paise.
- Peak hours are 08:00 to before 10:00 and 17:00 to before 20:00.
- Exactly 10:00 and 20:00 are off-peak.
- Minimum remaining card balance after a paid journey is Rs 50.
- The original assignment does not specify concession percentages. The programs do not invent a student/senior concession rate.
- Task12 demonstrates an assumed 10% weekend discount. It replaces the peak surcharge; confirm this policy with faculty.
- The Task12 monthly pass is a simplified demonstration for two selected zones. A production pass also needs start date, expiry date, passenger eligibility and transaction records.

## Execution and Evidence
Compile and run every source file yourself. Add your own terminal screenshots and any required input/output files inside the corresponding Task folder before submission. Do not mark a task as executed until you have run it and checked its output.

## GitHub Commit Example
```bash
git add Task01
git commit -m "Completed Task 01"
```
Make at least one progressive commit for every task, as required by the assignment.

## Conclusion
This repository contains C++ examples for analysing, implementing and testing the metro smart-card fare logic.

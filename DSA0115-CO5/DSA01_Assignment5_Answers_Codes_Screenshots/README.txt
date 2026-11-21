ASSIGNMENT 5 – CO5 PACKAGE

Contents:
- Assignment5_Complete_Answers.md: Part A design answers and Part B explanations.
- Task01: completed polymorphic billing code.
- Task02: completed claim TODOs, predicted-output programs, error-condition tests.
- Task03: benchmark for virtual vs switch and return-code vs exceptions.
- Task04: extension with EmergencyBill and CorporatePayer.
- Output_Screenshots: terminal-style PNG screenshots for executed program outputs.
- ALL_OUTPUTS.txt: combined captured stdout/stderr.

Compile examples:
g++ -std=c++17 -Wall -Wextra Task01/billing.cpp -o billing
g++ -std=c++17 -Wall -Wextra Task02/claim_errors.cpp -o claim_errors
g++ -std=c++17 -Wall -Wextra Task02/prediction_stack_unwinding.cpp -o stack
g++ -std=c++17 -Wall -Wextra Task02/prediction_rethrow.cpp -o rethrow
g++ -std=c++17 -O2 -Wall -Wextra Task03/benchmark.cpp -o benchmark
g++ -std=c++17 -Wall -Wextra Task04/extension.cpp -o extension

The PNGs are terminal-style representations of program output, not photos of a real terminal. Benchmark timings vary by machine. Complete register number, GitHub URL and local measurements before submission.

# DeadlockDoctor — Resource & Deadlock Manager

DeadlockDoctor is a C11 terminal application that demonstrates the Banker's deadlock-avoidance algorithm. It calculates Need, checks for a safe sequence, allows custom resource-allocation scenarios, and simulates resource requests using a tentative allocation followed by safety verification and rollback when unsafe.

## Build and run (Ubuntu / WSL)
```bash
make clean
make
make test
./deadlock_doctor
```
Requires GCC and GNU Make. No database or third-party library is required.

## Menu
1. Reload the built-in safe example
2. Enter a custom scenario
3. Display Allocation, Maximum, Need and Available
4. Run the safety check
5. Request resources for a process
6. Exit

## Demo values
Built-in example: 5 processes, 3 resource types, Available = (3,3,2). Expected safe sequence: P1 -> P3 -> P4 -> P0 -> P2.

Valid request: reset with option 1, select option 5, process 3, then request (0,1,1). Expected: granted.
Unsafe tentative request: reset with option 1, select option 5, process 4, then request (3,3,0). Expected: denied and state preserved.

## Scope
This is an educational user-space simulation. It does not control kernel resources or inspect real running processes. "Unsafe" means no safe sequence can be found for the declared state; it does not necessarily mean a deadlock has already happened.

See `docs/DEMO_SCRIPT.md` for a review walkthrough.

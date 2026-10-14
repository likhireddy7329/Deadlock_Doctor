# End-term review demo script

## Before class
Run `make clean && make && make test` in the extracted project folder.

## Demo 1 — Show the state
1. Start `./deadlock_doctor`.
2. Enter `3`.
3. Explain: Allocation = currently held, Maximum = maximum claim, Need = Maximum − Allocation, Available = free now.

## Demo 2 — Safe sequence
1. Enter `4`.
2. Expected result: SAFE; P1 -> P3 -> P4 -> P0 -> P2.
3. Explain: a process can finish when its Need is no greater than Work/available resources; when it finishes, its allocated resources are added back to Work.

## Demo 3 — Grant a valid request
1. Enter `1` to reset the demo.
2. Enter `5`, process `3`, then R0=`0`, R1=`1`, R2=`1`.
3. Expected: request granted; the resulting state remains safe.

## Demo 4 — Deny an unsafe request
1. Enter `1` to reset.
2. Enter `5`, process `4`, then R0=`3`, R1=`3`, R2=`0`.
3. Expected: denied. The request fits P4's original Need and Available, but the tentative state is unsafe. The code rolls back Allocation and Available.

## Demo 5 — Custom unsafe scenario
Choose option `2`: processes `2`, resources `1`; Allocation P0=1, P1=1; Maximum P0=2, P1=2; Available R0=0. Expected: UNSAFE.

## Short explanation
The program is a user-space educational simulation of Banker’s algorithm, not a live kernel deadlock detector.

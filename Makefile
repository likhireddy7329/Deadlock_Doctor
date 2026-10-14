CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g
SRC = src/main.c src/input.c src/deadlock.c

.PHONY: all clean test run
all: deadlock_doctor

deadlock_doctor: $(SRC) include/deadlock.h include/input.h
	$(CC) $(CFLAGS) $(SRC) -o $@

test_deadlock: tests/test_deadlock.c src/deadlock.c include/deadlock.h
	$(CC) $(CFLAGS) tests/test_deadlock.c src/deadlock.c -o $@

test: deadlock_doctor test_deadlock
	@echo "[1/3] Unit tests"
	@./test_deadlock
	@echo "[2/3] Application smoke test"
	@printf "4\n6\n" | ./deadlock_doctor | grep -q "SYSTEM STATUS: SAFE"
	@echo "PASS: application starts and built-in safety check works"
	@echo "[3/3] Test suite complete"

run: deadlock_doctor
	./deadlock_doctor

clean:
	rm -f deadlock_doctor test_deadlock

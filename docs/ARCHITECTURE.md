# Architecture and module responsibilities

```text
User
  |
  v
main.c: menu, demo, scenario loading, output
  |
  +--> input.c: bounded integer input, matrices, vectors
  |
  +--> deadlock.c: Need calculation, safety check, resource request + rollback
```

- `src/main.c`: menu and workflow.
- `src/input.c`: validates numeric ranges and reads matrix/vector values.
- `src/deadlock.c`: algorithm implementation.
- `include/*.h`: shared interfaces and limits.
- `tests/test_deadlock.c`: unit tests.
- `Makefile`: build, run, test, clean.

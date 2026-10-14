#ifndef INPUT_H
#define INPUT_H
#include "deadlock.h"
int read_int_range(const char *prompt, int min, int max, int *out);
int read_nonnegative_vector(const char *prompt, int r, int vector[MAX_RESOURCES]);
int read_matrix(const char *title, int p, int r, int matrix[MAX_PROCESSES][MAX_RESOURCES]);
#endif

#include <stdio.h>
#include "input.h"

int read_int_range(const char *prompt, int min, int max, int *out) {
    char line[128];
    long value;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0;
        if (sscanf(line, " %ld %c", &value, &extra) == 1 && value >= min && value <= max) {
            *out = (int)value;
            return 1;
        }
        printf("Please enter one integer from %d to %d.\n", min, max);
    }
}

int read_nonnegative_vector(const char *prompt, int r, int vector[MAX_RESOURCES]) {
    printf("%s\n", prompt);
    for (int j = 0; j < r; ++j) {
        char label[48];
        snprintf(label, sizeof label, "  R%d: ", j);
        if (!read_int_range(label, 0, 1000000, &vector[j])) return 0;
    }
    return 1;
}

int read_matrix(const char *title, int p, int r, int matrix[MAX_PROCESSES][MAX_RESOURCES]) {
    printf("\n%s\n", title);
    printf("Enter each value separately when prompted.\n");
    for (int i = 0; i < p; ++i) {
        printf("P%d:\n", i);
        for (int j = 0; j < r; ++j) {
            char label[48];
            snprintf(label, sizeof label, "  R%d: ", j);
            if (!read_int_range(label, 0, 1000000, &matrix[i][j])) return 0;
        }
    }
    return 1;
}

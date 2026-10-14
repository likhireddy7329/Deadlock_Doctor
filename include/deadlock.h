#ifndef DEADLOCK_H
#define DEADLOCK_H
#define MAX_PROCESSES 20
#define MAX_RESOURCES 10

int calculate_need(int p, int r,
    const int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int need[MAX_PROCESSES][MAX_RESOURCES]);

int safety_check(int p, int r,
    const int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    const int available[MAX_RESOURCES],
    int sequence[MAX_PROCESSES]);

/* 1 = granted, 0 = denied, -1 = invalid/inconsistent input */
int request_resources(int process, int p, int r,
    int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int available[MAX_RESOURCES],
    const int request[MAX_RESOURCES]);

#endif

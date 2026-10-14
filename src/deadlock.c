#include <string.h>
#include "deadlock.h"

static int valid_dimensions(int p, int r) {
    return p >= 1 && p <= MAX_PROCESSES && r >= 1 && r <= MAX_RESOURCES;
}

int calculate_need(int p, int r,
    const int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int need[MAX_PROCESSES][MAX_RESOURCES]) {
    if (!valid_dimensions(p, r)) return 0;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            if (allocation[i][j] < 0 || maximum[i][j] < allocation[i][j]) return 0;
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    return 1;
}

int safety_check(int p, int r,
    const int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    const int available[MAX_RESOURCES],
    int sequence[MAX_PROCESSES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES] = {{0}};
    int work[MAX_RESOURCES] = {0};
    int finish[MAX_PROCESSES] = {0};
    if (!valid_dimensions(p, r) || !calculate_need(p, r, allocation, maximum, need)) return 0;
    for (int j = 0; j < r; ++j) {
        if (available[j] < 0) return 0;
        work[j] = available[j];
    }
    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; ++i) {
            if (finish[i]) continue;
            int can_finish = 1;
            for (int j = 0; j < r; ++j) {
                if (need[i][j] > work[j]) { can_finish = 0; break; }
            }
            if (can_finish) {
                for (int j = 0; j < r; ++j) work[j] += allocation[i][j];
                finish[i] = 1;
                sequence[count++] = i;
                found = 1;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int request_resources(int process, int p, int r,
    int allocation[MAX_PROCESSES][MAX_RESOURCES],
    const int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int available[MAX_RESOURCES],
    const int request[MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES] = {{0}};
    int sequence[MAX_PROCESSES];
    if (!valid_dimensions(p, r) || process < 0 || process >= p) return -1;
    if (!calculate_need(p, r, allocation, maximum, need)) return -1;
    for (int j = 0; j < r; ++j) {
        if (available[j] < 0 || request[j] < 0) return -1;
        if (request[j] > need[process][j] || request[j] > available[j]) return 0;
    }
    for (int j = 0; j < r; ++j) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
    }
    if (safety_check(p, r, allocation, maximum, available, sequence)) return 1;
    for (int j = 0; j < r; ++j) {
        allocation[process][j] -= request[j];
        available[j] += request[j];
    }
    return 0;
}

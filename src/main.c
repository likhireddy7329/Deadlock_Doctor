#include <stdio.h>
#include <string.h>
#include "deadlock.h"
#include "input.h"

static int p = 5, r = 3;
static int allocation[MAX_PROCESSES][MAX_RESOURCES];
static int maximum[MAX_PROCESSES][MAX_RESOURCES];
static int available[MAX_RESOURCES];

static void load_safe_demo(void) {
    const int a[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    const int m[5][3] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    const int v[3] = {3,3,2};
    memset(allocation, 0, sizeof allocation);
    memset(maximum, 0, sizeof maximum);
    memset(available, 0, sizeof available);
    for (int i=0;i<5;i++) for (int j=0;j<3;j++) { allocation[i][j]=a[i][j]; maximum[i][j]=m[i][j]; }
    for (int j=0;j<3;j++) available[j]=v[j];
    p=5; r=3;
}

static void print_matrix(const char *name, int matrix[MAX_PROCESSES][MAX_RESOURCES]) {
    printf("\n%s\n       ", name);
    for (int j=0;j<r;j++) printf("R%-5d", j);
    putchar('\n');
    for (int i=0;i<p;i++) {
        printf("P%-5d", i);
        for (int j=0;j<r;j++) printf("%-6d", matrix[i][j]);
        putchar('\n');
    }
}

static void display_state(void) {
    int need[MAX_PROCESSES][MAX_RESOURCES]={{0}};
    if (!calculate_need(p,r,allocation,maximum,need)) {
        puts("Invalid state: every Maximum value must be >= Allocation.");
        return;
    }
    print_matrix("Allocation Matrix (currently held)", allocation);
    print_matrix("Maximum Matrix (maximum claim)", maximum);
    print_matrix("Need Matrix (Maximum - Allocation)", need);
    printf("\nAvailable Resources: ");
    for (int j=0;j<r;j++) printf("R%d=%d%s",j,available[j],j==r-1?"\n":"  ");
}

static void run_safety(void) {
    int sequence[MAX_PROCESSES];
    if (safety_check(p,r,allocation,maximum,available,sequence)) {
        printf("\nSYSTEM STATUS: SAFE\nSafe Sequence: ");
        for (int i=0;i<p;i++) printf("P%d%s",sequence[i],i==p-1?"\n":" -> ");
        puts("Meaning: every process can finish in this order without deadlock.");
    } else {
        puts("\nSYSTEM STATUS: UNSAFE");
        puts("No safe sequence exists for the current declared state.");
        puts("This indicates deadlock risk; it does not prove deadlock has already occurred.");
    }
}

static void custom_scenario(void) {
    int np,nr;
    if (!read_int_range("Number of processes (1-20): ",1,MAX_PROCESSES,&np) ||
        !read_int_range("Number of resources (1-10): ",1,MAX_RESOURCES,&nr)) return;
    int a[MAX_PROCESSES][MAX_RESOURCES]={{0}}, m[MAX_PROCESSES][MAX_RESOURCES]={{0}}, v[MAX_RESOURCES]={0};
    if (!read_matrix("Enter Allocation Matrix",np,nr,a) ||
        !read_matrix("Enter Maximum Matrix",np,nr,m) ||
        !read_nonnegative_vector("Enter Available Resource Vector",nr,v)) return;
    int need[MAX_PROCESSES][MAX_RESOURCES]={{0}};
    if (!calculate_need(np,nr,a,m,need)) {
        puts("Invalid scenario: Maximum must be greater than or equal to Allocation for every cell. Existing state unchanged.");
        return;
    }
    p=np; r=nr;
    memcpy(allocation,a,sizeof allocation);
    memcpy(maximum,m,sizeof maximum);
    memcpy(available,v,sizeof available);
    puts("Custom scenario loaded.");
    run_safety();
}

static void request_resources_menu(void) {
    int process, request[MAX_RESOURCES]={0};
    if (!read_int_range("Process number: ",0,p-1,&process)) return;
    if (!read_nonnegative_vector("Enter request vector",r,request)) return;
    int result=request_resources(process,p,r,allocation,maximum,available,request);
    if (result==1) puts("REQUEST GRANTED: tentative allocation is safe; state updated.");
    else if (result==0) puts("REQUEST DENIED: exceeds Need/Available or would make the state unsafe. State preserved.");
    else puts("INVALID REQUEST/STATE: input or matrices are inconsistent.");
}

int main(void) {
    load_safe_demo();
    puts("\n================================================");
    puts("                 DEADLOCK DOCTOR");
    puts("          Resource & Deadlock Manager");
    puts("================================================");
    puts("Educational simulation of Banker's safety algorithm.");
    puts("Built-in SAFE demo loaded automatically.");
    int choice;
    for (;;) {
        puts("\n-------------------- MENU --------------------");
        puts("1. Load built-in SAFE demo");
        puts("2. Enter custom scenario");
        puts("3. Display current resource state");
        puts("4. Run safety/deadlock check");
        puts("5. Request resources for a process");
        puts("6. Exit");
        if (!read_int_range("Enter choice (1-6): ",1,6,&choice)) break;
        switch(choice) {
            case 1: load_safe_demo(); puts("Built-in SAFE demo loaded."); break;
            case 2: custom_scenario(); break;
            case 3: display_state(); break;
            case 4: run_safety(); break;
            case 5: request_resources_menu(); break;
            case 6: puts("Thank you for using DeadlockDoctor."); return 0;
        }
    }
    return 0;
}

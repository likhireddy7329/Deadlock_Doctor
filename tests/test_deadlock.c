#include <stdio.h>
#include <string.h>
#include "deadlock.h"
static int failures=0, checks=0;
#define CHECK(x,msg) do { checks++; if (x) printf("PASS: %s\n",msg); else {printf("FAIL: %s\n",msg); failures++;} } while(0)
int main(void) {
    int a[MAX_PROCESSES][MAX_RESOURCES]={{0}}, m[MAX_PROCESSES][MAX_RESOURCES]={{0}}, v[MAX_RESOURCES]={3,3,2}, seq[MAX_PROCESSES];
    const int aa[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    const int mm[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    for(int i=0;i<5;i++) for(int j=0;j<3;j++){a[i][j]=aa[i][j];m[i][j]=mm[i][j];}
    int need[MAX_PROCESSES][MAX_RESOURCES]={{0}};
    CHECK(calculate_need(5,3,a,m,need),"Need matrix calculates successfully");
    CHECK(need[3][0]==0 && need[3][1]==1 && need[3][2]==1,"P3 Need is (0,1,1)");
    CHECK(safety_check(5,3,a,m,v,seq),"built-in state is SAFE");
    CHECK(seq[0]==1 && seq[1]==3 && seq[2]==4 && seq[3]==0 && seq[4]==2,"safe sequence matches expected demo");
    int req[MAX_RESOURCES]={0,1,1};
    CHECK(request_resources(3,5,3,a,m,v,req)==1,"valid P3 request is granted");
    int req_too_big[MAX_RESOURCES]={9,0,0};
    CHECK(request_resources(3,5,3,a,m,v,req_too_big)==0,"request above Need/Available is denied");
    int bad_a[MAX_PROCESSES][MAX_RESOURCES]={{0}}, bad_m[MAX_PROCESSES][MAX_RESOURCES]={{0}}, bad_v[MAX_RESOURCES]={0};
    bad_a[0][0]=1; bad_a[1][0]=1; bad_m[0][0]=2; bad_m[1][0]=2;
    CHECK(!safety_check(2,1,bad_a,bad_m,bad_v,seq),"no-progress state is UNSAFE");
    int ra[MAX_PROCESSES][MAX_RESOURCES]={{0}}, rm[MAX_PROCESSES][MAX_RESOURCES]={{0}}, rv[MAX_RESOURCES]={3,3,2};
    for(int i=0;i<5;i++)for(int j=0;j<3;j++){ra[i][j]=aa[i][j];rm[i][j]=mm[i][j];}
    int snapshot_a[MAX_PROCESSES][MAX_RESOURCES], snapshot_v[MAX_RESOURCES];
    memcpy(snapshot_a,ra,sizeof ra); memcpy(snapshot_v,rv,sizeof rv);
    int unsafe_req[MAX_RESOURCES]={3,3,0};
    CHECK(request_resources(4,5,3,ra,rm,rv,unsafe_req)==0,"unsafe tentative grant is denied");
    CHECK(memcmp(snapshot_a,ra,sizeof ra)==0 && memcmp(snapshot_v,rv,sizeof rv)==0,"rollback restores Allocation and Available");
    int unavailable[MAX_RESOURCES]={4,0,0};
    CHECK(request_resources(4,5,3,ra,rm,rv,unavailable)==0,"request above Available is denied");
    CHECK(request_resources(9,5,3,ra,rm,rv,req)==-1,"invalid process index is rejected");
    int inconsistent[MAX_PROCESSES][MAX_RESOURCES]={{0}};
    inconsistent[0][0]=2; int max_bad[MAX_PROCESSES][MAX_RESOURCES]={{0}}; max_bad[0][0]=1;
    CHECK(!calculate_need(1,1,inconsistent,max_bad,need),"Maximum below Allocation is rejected");
    printf("\nChecks: %d, Failures: %d\n",checks,failures);
    return failures ? 1 : 0;
}

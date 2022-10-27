/**
 * @file schedtest.c
 * @author JesseSlater
 * @brief 
 * Runs tests of the scheduler
 * 
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/log.h"

void test1(){
    fork();
    nice(-19);
    struct logentry log[100];
    uint64 acc = 0; 
    startlog();
    for (uint64 i=0; i<900000000; i++) { 
        acc += 1; 
    }
    int n = getlog(&log[0]);
    for (int i=0; i < n; i++){
        printf("pid %d, time %d\n", log[i].pid, log[i].time);
    }
    printf("acc %d\n", acc);
}

void test2(){
    int f = fork();
    nice(-19);
    struct logentry log[100];
    uint64 acc = 0; 
    startlog();
    if (f != 0) {
        for (uint64 i=0; i<1000000; i++) { 
            acc += 1; 
        }
    }
    else {
        for (uint64 i=0; i<1000; i++) { 
            sleep(.01); 
            acc += 1;
        } 
    }
    int n = getlog(&log[0]);
    for (int i=0; i < n; i++){
        printf("pid %d, time %d\n", log[i].pid, log[i].time);
    }
    printf("acc %d\n", acc);
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Too few arguments. Expected test number (1 or 2)\n"); 
    }
    else if(argv[1][0] == '1')
    {
        test1();
    }
    else if(argv[1][0] == '2')
    {
        test2();
    }
    else
    {
        printf("Invalid argument. Expected test number (1 or 2)\n");
    }
    exit(0);
}


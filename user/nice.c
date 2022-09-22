/**
 * @file nice.c
 * @author John Mindrup
 * @brief 
 * Adds the nice command line utility to xv6-risc
 * Sets the nice value for a command line utility and executes the command
 * 
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    //the nice value
    int nicevalue;
    if(argc < 2)
    printf("Too few arguments expected nice N PROG [ARG] ...\n");
    /**
     * atoi should return 0 if given something that starts with a non-number
     * check if its '-' and if so give it the string argument indexed one further
     * if not give atoi the full string
     * if the argument starts with numbers it will convert those as an int
     * will default to zero if a non-number is given
     */
    if(argv[1][0] == '-')
    {
        nicevalue = atoi(argv[1]+1);
    }
    else
    {
        nicevalue = atoi(argv[1]);
    }
    //make the nice system call with the nicevalue
    nice(nicevalue);
    if(argc < 3)
    printf("Too few arguments expected nice N PROG [ARG] ...\n");
    exec(argv[2], &argv[2]);
    exit(0);
}
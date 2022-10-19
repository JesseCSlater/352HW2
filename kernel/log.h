//Log entry struct. Copied from project doc
#define LOG_SIZE 100 

//Global clock. Copied from announcement
extern int time;

struct logentry { 
        int pid; // process id 
        int time; // number of ticks 
};
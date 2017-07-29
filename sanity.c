#include "types.h"
#include "user.h"
#include "stat.h"


int iteration_definition = 50;                        

struct perf {
    int ctime;
    int ttime;
    int stime;
    int retime;
    int rutime;
};


int fib(int n)
{
    if (n <= 1){
        return n;
    }
    return fib(n-1)+fib(n-2);
}



int main() {
    int average_running_time = 0;
    int average_ready_state_time = 0;
    int average_sleeping_state_time = 0;
    int average_turnaround_time = 0;
    struct perf performance;
    int status;
    int pid;
    for (int i = 0; i < iteration_definition; i++)
    {
        if (fork() == 0)
        {
            if (i % 10 == 0)                            // Every tenth process is performing I\O
            {
                printf(1,"Perform IO\n");
                exit(0);
            }
            else if (i % 7 == 0)                             // It means that in prioritized policy (policy #1), approximately one of every 5 processes should get more running time (better turnaround)
            {
                priority(1000000);
            }
            else if (i % 6 == 0){
                for (int j = 0; j < 10; j++){
                    sleep(1);
                }
            }
            fib(30);
            exit(0);
        }
    }
    for (int i = 0; i < iteration_definition; i++)
    {
        pid = wait_stat(&status, &performance);                                 // Return pid of child process
        average_running_time += performance.rutime;                             // Sum child process running time
        average_ready_state_time += performance.retime;                         // Sum child process ready state time
        average_sleeping_state_time += performance.stime;                       // Sum child process sleeping state time
        average_turnaround_time += (performance.ttime - performance.ctime);     // Sum child process turnaround time (termination time minus creation time)
        printf(1, "\n==============================\n\n");
        printf(1, "Process %d creation time: %d\n", pid, performance.ctime);
        printf(1, "Process %d running time: %d\n", pid, performance.rutime);
        printf(1, "Process %d sleeping state time: %d\n", pid, performance.stime);
        printf(1, "Process %d ready state time: %d\n", pid, performance.retime);
        printf(1, "Process %d termination time: %d\n", pid, performance.ttime);
        printf(1, "Process %d turnaround time: %d\n", pid, (performance.ttime-performance.ctime));
        printf(1, "\n==============================\n"); 
    }
    printf(1, "\n******************************************\n\n");
    printf(1, "Average running time: %d\n", average_running_time / iteration_definition);
    printf(1, "Average sleeping state time: %d\n", average_sleeping_state_time / iteration_definition);
    printf(1, "Average waiting time: %d\n", average_ready_state_time / iteration_definition);
    printf(1, "Average turnaround time: %d\n", average_turnaround_time / iteration_definition);
    printf(1, "\nApproximated percentage of time running: %d%%\n", (average_running_time * 100) / average_turnaround_time);
    printf(1, "Approximated percentage of time waiting: %d%%\n", (average_ready_state_time * 100) / average_turnaround_time);
    printf(1, "Approximated percentage of time sleeping: %d%%\n", (average_sleeping_state_time * 100) / average_turnaround_time);
    printf(1, "\n******************************************\n\n");
    return 0;
}
    
 
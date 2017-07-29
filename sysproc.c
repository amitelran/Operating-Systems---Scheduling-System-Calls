#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_wait_stat(void)             // TASK 3.5
{
    int status;
    struct perf *performance_stat;
    if (argint(0, &status) < 0)                 // argint assigns the status argument
    {
        return -1;
    }
    if (argptr(1, (void*)&performance_stat, sizeof(*performance_stat)) < 0)         // argptr assigns the perf structure pointer
    {
        return -1;
    }
    return wait_stat(&status, performance_stat);           
}
    
int
sys_priority(void)              // TASK 3.2
{
    int change_priority;
    argint(0, &change_priority);        // argint assigns the priority argument
    priority(change_priority);
    return 0;
}

int 
sys_policy(void)                // TASK 3.4
{
    int change_policy;
    if (argint(0, &change_policy) < 0)  // argint assigns the policy argument
    {
        return -1;
    }
    policy(change_policy);
    return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)                      // TASK 2.1
{   
    int exit_arg;
    if (argint(0, &exit_arg) < 0)   // argint assigns to exit_arg the exit status of the process
    {
        return -1;
    }
    exit(exit_arg);
    return 0;  // not reached
}

int
sys_wait(void)                      // TASK 2.2
{
    int  status;
    if(argint(0, &status) < 0)
    {
        return -1;                  // argint assigns to exit_arg the exit status of the process
    }
    return wait(&status);           
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

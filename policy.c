#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])            // TASK 3.4
{   
    if ((*argv[1] < '0' ) || (*argv[1] > '2')){             // Check for valid policy identifier
        printf(2, "Invalid policy identifier\n");
        exit(0);
    }
    int new_policy = atoi(argv[1]);
    policy(new_policy);
    printf(2, "Scheduler policy is now: %d\n", new_policy);
    exit(0);
}

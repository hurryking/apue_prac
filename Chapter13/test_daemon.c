#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void skeleton_daemon()
{
    pid_t pid;
    
    pid = fork(); // 1. fork off the parent process
    if (pid < 0) { 
        exit(EXIT_FAILURE); 
    } 
    if (pid > 0) { // 1. terminates the parent process
        exit(EXIT_SUCCESS); 
    } 
    if (setsid()<0) { // 2. child process becomes session leader
        exit(EXIT_FAILURE); 
    } 
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    pid = fork(); // 3. fork off the second time
    if (pid<0) { 
        exit(EXIT_FAILURE); 
    }
    if (pid>0) { // terminates the parents
        exit(EXIT_SUCCESS); 
    }

    umask(0); // 4. set new file permissions

    chdir("/"); // 5. change the working directory

    int x; // 6. close all open file descriptors
    for (x=sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close(x);
    }

    openlog("firstdaemon", LOG_PID, LOG_DAEMON);
}

int main()
{
    skeleton_daemon();
    while (1)
    {
        syslog(LOG_NOTICE, "First daemon started.");
        sleep(20);
        break;
    }

    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
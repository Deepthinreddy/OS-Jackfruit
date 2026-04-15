#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define STACK_SIZE 1024 * 1024

static char stack[STACK_SIZE];

// ================= CONTAINER =================
int container_main(void *arg) {
    char *name = (char *)arg;

    printf("Container [%s] started\n", name);

    chroot("rootfs");
    chdir("/");

    // create log file
    char logfile[100];
    sprintf(logfile, "%s.log", name);

    int fd = open(logfile, O_CREAT | O_WRONLY | O_APPEND, 0644);

    // redirect output
    dup2(fd, 1); // stdout
    dup2(fd, 2); // stderr

    execl("/bin/sh", "/bin/sh", NULL);

    perror("exec failed");
    return 1;
}

// ================= MAIN =================
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage:\n");
        printf("./engine start <name>\n");
        printf("./engine ps\n");
        printf("./engine logs <name>\n");
        return 1;
    }

    // START CONTAINER
    if (strcmp(argv[1], "start") == 0) {

        char *name = argv[2];

        pid_t pid = clone(container_main,
                          stack + STACK_SIZE,
                          CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD,
                          name);

        if (pid == -1) {
            perror("clone failed");
            exit(1);
        }

        printf("Started container %s (PID: %d)\n", name, pid);

        // save to file
        FILE *f = fopen("containers.txt", "a");
        fprintf(f, "%s %d\n", name, pid);
        fclose(f);
    }

    // LIST CONTAINERS
    else if (strcmp(argv[1], "ps") == 0) {

        FILE *f = fopen("containers.txt", "r");

        if (!f) {
            printf("No containers found\n");
            return 0;
        }

        char name[50];
        int pid;

        printf("NAME\tPID\n");

        while (fscanf(f, "%s %d", name, &pid) != EOF) {
            printf("%s\t%d\n", name, pid);
        }

        fclose(f);
    }

    // SHOW LOGS
    else if (strcmp(argv[1], "logs") == 0) {

        char filename[100];
        sprintf(filename, "%s.log", argv[2]);

        FILE *f = fopen(filename, "r");

        if (!f) {
            printf("No logs found\n");
            return 1;
        }

        char ch;
        while ((ch = fgetc(f)) != EOF)
            putchar(ch);

        fclose(f);
    }

    else {
        printf("Unknown command\n");
    }

    return 0;
}

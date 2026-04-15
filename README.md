# OS Project – Multi-Container Runtime

## Name: Deepthi N Reddy
SRN : PES2UG24CS149


## Name : Ganvai Purushothama
SRN : PES2UG24CS167
## Course: Operating Systems Lab  

---

# Task 1: Container Engine Implementation

## Objective  
To implement a simple container runtime using Linux namespaces and system calls.

## Code Used  
File: engine.c

## Compilation  
gcc engine.c -o engine

## Execution  
sudo ./engine start alpha  
./engine ps  

## Output  
Started container alpha (PID: 3410)

NAME    PID  
alpha   3410  

## Explanation  
The container engine uses the clone() system call with CLONE_NEWPID and CLONE_NEWUTS to create isolated environments. Each container runs as a separate process with its own PID namespace.

---

# Task 2: Running Multiple Containers

## Objective  
To create and manage multiple containers simultaneously.

## Execution  
sudo ./engine start alpha  
sudo ./engine start beta  
./engine ps  

## Output  
NAME    PID  
alpha   3410  
beta    3414  

## Explanation  
Multiple containers are created and tracked using process IDs. The ps command lists all active containers.

---

# Task 3: Logging Container Output

## Objective  
To capture and view container logs.

## Execution  
echo "hello from alpha" >> alpha.log  
./engine logs alpha  

## Output  
hello from alpha  

## Explanation  
Container logs are stored in files and can be retrieved using the logs command, simulating real container logging behavior.

---

# Task 4: Kernel Module Monitoring

## Objective  
To monitor container activity using a Linux kernel module.

## Files Used  
monitor.c  
Makefile  

## Compilation  
make  

## Load Module  
sudo insmod monitor.ko  

## Create Device  
sudo mknod /dev/container_monitor c 240 0  
sudo chmod 666 /dev/container_monitor  

## Verification  
sudo dmesg | tail  

## Output  
Monitor module loaded. Major: 240  

## Explanation  
The kernel module registers a character device and logs activity using kernel messages (dmesg). It demonstrates communication between user space and kernel space.

---

# Task 5: CPU Scheduling Experiment

## Objective  
To observe process scheduling using different priorities.

## Execution  
./cpu  

In another terminal:  
nice -n 10 ./cpu  

## Monitoring  
top  

## Output  
PID   NI   %CPU   COMMAND  
4252   0   98.0   cpu  
4260  10   98.7   cpu  

## Explanation  
The process with lower nice value (higher priority) is favored by the scheduler. This demonstrates Linux scheduling behavior.

---

# Task 6: Cleanup

## Objective  
To remove container metadata and logs.

## Execution  
rm -f containers.txt  
rm -f *.log  
./engine ps  

## Output  
No containers found  

## Explanation  
All container records and logs are removed to ensure proper cleanup and resource management.

---

# Conclusion  

This project demonstrates the implementation of a lightweight container runtime using Linux system calls, namespaces, and kernel modules. It provides insight into how container systems like Docker work internally.

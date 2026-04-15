# Multi-Container Runtime

Team Member 1 : Deepthi N Reddy
SRN : PES2UG24CS149

Team Member 2 : Ganavi Purushothama
SRN : PES2UG24CS167

Task 1: Container Engine Implementation
Objective

To implement a simple container runtime using Linux namespaces.

Code Used

File: engine.c

Compilation
gcc engine.c -o engine
Execution
sudo ./engine start alpha
sudo ./engine run alpha
./engine ps
Output
Starting container: alpha
Container alpha running in background (PID: 3410)

NAME    PID
alpha   3410
Explanation

The container engine uses clone() with CLONE_NEWPID and CLONE_NEWUTS to create isolated environments. Each container runs as a separate process with its own PID namespace.

Task 2: Running Multiple Containers
Objective

To create and manage multiple containers simultaneously.

Execution
sudo ./engine start alpha
sudo ./engine start beta
./engine ps
Output
NAME    PID
alpha   3410
beta    3414
Explanation

Multiple containers are created and tracked using process IDs. The ps command lists all running containers.

Task 3: Logging Container Output
Objective

To capture container output into log files.

Execution
echo "hello from alpha" >> alpha.log
cat alpha.log
Output
hello from alpha
Explanation

Logs are stored in files to simulate container logging behavior.

Task 4: Kernel Module Monitoring
Objective

To monitor container activity using a kernel module.

Files Used
monitor.c
Makefile
Compilation
make
Load Module
sudo insmod monitor.ko
Create Device
sudo mknod /dev/container_monitor c 240 0
sudo chmod 666 /dev/container_monitor
Execution
echo "test" > /dev/container_monitor
sudo dmesg | tail
Output
Monitor module loaded. Major: 240
Explanation

The kernel module creates a character device and logs activity using kernel messages.

Task 5: Process Monitoring
Objective

To observe running processes and system usage.

Execution
top
Output
PID USER  %CPU COMMAND
4260 deepthi 98.7 cpu
Explanation

The top command shows CPU usage and process activity in real-time.

Task 6: CPU Load Simulation
Objective

To simulate CPU-intensive workload.

Code Used

File: cpu.c

Compilation
gcc cpu.c -o cpu
Execution
./cpu
Output

(Continuous CPU usage visible in top)

Explanation

The program runs an infinite loop to generate CPU load, helping analyze scheduling behavior.

Conclusion

This project demonstrates containerization using Linux namespaces, kernel module interaction, and system monitoring. It provides a basic understanding of how container runtimes like Docker work internally.

Objective: 
Run a process which creates a child process, and check the order of execution, whether child process executes first or parent.

Run:
<code> bash run_test.sh </code>

Files:
execution_order_check.c -- creates a child process and outputs "child" if child process is terminating and prints "parent" if parent process is terminating

count_instance.py -- python script to count the number of times child is exectuted before parent (python 2)

run_test.sh -- bash script runs the c code 5000 times, outputs the content to a file, and calls the python script to count the number of instances

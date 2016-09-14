#!/bin/bash
	echo "compiling execution_order_check.c"
	gcc execution_order_check.c -o execution_order_check.out
	echo "Executing it 5000 times"
    for i in `seq 1 5000`;
    do
            ./execution_order_check.out >> execution_order_check.txt
            if (( $i % 4 == 0 ))
            then
            	
            	echo -ne "- \r"
            elif (( $i % 4 == 1 ))
            then
            	
            	echo -ne "| \r"
            elif (( $i % 4 == 2 ))
            then
            	
            	echo -ne "/ \r"
            else
            	
            	echo -ne "\ \r"
            fi
    done   

    python count_instance.py
    echo "Cleaning up"
    rm execution_order_check.txt
    rm execution_order_check.out
    echo "Exiting"
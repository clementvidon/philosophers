#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

helgrind_run()
{
    echo "========================================="
    echo "===============[helgrind run]============"
    echo "========================================="
    MAKE="make re helgrind_run"

    AV="1 800 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="5 800 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 310 200 100"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 310 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
}

valgrind_run()
{
    echo "========================================="
    echo "===============[valgrind run]============"
    echo "========================================="
    MAKE="make re valgrind_run"

    AV="1 800 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="5 800 200 200 7"
    echo " > philo " $AV
    sleep 0.5
    $MAKE AV="$AV";
    AV="4 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 310 200 100"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 310 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
}

san_thread()
{
    echo "========================================="
    echo "===============[san thread]=============="
    echo "========================================="
    MAKE="make fclean san_thread run"

    AV="1 800 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="5 800 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 310 200 100"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 310 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
}

san_addr()
{
    echo "========================================="
    echo "===============[san addr]================"
    echo "========================================="
    MAKE="make fclean san_addr run"

    AV="1 800 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="5 800 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 310 200 100"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 310 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
}

run()
{
    echo "========================================="
    echo "===============[run]====================="
    echo "========================================="
    MAKE="make run"

    AV="1 800 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="5 800 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="4 310 200 100"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 410 200 200 7"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
    AV="2 310 200 200"
    echo " > philo " $AV
    sleep 1
    $MAKE AV="$AV";
}

helgrind_run;
valgrind_run;
san_thread;
san_addr;
run;

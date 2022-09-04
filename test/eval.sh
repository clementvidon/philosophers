#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

helgrind_run()
{
    echo "========================================="
    echo "===============[helgrind run]============"
    echo "========================================="
    MAKE="make --no-print-directory re runv"

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="5 800 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 310 200 100"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 310 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
}

valgrind_run()
{
    echo "========================================="
    echo "===============[valgrind run]============"
    echo "========================================="
    MAKE="make re runv"

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="5 800 200 200 7"
    echo " > philo " $p
    sleep 0.5
    $MAKE p="$p";
    p="4 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 310 200 100"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 310 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
}

san_thread()
{
    echo "========================================="
    echo "===============[san thread]=============="
    echo "========================================="
    MAKE="make fclean sant run"

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="5 800 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 310 200 100"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 310 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
}

san_addr()
{
    echo "========================================="
    echo "===============[san addr]================"
    echo "========================================="
    MAKE="make fclean sana run"

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="5 800 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 310 200 100"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 310 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
}

run()
{
    echo "========================================="
    echo "===============[run]====================="
    echo "========================================="
    MAKE="make run"

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="5 800 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="4 310 200 100"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
    p="2 310 200 200"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";
}

helgrind_run;
valgrind_run;
san_thread;
san_addr;
run;

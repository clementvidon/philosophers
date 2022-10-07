#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

run()
{
    rule=$1
    echo "===[ $rule ]==="
    MAKE="make -j $rule"
    sleep 2

    p="1 800 200 200"
    echo " > philo " $p
    sleep 1
    echo ">>>$MAKE"
    $MAKE p="$p";
    echo "  >>> died <<<"
    sleep 2

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
    echo "  >>> died <<<"
    sleep 2

    p="2 410 200 200 7"
    echo " > philo " $p
    sleep 1
    $MAKE p="$p";

    p="2 310 200 200"
    echo " > philo " $p
    $MAKE p="$p";
    echo "  >>> died <<<"
    sleep 2
}

run "re hrun";
run "re vrun";
run "re tsan run";
run "re asan run";
run "re run";

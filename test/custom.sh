#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

makefile_rules()
{
    AV="4 310 200 200"

    echo "========================================="
    echo "===============[helgrind run]============"
    echo "========================================="
    make re helgrind_run AV="$AV";

    echo "========================================="
    echo "===============[valgrind run]============"
    echo "========================================="
    make re valgrind_run AV="$AV";

    echo "========================================="
    echo "===============[san thread]=============="
    echo "========================================="
    make fclean san_thread run AV="$AV";

    echo "========================================="
    echo "===============[san addr]================"
    echo "========================================="
    make fclean san_addr run AV="$AV";

    echo "========================================="
    echo "===============[make run]================"
    echo "========================================="
    make re run AV="$AV";
}

makefile_rules;

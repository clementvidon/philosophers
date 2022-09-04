#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

p=$1

echo "========================================="
echo "===============[helgrind run]============"
echo "========================================="
make --no-print-directory re runh p="$p";

echo "========================================="
echo "===============[valgrind run]============"
echo "========================================="
make --no-print-directory re runv p="$p";

echo "========================================="
echo "===============[san thread]=============="
echo "========================================="
make --no-print-directory fclean sant run p="$p";

echo "========================================="
echo "===============[san addr]================"
echo "========================================="
make --no-print-directory fclean sana run p="$p";

echo "========================================="
echo "===============[make run]================"
echo "========================================="
make --no-print-directory re run p="$p";

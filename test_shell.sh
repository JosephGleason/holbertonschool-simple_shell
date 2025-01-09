#!/bin/bash

# Compile the shell program
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
if [ $? -ne 0 ]; then
    echo "Compilation failed. Fix the errors and try again."
    exit 1
fi

echo "Compilation succeeded."

# Test PATH handling
echo "Testing PATH handling..."

# Test a command in PATH
echo "Testing 'ls' (should work if PATH is set correctly)..."
ls_output=$(echo "ls" | ./hsh)
if [[ $ls_output == "" ]]; then
    echo "Error: 'ls' not found or PATH not handled correctly."
else
    echo "'ls' executed successfully."
fi

# Test a fallback PATH
echo "Temporarily clearing PATH to test fallback..."
OLD_PATH=$PATH
export PATH=""
ls_fallback=$(echo "ls" | ./hsh)
if [[ $ls_fallback == "" ]]; then
    echo "Error: fallback PATH not working."
else
    echo "Fallback PATH executed 'ls' successfully."
fi
export PATH=$OLD_PATH

# Run other test commands
echo "Starting additional command tests. Press Ctrl+C to exit at any time."
echo "
ls
pwd
echo 'Hello, World!'
invalidcommand
/bin/ls
exit
" | ./hsh

echo "Shell execution test completed."


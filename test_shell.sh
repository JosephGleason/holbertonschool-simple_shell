#!/bin/bash

# Path to your shell program
SHELL_PROGRAM="./hsh"

# List of test commands to check
TEST_COMMANDS=(
    "ls"
    "pwd"
    "echo Hello"
    "cat /etc/passwd"
    "whoami"
    "date"
    "exit"
)

# Directories to check in the PATH
PATH_DIRS=$(echo $PATH | tr ':' ' ')

# Function to run a test command
run_test() {
    local command="$1"
    echo "Running command: $command"

    # Run the command in the custom shell and in the system shell for comparison
    echo -n "Output from your shell: "
    $SHELL_PROGRAM -c "$command"
    echo -n "Output from system shell: "
    bash -c "$command"

    echo "--------------------------------------------------"
}

# Test each command
for command in "${TEST_COMMANDS[@]}"; do
    run_test "$command"
done

# Test commands with full paths
for dir in $PATH_DIRS; do
    echo "Testing commands in directory: $dir"
    for command in "${TEST_COMMANDS[@]}"; do
        full_path="$dir/$command"
        if [ -x "$full_path" ]; then
            echo "Found $command in $dir"
        fi
    done
done


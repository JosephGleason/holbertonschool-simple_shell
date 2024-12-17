# Simple Shell Project

## Table of Contents
- [Project Overview](#project-overview)
- [Purpose](#purpose)
- [Main Features](#main-features)
- [Intended Audience](#intended-audience)
- [Supported Specifiers](#supported-specifiers)
- [Compilation Instructions](#compilation-instructions)
- [Language](#language)
- [Challenges](#challenges)
- [Reference](#reference)
- [Contributors](#contributors)
- [Project Tasks](#project-tasks)

## Project Overview

The Simple Shell project is a basic implementation of a Unix command-line interpreter. This shell allows users to execute commands in both interactive and non-interactive modes, similar to standard shells such as bash or sh. It demonstrates fundamental concepts in system programming, such as process creation, file handling, and memory management.

## Purpose

This project was developed as part of the Holberton School curriculum to:

- Enhance understanding of the C programming language.
- Explore system calls, such as `fork`, `execve`, and `wait`.
- Build knowledge of memory allocation and management.
- Learn about parsing user input and managing tokens.

## Main Features

- Displays a prompt and waits for user input in interactive mode.
- Executes commands with their arguments.
- Handles built-in commands, such as `exit`.
- Supports searching for executables in the `PATH` environment variable.
- Works in both interactive and non-interactive modes.
- Provides basic error handling and messages.

## Intended Audience

This project is intended for:

- Students and programmers learning C and Unix system programming.
- Developers interested in understanding shell implementations.
- Anyone looking to deepen their knowledge of operating systems and command-line interfaces.

## Supported Specifiers

The shell recognizes standard commands available in the system’s `PATH`.

Built-in commands supported include:

- `exit` to terminate the shell.

## Compilation Instructions

To compile the Simple Shell project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/simple_shell.git
    ```

2. Navigate to the project directory:
    ```bash
    cd simple_shell
    ```

3. Compile the program:
    ```bash
    gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
    ```

4. Run the shell:
    ```bash
    ./hsh
    ```

## Language

The project is written entirely in the C programming language (C90 standard).

## Challenges

During the development of this project, the following challenges were encountered:

- Parsing and tokenizing user input efficiently.
- Implementing process handling using system calls like `fork` and `execve`.
- Handling edge cases, such as invalid commands or malformed input.
- Managing memory allocation and avoiding leaks.

## Reference

For more information about Unix shells and system programming, see:

- UNIX Programming FAQ
- Linux Programmer’s Manual
- The C Programming Language

## Project Tasks

### 0. README, man, AUTHORS
- Write a README
- Write a man for your shell.
- Create an AUTHORS file listing all individuals contributing to the repository.

### 1. Betty would be proud
- Write a beautiful code that passes the Betty checks.

### 2. Simple shell 0.1
- Write a UNIX command line interpreter.
- The shell should display a prompt and wait for the user to type a command, executing that command when entered.
- The shell should handle errors, including cases where executables cannot be found.
- Handle the “end of file” condition (Ctrl+D).

### 3. Simple shell 0.2
- Handle command lines with arguments.

### 4. Simple shell 0.3
- Handle the PATH.
- `fork` must not be called if the command doesn’t exist.

### 5. Simple shell 0.4
- Implement the exit built-in command that terminates the shell.

### 6. Simple shell 1.0
- Implement the `env` built-in command that prints the current environment.

## Contributors

- Joseph Gleason Lopez
- Jean Carlo Carrion Caraballo


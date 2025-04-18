Simple Shell

▶ Introduction 
    The collaborators to create this simple Shell Terminal were Joseph Gleason and Kamila Sostre. The 
purpose of this project is to apply all the concepts learned for C language while executing a terminal. 
This was arranged in seven files to handle inputs, prompts and execution of the shell. A separate repository was made as the checker for each task that allows the terminal to fully function. 

▶ Description
  The Shell Terminal is a command interpreter that manages processes and uses an interface between the user and the operating system. It captures the users input and sends it to the shell and parses it into a command and arguments. The PATH environment variable is used to search for the executable command 
and, I/O commands to handle inputs and outputs. 

▶ Requisites
 
* Each file ends with a new line.
* The codes must be correctly checked with Betty style.
* There is no memory leaks
* Limited to 5 functions per file
* The header file must be guarded

▶ Protoypes and Functions

* void display_prompt(void);
* char *find_command(char *command);
* char **input_handler(char *line);
* int execute_shell(void);
* int second_handler(char **args);
* read
* write
* exit
* continue
* free
* malloc
* realloc
* perror
* args
* strtok
* isatty

▶ Usage

#include "shell.h"

void execute_command(char **args)
{
   pid_t pid;
   int status;

   pid = fork()
   
   if (pid == 0)
   
   {
         
         if (execve(args[0], args, environ) == -1)
         
        {
            
        perror("Error");
            
        exit(EXIT_FAILURE);
         
        }
   
   }
   
   else if (pid > 0)
   
   {
   
   waitpid(pid, &status, 0);
   
   }
   
   else
   
   {
   
     perror("Error");
   
   }

}


▶ Branches

* main
* Joe
* Kami

▶ Authors

[Joseph Gleason - https://github.com/JosephGleason]


[Kamila Sostre - https://github.com/kamisos3]

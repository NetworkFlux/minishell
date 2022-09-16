# -- minishell --

  

## Usage (mac only) -- 👈

  

```bash

git clone https://github.com/NetworkFlux/minishell.git && cd minishell && make && ./minishell

```

  

## Topics -- 🗝

  

1. Bash

  

2. Shell

  

3. Interpreter

  

4. C

  

  

## Challenge -- 💡

  

  

This project is about creating a simple shell.

  

  

## Objectives -- ✅

  

  

This program is supposed to mimic a functioning terminal and able to execute practically every command. This terminal should handel piping aswell as file redirections.

- Extensive parsing
- Piping
- Redirections
- Environment variables
  
  

## Rules -- 🚨

  

This is what this shell does :
 
-   Have a working history.
-   Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
-   Not interpret unclosed quotes.
-   Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
-   Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
-  Implement redirections:
-   Implement pipes.
-   Handle environment variables.
-   Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
-   Your shell must implement the following builtins:
    ◦ echo with option -n  
    ◦ cd with only a relative or absolute path ◦ pwd with no options  
    ◦ export with no options  
    ◦ unset with no options  
    ◦ env with no options or arguments  
    ◦ exit with no options
  
  

👍 Thanks to [fcaquard](https://github.com/fqrd "fcaquard GitHub") for his help, we did this together ! 👍
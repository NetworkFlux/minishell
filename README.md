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
This program is supposed to mimic a functioning terminal and be able to execute practically every command. This terminal should handel piping aswell as file redirections.
- Extensive parsing
- Piping
- Redirections
- Environment variables

## Rules -- 🚨
This is what this shell does :
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not interpret unclosed quotes.
- Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
- Implement pipes.
- Handle environment variables.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- This shell must implement the following builtins:
	- echo
	- cd
	- export
	- unset
	- env
	- exit

## Help -- ⏳
You might get this error at compilation :

<img src="https://github.com/NetworkFlux/minishell/blob/main/imgs/compile_error.png">

For this program to work you need to have readline on you computer. I personally use [brew](https://brew.sh/index_fr "Brew Site") as packet manager. In order to install readline with brew use the following command :

```bash
brew install readline
```

Now readline installed, you will need to find the path to readline which will be given by :

```bash
brew info readline
```

With readline finally working copy LDFLAGS and CPPFLAGS and paste it in the makefile at line 75 (2 lasts links).

👍 Thanks to [fcaquard](https://github.com/fqrd "fcaquard GitHub") for his help, we did this together ! 👍
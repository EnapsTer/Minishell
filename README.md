# Minishell
The objective of this project is to create a simple shell. Yes, own little bash or zsh.

## Launch

```bash
git clone https://github.com/EnapsTer/Minishell.git minishell && cd minishell

make && ./minishell
```

### What is released
* Builtins
  * echo with option ’-n’
  * cd with only a relative or absolute path
  * pwd
  * export
  * unset
  * env
  * exit
* Prompt like in bash
* Searching and launching the right executable (based on the PATH variable or by using
relative or absolute path) like in bash
* ; ' " works like in bash
* Pipes "|" and redirections " > >> < "
* Environment variables
* Signals ctrl-C, ctrl-D and ctrl-\

![alt-текст](https://github.com/EnapsTer/Minishell/blob/main/screenshots/prompt-screen.png "screenshot")

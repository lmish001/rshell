# rshell
rshell is a command shell in C++ that executes bash commands located in /src/bin. There is also an ‘exit’ built-in command that closes the rshell, and a 'test' command to see if a file or directory exists.
The program can execute single commands or various commands linked by connectors. The connectors that can follow a command:
-	`;`	always executed the command that comes after it	
-	`&&`	only executes the next command if the previous one executed successfully
-	`||`	only executes the next command if the previous one failed to execute
There is no limit to the number of commands that can be chained together.  If a connector does not have a command that follows it, the previous command will not get executed (`ls  ;`).
A user can also write comments. Each comment begins with `#`, and the program will not execute anything that comes after that.

# `test` command
The user can run the `test` command either using the keyword `test`:
`$ test -e test/file/path`
or using the symbolic version of the command:
`$ [ -e test/file/path ]`

The `test` command accepts the following flags:
- `-e` checks if the file/directory exists
- `-f` checks if the file/directory exists and is a regular file
- `-d` checks if the file/directory exists and is a directory
If the user does not specify a flag, the -e functionality will be used by default. If the command evaluates the check to be true, it will print out `(True)`. Otherwise, it will print out `(False)`.

# Precedence Operators
Parentheses `()` are used as precedence operators to change the precedence of the connectors in rshell. For example:
Input without parentheses: `echo a && echo b || echo c && echo d` 
Output: `a  b  d `
Input with parentheses: `(echo a && echo b) || (echo c && echo d)` 
Output: `a  b`

# Output Redirection
`>` and `>>` is used for output redirection. `>` will overwrite an existing file, or create a new one if it doesn't exist. `>>` will append to an existing file or create a new one if it doesn't exist.

# Input Redirection
Using `<`, commands can get input from the specified file.

# Piping
The output of one command can be used as input for the next one using piping. For example:
`ls | sort | grep a`


# Repository structure
-	src/ contains the .cpp files and the header. 
-	tests/ contains bash scripts for testing the code (and the input files with the tests cases)
To run the program, input the following commands:
```
$ git clone https://github.com/lmish001/rshell.git
$ cd rshell
$ git checkout hw4
$ make
$ bin/rshell
```

To run the tests, input tests/<name_of_test_cases>.sh while in the rshell directory. Currently there are 4 test scripts:
- `commented_command.sh`
- `single_command.sh`
- `multiple_commands.sh`
- `exit_command.sh`
- `test_test.sh`
- `precedence_test.sh`
- `commented_command.sh`
- `exit.sh`
- `input_redir.sh`
- `io_redir.sh`
- `io_syntax.sh`
- `output_redir.sh`
- `pipe.sh`

# Known bugs
- Piping has not been combined to work with input/output redirection 

#Fixed Bugs
- The shell doesn't exit after presing 'Enter
- If a command is trying to delete a directory/file that does not exist, rshell no longer treats it as a successfully executed command.

Synopsis:
This program is building a command shell called rshell.
1. Print a command prompt (e.g. $)
2. Read in a command on one line. Commands will have the form:
  cmd = executable [ argumentList ] [ connector cmd ]
  connector = || or && or ;
where executable is an executable program in the PATH and argumentList is a list of zero
or more arguments separated by spaces. The connector is an optional way you can run multiple
commands at once. If a command is followed by ;, then the next command is always executed;
if a command is followed by &&, then the next command is executed only if the first one
succeeds; if a command is followed by ||, then the next command is executed only if the first
one fails. For example:
  $ ls -a
  $ echo hello
  $ mkdir test
    is equivalent to:
  $ ls -a; echo hello; mkdir test
There should be no limit to the number of commands that can be chained together using these
operators, and your program must be able to handle any combination of operators. For
example, you should be able to handle the command:
  $ ls -a; echo hello && mkdir test || echo world; git status
3. command of exit which exits your shell
4. Anything that appears after a # character should be considered a comment. 

Running the program:
  $ git clone https://github.com/yourusername/rshell.git
  $ cd rshell
  $ git checkout hw1
  $ make
  $ bin/rshell
  
Tests for the program:
The .sh files have been chmod when you makefile. So the only thing you need to do is running the .sh files in Directory tests.(For example: tests/exit.sh or ./exit.sh)

Limits:
If any blank space appears between commands and connectors, the program will crush.

Contributors:
Zhenyu Hu
rrrrain.z@gmail.com

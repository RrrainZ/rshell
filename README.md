Synopsis:

1.The Test Command
add the test command to your rshell, as well as its symbolic
equivalent [ ]. The square brackets [ ] are actually set up as the test command in bash, you can
read about it here and try it out on your own. This command returns 0 (TRUE) if the test
succeeds and 1 (FALSE) if the test fails. This command is very useful for writing conditions that
can be combined with && and || to write more complex bash command structures.

$ test ­e /test/file/path
$ [ ­e /test/file/path ]

-e checks if the file/directory exists
-f checks if the file/directory exists and is a regular file
-d checks if the file/directory exists and is a directory

If the command test ­e /test/file/path evaluates to True, then print display the following
(True)
And likewise, if the above command evaluates to False, then print False in the same manner
(False)

Additionally, test command should work with the connectors && and || that you have written
previously in assignment 2, as well as all other functionality from assignment 2.
$ test ­e /test/file/path && echo “path exists”
­ or ­
$ [ ­e /test/file/path ] && echo “path exists”

(True)
path exists

2.The Precedence Operators

add parentheses to change the precedence of the connectors
$ (echo A && echo B) || (echo C && echo D)
which would print
A
B
This is because the parentheses change the precedence, so that when (echo A && echo B)
returns true (since it execute correctly) to the || operator then it will not run the entire group
(echo C && echo D) since the parentheses have now grouped these commands together. Note
that if for some reason echo A failed, echo B would not execute, and (echo C && echo D) would
be executed.


Running the program:

  $ git clone https://github.com/yourusername/rshell.git
  $ cd rshell
  $ git checkout hw2
  $ make
  $ bin/rshell
  
Tests for the program:

The .sh files have been chmod when you makefile. So the only thing you need to do is running the .sh files in Directory tests.(For example: tests/exit.sh or ./exit.sh)

Limits:

When any blank space places between '()' and '#', there will be a crush.
When any blank space places at first space, there will be a crush.
When command have nested '()' like (...(...)), there will be a crush.

Contributors:

Zhenyu Hu
rrrrain.z@gmail.com

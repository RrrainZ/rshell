#!/bin/sh
echo "ls -a;echo hello||echo world&&git status#ls"
./rshell << EOF
ls -a;echo hello||echo world&&git status#ls
exit
EOF

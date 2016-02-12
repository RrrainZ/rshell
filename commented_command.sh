#!/bin/sh
echo "ls -a;echo hello||echo world&&git status#ls"
./a.out << EOF 
ls -a;echo hello||echo world&&git status#ls
exit
EOF

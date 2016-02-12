#!/bin/sh
echo "ls -a"
echo "echo hello"
echo "git status"
./a.out << EOF
ls -a
echo hello
git status
exit
EOF

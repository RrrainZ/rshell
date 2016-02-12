#!/bin/sh
echo "ls -a"
echo "exit"
./rshell << EOF
ls -a
exit
EOF

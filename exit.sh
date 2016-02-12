#!/bin/sh
echo "ls -a"
echo "exit"
./a.out << EOF
ls -a
exit
EOF

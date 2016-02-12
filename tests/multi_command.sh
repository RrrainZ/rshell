#!/bin/sh
echo "ls -a;echo hello&&mkdir test||echo world;git status"
./rshell << EOF
ls -a;echo hello&&mkdir test||echo world;git status
exit
EOF

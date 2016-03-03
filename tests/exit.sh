#!/bin/sh
echo "(test -e ./test/Zhenyu_625503.txt && echo B) || (echo C && echo D)"
echo "exit"
./rshell << EOF
(test -e ./test/Zhenyu_625503.txt && echo B) || (echo C && echo D)
exit
EOF

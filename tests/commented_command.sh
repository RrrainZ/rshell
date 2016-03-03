#!/bin/sh
echo "(test -e ./test/Zhenyu_625503.txt && echo B) || (echo C && echo D)# echo "path exists""
echo "[ -e ./test/Zhenyu_625503.txt ] # echo “path exists”"
./rshell << EOF
(test -e ./test/Zhenyu_625503.txt && echo B) || (echo C && echo D)# echo "path exists"
[ -e ./test/Zhenyu_625503.txt ] # echo “path exists”
exit
EOF

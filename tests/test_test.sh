#!/bin/sh
echo "test -e ./test/Zhenyu_625503.txt"
echo "test -d ./test/Zhenyu_625503.txt"
echo "test -f ./test/Zhenyu_625503.txt"
echo "[ -e ./test/Zhenyu_625503.txt ]"
echo "test -e ./test/Zhenyu_625503.txt && echo “path exists”"
echo " [ -e ./test/Zhenyu_625503.txt ] && echo “path exists”"
./rshell << EOF
test -e ./test/Zhenyu_625503.txt
test ­-d ./test/Zhenyu_625503.txt
test ­-f ./test/Zhenyu_625503.txt
[ -e ./test/Zhenyu_625503.txt ]
test -e ./test/Zhenyu_625503.txt && echo “path exists”
[ -e ./test/Zhenyu_625503.txt ] && echo “path exists”
exit
EOF
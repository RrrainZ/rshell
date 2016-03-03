#!/bin/sh
echo "(echo A && echo B) || (echo C && echo D)"
echo "(echo A && echo B) || (echo C && echo D"
./rshell << EOF
(echo A && echo B) || (echo C && echo D)
(echo A && echo B) || (echo C && echo D
exit
EOF

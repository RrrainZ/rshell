all: rshell
rshell:
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o tests/rshell
	chmod +x tests/commented_command.sh
	chmod +x tests/exit.sh
	chmod +x tests/test_test.sh
	chmod +x tests/precedence_test.sh

clean:
	rm -rf bin/

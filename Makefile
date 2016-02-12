all: rshell
rshell:
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/main1.cpp -o bin/rshell
	g++ -Wall -Werror -ansi -pedantic src/main1.cpp -o tests/rshell
	chmod +x tests/commented_command.sh
	chmod +x tests/exit.sh
	chmod +x tests/multi_command.sh
	chmod +x tests/single_command.sh

clean:
	rm -rf bin/

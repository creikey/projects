exec_name=projects

.PHONY: clean

make_path=$(shell pwd)
install_path=$(make_path)/install.sh
exec_path=$(make_path)/$(exec_name)
objects=main.o prj_parser.o

$(exec_name): $(objects)
	gcc $(objects) -o $(exec_name)

debug: $(objects)
	gcc $(objects) -o $(exec_name) -g

main.o: main.c
	gcc -c main.c

prj_parser.o: prj_parser.c prj_parser.h
	gcc -c prj_parser.c

clean:
	-rm $(objects)
	-rm $(exec_name)
	-rm *.gch


exec_name=prj

.PHONY: clean

make_path=$(shell pwd)
install_path=$(make_path)/install.sh
exec_path=$(make_path)/$(exec_name)
objects=main.o

$(exec_name): $(objects)
	gcc $(objects) -o $(exec_name)

main.o: main.c
	gcc -c main.c

clean:
	-rm $(objects)
	-rm $(exec_name)


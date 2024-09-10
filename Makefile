
EXECUTABLE = bmp
SOURCES = bmp.c serial.c

all: build run

build: ./obj
	@gcc -Wall -Wextra -std=c11 -ggdb -g ${SOURCES} -o ${EXECUTABLE}

./obj:
	@mkdir obj

run:
	@./${EXECUTABLE}

clean:
	@rm -rf a.out
	@rm -rf ${EXECUTABLE}

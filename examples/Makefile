COMPILER = gcc
COMPILER_FLAGS = -g -Wall -Werror
LINKER_FLAGS = -lncursesw -lm

PROG_NAME = dots
SOURCE_FILES = $(wildcard ../src/*.c) \
       		   $(wildcard ../examples/*.c)

prog:
	$(COMPILER) -o $(PROG_NAME) $(SOURCE_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS)
clean:
	rm dots
CC = gcc
CFLAGS = -m32 -O2 -Wall -Werror -fno-builtin
CFLAGS += ________  # TODO: Add an option here to add the directory
                    # "myloader/include" to search for header files.
ASFLAGS = -m32
 
CSRC = ________  # TODO: Find all .c files under the "loader/src" directory.
 
OBJS = ________  # TODO: Convert the suffix of all string in $(CSRC) into ".o".
 
loader: ________  # TODO: Add prerequisites for creating the loader.
	ld -o loader -e start -Ttext 0x100000 -m elf_i386 src/start.o $(OBJS)
 
clean:
	________  # TODO: Add command to remove all compile results.
include ../../Makefile.defs

.DEFAULT_GOAL:=all

all: char_by_char load_full_file blocks string_blocks

char_by_char: char_by_char.c setup
	$(CC) $(CCFLAGS) char_by_char.c -o $(BIN)/char_by_char

load_full_file: load_full_file.c setup
	$(CC) $(CCFLAGS) load_full_file.c -o $(BIN)/load_full_file

blocks: blocks.c setup
	$(CC) $(CCFLAGS) blocks.c -o $(BIN)/blocks

string_blocks: string_blocks.c setup
	$(CC) $(CCFLAGS) string_blocks.c -o $(BIN)/string_blocks
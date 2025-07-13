# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pedantic -O3 -fno-fast-math 
LDFLAGS = -lgmp -lmpfr

# Targets
TARGET = main
# Source files
SRC = main.c
# Object files
OBJ = $(SRC:.c=.o)
# Assembly file
ASM = $(SRC:.c=.s)
# Header files
HDR = $(wildcard *.h)
# Include directories
INCLUDES = -I.
# Compiler flags for header files
HDR_CFLAGS = $(addprefix -I,$(INCLUDES))
# Compiler flags for object files
OBJ_CFLAGS = $(addprefix -c,$(HDR_CFLAGS))
# Compiler flags for assembly files
ASM_CFLAGS = $(addprefix -S,$(HDR_CFLAGS))
# Compiler flags for all files
ALL_CFLAGS = $(CFLAGS) $(HDR_CFLAGS)
# Compiler flags for object files
OBJ_CFLAGS = $(CFLAGS) $(HDR_CFLAGS)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): main.o
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile main.c with header dependency
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Generate assembly code (main.s) from main.c
asm:
	$(CC) $(CFLAGS) -S main.c -o main.s

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

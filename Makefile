# Makefile for Coursework project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -O0

# Linker flags
LDFLAGS = -lm

# Source files
SRC = main.c time_measurement/time_measurement_processing.c time_measurement/time_measurement_processing.h settings.h user_interface/menu.c user_interface/menu.h user_interface/spreadsheet.c user_interface/spreadsheet.h time_measurement/measure_options.c time_measurement/measure_options.h algorithms/select_6_sorting.c algorithms/select_6_sorting.h algorithms/common_array.c algorithms/common_array.h algorithms/hybrid_select_1_exchange.c algorithms/hybrid_select_1_exchange.h algorithms/shell_1_sorting.c algorithms/shell_1_sorting.h algorithms/memory_access_test.c algorithms/memory_access_test.h

# Object files
OBJ = $(SRC:.c=.o)

# Executable file
EXECUTABLE = Coursework

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)
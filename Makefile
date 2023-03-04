CC = gcc
CFLAGS = -std=c11 -O3 -lm

SRCS = main.c \
       time_measurement/time_measurement_processing.c \
       user_interface/menu.c \
       user_interface/spreadsheet.c \
       time_measurement/measure_options.c \
       algorithms/select_6_sorting.c \
       algorithms/common_array.c \
       algorithms/hybrid_select_1_exchange.c \
       algorithms/shell_1_sorting.c

OBJS = $(SRCS:.c=.o)

EXEC = Course_work

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
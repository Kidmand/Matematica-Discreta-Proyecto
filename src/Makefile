CC := gcc

CFLAGS  := -O3 -Wall -Wextra -Wno-unused-parameter -std=c99
G := -g
SOURCES := $(wildcard *.c)
OBJECTS := $(filter-out MainParte2.c,$(SOURCES:.c=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(G) -o $@.out $(filter-out MainParte2.o,$^)

mainParte2: $(OBJECTS)
	$(CC) $(CFLAGS) $(G) -o MainParte2.out MainParte2.c $(filter-out MainParte2.o,$^)

test: $(OBJECTS)
	$(CC) $(CFLAGS) $(G) -o $(FILE:.c=).out $(FILE) $(filter-out MainParte2.o,$^)
	@echo "\n------------------------------------------------------\n"
	@echo "Ejecutando test:\n"
	./$(FILE:.c=).out

test-compile: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(FILE:.c=).out $(FILE) $(filter-out MainParte2.o,$^)

test-valgrind: $(OBJECTS)
	@echo "Ejecutando test con valgrind:\n"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(FILE)

test-callgrind: $(OBJECTS)
	@echo "Ejecutando test con callgrind:\n"
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./$(FILE)


fast_test: $(OBJECTS)
	$(CC) $(CFLAGS) $(G) -o ./tests/fast.test.out ./tests/fast.test.c
	@echo "\n------------------------------------------------------\n"
	@echo "Ejecutando fast.test:\n"
	./tests/fast.test.out

clean:
	rm -f *.o *.out ./tests/*.out

.PHONY: run clean test

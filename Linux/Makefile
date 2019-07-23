CC = g++
CFLAGS = -O2
LFLAGS = -s
BIN = bin/secstats
OBJ = obj/main.o obj/csv.o obj/stats.o
DIRS = obj bin

$(shell mkdir -p $(DIRS))

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

obj/main.o: src/main.cpp src/csv.hpp src/stats.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/csv.o: src/csv.cpp src/csv.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/stats.o: src/stats.cpp src/stats.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)

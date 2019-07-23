CC = cl.exe
CFLAGS = /EHsc /c /O2
LFLAGS =
EXE = bin\secstats
OBJ = obj\main.obj obj\csv.obj obj\stats.obj

$(EXE): $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) /Fe$@

obj\main.obj: src\main.cpp src\stats.hpp src\csv.hpp
	$(CC) $(CFLAGS) src\main.cpp /Fo$@
	
obj\stats.obj: src\stats.cpp src\stats.hpp
	$(CC) $(CFLAGS) src\stats.cpp /Fo$@
	
obj\csv.obj: src\csv.cpp src\csv.hpp
	$(CC) $(CFLAGS) src\csv.cpp /Fo$@	

.PHONY : clean
clean:
	del $(EXE) $(OBJ)


SRC=src/main.cpp src/psik.cpp
INC=-Iinclude
LDFLAGS=-lraylib -lbox2d

INCS:= $(wildcard include/*.h)

mortal: $(SRC) $(INCS)
	clang++ $(INC) -o $@ $(SRC) $(LDFLAGS)
 

.PHONY: run
run: mortal
	./mortal

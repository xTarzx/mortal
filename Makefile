
SRC=main.cpp
INC=-Iinclude
LDFLAGS=-lraylib -lbox2d

mortal: $(SRC)
	clang++ $(INC) -o $@ $(SRC) $(LDFLAGS)
 

.PHONY: run
run: mortal
	./mortal

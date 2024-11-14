
SRC=src/main.cpp src/psik.cpp src/pose.cpp src/serialize.cpp
INC=-Iinclude
LDFLAGS=-lraylib -lbox2d

INCS:= $(wildcard include/*.h)

mortal: $(SRC) $(INCS)
	clang++ $(INC) -o $@ $(SRC) $(LDFLAGS)
 

.PHONY: run clean
run: mortal
	./mortal

clean:
	rm ./mortal
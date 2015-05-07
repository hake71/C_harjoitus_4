CC= gcc
CFLAGS= -Wall -I.
EXE_NAME=Laskin
FILES= laskin.c
INCLUDE = 

all: $(FILES) $(INCLUDE)
	clear
	$(CC) -o $(EXE_NAME) $(FILES)  $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXE_NAME)
	
run:
	./$(EXE_NAME) 12 + 23

run2:
	./$(EXE_NAME) 10 + 24 x 32 + 24
	
rebuild: clean all

build: clean all run

build2: clean all run2

SRC1 = Code7_1001639122.c
SRC2 = BSTLib.c
SRC3 = QueueLib.c
SRC4 = StackLib.c
SRC5 = ListLib.c
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
OBJ4 = $(SRC4:.c=.o)
OBJ5 = $(SRC5:.c=.o)
EXE = $(SRC1:.c=.e)

HFILES = BSTLib.h QueueLib.h StackLib.h ListLib.h

CFLAGS = -g

all : $(EXE)

$(EXE): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)
	gcc $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) -o $(EXE) 

$(OBJ1) : $(SRC1) $(HFILES)
	gcc -c $(CFLAGS) $(SRC1) -o $(OBJ1) 

$(OBJ2) : $(SRC2) $(HFILES) 
	gcc -c $(CFLAGS) $(SRC2) -o $(OBJ2)

$(OBJ3) : $(SRC3) $(HFILES) 
	gcc -c $(CFLAGS) $(SRC3) -o $(OBJ3)

$(OBJ4) : $(SRC4) $(HFILES) 
	gcc -c $(CFLAGS) $(SRC4) -o $(OBJ4)

$(OBJ5) : $(SRC5) $(HFILES) 
	gcc -c $(CFLAGS) $(SRC5) -o $(OBJ5)



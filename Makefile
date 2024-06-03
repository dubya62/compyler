
CC := gcc -O3
OBJ := gcc -c -O3
DBG := gcc -g

OBJECTS := str.o sint.o darr.o stack.o main.o dtype.o dictionary.o
all: $(OBJECTS)
	echo "All object files created."

# test
main.o: main.c
	$(OBJ) -o $@ $<

main: $(OBJECTS)
	$(CC) -o $@ $^

# dictionary
dictionary.o: dictionary.c dictionary.h
	$(OBJ) -o $@ $<

dictionary: dictionary.o
	$(CC) -o $@ $^

# dtype
dtype.o: dynamic_type.c dynamic_type.h
	$(OBJ) -o $@ $<

dtype: dtype.o
	$(CC) -o $@ $^

# str
str.o: str.c str.h
	$(OBJ) -o $@ $<

str: str.o
	$(CC) -o $@ $^


# sint
sint.o: sint.c sint.h
	$(OBJ) -o $@ $<

sint: sint.o
	$(CC) -o $@ $^


# dynamic array
darr.o: dynamic_array.c dynamic_array.h
	$(OBJ) -o $@ $<

darr: darr.o dtype.o
	$(CC) -o $@ $^

# stack
stack.o: stack.c stack.h
	$(OBJ) -o $@ $<

stack: stack.o dynamic_array.o dtype.o
	$(CC) -o $@ $^

# clean
clean:
	rm -f $(basename $(OBJECTS))
	rm -f $(OBJECTS)
	rm -f gmon.out


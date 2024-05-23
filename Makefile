
all:
	echo "All dependencies gathered."

str: str.c str.h
	gcc -o str str.c -O3

debug: str.c str.h sint.c sint.h
	gcc -o str str.c -g
	gcc -o sint sint.c -g

sint: sint.c sint.h
	gcc -o sint sint.c -O3

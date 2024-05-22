
all:
	echo "All dependencies gathered."

str: str.c str.h
	gcc -o str str.c -O3

debug: str.c str.h
	gcc -o str str.c -g

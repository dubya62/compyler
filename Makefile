
all:
	echo "All dependencies gathered."

str: str.c str.h
	gcc -o str str.c -O3

debug: str.c str.h sint.c sint.h dynamic_array.c dynamic_array.h
	gcc -o str str.c -g
	gcc -o sint sint.c -g
	gcc -o darr dynamic_array.c -g

sint: sint.c sint.h
	gcc -o sint sint.c -O3

darr: dynamic_array.c dynamic_array.h
	gcc -o darr dynamic_array.c -O3

clean:
	rm -f str
	rm -f sint
	rm -f darr

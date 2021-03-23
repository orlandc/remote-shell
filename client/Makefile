client: tcp.o leercadena.o
	gcc -o client client.c tcp.o leercadena.o

tcp.o:
	gcc -c tcp.c

leercadena.o:
	gcc -c leercadena.c

clean:
	rm -f tcp.o client leercadena.o tcp.o 
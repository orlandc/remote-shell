server: tcp.o leercadena.o
	gcc -o server server.c tcp.o leercadena.o

tcp.o:
	gcc -c tcp.c

leercadena.o:
	gcc -c leercadena.c

clean:
	rm -f tcp.o server leercadena.o tcp.o
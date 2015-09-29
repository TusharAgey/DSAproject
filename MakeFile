try: list.o Techna.o main.o
	cc *.o -o project
list.o: list.c 
	cc list.c -c
Techna.o: list.c Techna.c
	cc list.c -c
	cc Techna.c -c
main.o: main.c list.c Techna.c
	cc list.c -c
	cc Techna.c -c
	cc main.c -c

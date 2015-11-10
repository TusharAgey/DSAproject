try: list2.o list.o Techna.o main.o
	cc *.o -o project
	clear
	./project
list.o: list.c 
	cc list.c -c
list2.o: list2.c 
	cc list2.c -c
Techna.o: list.c Techna.c
	cc Techna.c -c
main.o: main.c list.c Techna.c
	cc main.c -c


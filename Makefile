livraison: main.o liste_arete.o sommet.o
	gcc -o livraison main.o liste_arete.o sommet.o
main.o: main.c
	gcc -c -Wall main.c
liste_arete.o: liste_arete.c
	gcc -c -Wall liste_arete.c
sommet.o: sommet.c
	gcc -c -Wall sommet.c
clean:
	rm *.o livraison

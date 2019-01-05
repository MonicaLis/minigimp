
# Dans un fichier makefile, on peut utiliser de variables.
# monvar = valeur    pour affecter
# $(monvar)          pour recuperer la valeur

# De plus, il y a quelques variables internes, qu'on peut utiliser:
# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances


CC=gcc
CFLAGS=-Wall 


bin/minigimp: main.o ppm.o image.o pixel.o histo.o filter.o
		$(CC) -o $@ $^

main.o: src/main.c src/image.h src/ppm.h
	$(CC) -o $@ -c $< $(CFLAGS)

image.o: src/image.c src/image.h 
	     $(CC) -o $@ -c $< $(CFLAGS)

pixel.o: src/pixel.c src/pixel.h 
	     $(CC) -o $@ -c $< $(CFLAGS)

ppm.o: src/ppm.c src/ppm.h 
	     $(CC) -o $@ -c $< $(CFLAGS)

histo.o: src/histo.c src/histo.h 
	     $(CC) -o $@ -c $< $(CFLAGS)

filter.o: src/filter.c src/filter.h 
	     $(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

# mais en plus, on va effacer les fichiers .o

# On peut en faire encore plus ; dans certains cas, par exemple, certains
# regles peuvent etre omis, cars définis implicitement.
#
# Si vous voulez en connaitre plus, pour l'instant, cherchez en ligne.
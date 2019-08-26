# ssdsim linux support
all:ssd 
	
clean:
	rm -f ssd *.o *~
.PHONY: clean

ssd: ssd.o avlTree.o flash.o initialize.o pagemap.o avlTree.o
	gcc -w -g -o ssd ssd.o avlTree.o flash.o initialize.o pagemap.o -lm 
ssd.o: ssd.c flash.o
	gcc -w -c -g ssd.c  
flash.o: flash.c initialize.o 
	gcc -w -c -g flash.c
initialize.o: initialize.c avlTree.o pagemap.o 
	gcc -w -c -g initialize.c
pagemap.o: pagemap.c initialize.h
	gcc -w -c -g pagemap.c
avlTree.o: avlTree.c avlTree.h
	gcc -w -c -g avlTree.c


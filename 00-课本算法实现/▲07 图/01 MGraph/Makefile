objects = MGraph-main.o  MGraph.o	 LinkQueue.o Scanf.o

main: $(objects)
	gcc -o main $(objects)


MGraph-main.o:    	MGraph-main.c	
MGraph.o:         	MGraph.c          	MGraph.h
LinkQueue.o:		LinkQueue.c 	 	LinkQueue.h
Scanf.o:			Scanf.c

.PHONY:clean
clean:
	rm main $(objects)

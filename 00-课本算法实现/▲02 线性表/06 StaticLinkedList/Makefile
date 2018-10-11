objects = StaticLinkedList-main.o  StaticLinkedList.o	 

main: $(objects)
	gcc -o main $(objects)

StaticLinkedList-main.o:    	StaticLinkedList-main.c     	
StaticLinkedList.o:         	StaticLinkedList.c          	StaticLinkedList.h

.PHONY:clean
clean:
	rm main $(objects)




#FINAL NAME 4
all: listen_up

#MAKING EXICUTIBLES
listen_up: Song.o SLL.o main.o BST.o listenHeap.o
	g++ Song.o main.o -o listen_up
      #--eventually need to add main, BST, Heap
      
#KEEP DA O'S by Tyler the Creator
main.o: main.cpp
	g++ -c main.cpp

Song.o: Song.cpp Song.h
	g++ -c Song.cpp
	
SLL.o: SLL.cpp SLL.h
	g++ -c SLL.cpp
	
BST.o: BST.cpp BST.h 
	g++ -c BST.cpp
	
listenHeap.o: listenHeap.cpp listenHeap.h
	g++ -c listenHeap.cpp
	
#ITS SPRING YOU KNOW WHAT THAT MEANS
clean:
	rm -f *.o listen_up

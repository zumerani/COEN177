/*
	
	Zain Umerani
	COEN 177 - Lab Three
	
	deque.h

	 
	Description:
	Header file for deque.cpp implementation. Lists all the function prototypes for deque.c and ultimately to be used for
    LRU, LFU, Clock, and Second-Chance.
	 

*/

# ifndef DEQUE_H
# define DEQUE_H

class Deque {
    int count;
    class node* head;
	class node* clockPointer;
	

public:
    Deque();
    ~Deque();
    int size();
    void addFirst(int x);
    void addLast(int x);
    int removeFirst();
    int removeLast();
    int getFirst();
    int getLast();
	void print();
	class node* find(int val);
	void setTime(int val, int clock);
	void timeSetLast(int clock);
	void removeOldest();
	void setReferenceBit(int val);
	void moveBack(int val);
	int getFirstReference();
	void removeLFU();
	void clockChangeHand();
    void removeRandom();
};

# endif /* DEQUE_H */

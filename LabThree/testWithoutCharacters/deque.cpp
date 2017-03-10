#include <iostream>
#include <cassert>
#include "deque.h"
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct node {
	int data;
	int clock;
	int reference;
	int use;
	struct node *next;
	struct node *prev;
};


//This is the constructor. It runs in O(1).
Deque::Deque(){
    count = 0;
    head = new node;
    assert(head != NULL); //ensure that head is not NULL
    //sets the next and prev pointers back to head (one node)
	head->next = head;
    head->prev = head;
	clockPointer = head; //set clock
}

//This function returns the number of elements in the deque. Runs in O(1).
int Deque::size(){
    return  count;
}

//This function adds 'x' as the first item. Runs in O(1).
void Deque::addFirst(int x){
    node *temp = new node;
    assert(temp != NULL); //assert that temp is not NULL
    node *header = head;
    temp->data = x;
    temp->prev = header; //sets the prev of the temp to the head
    temp->next = header->next; //sets the next of the temp to the first element in the deque (inserting temp before first element, so temp is now first)
    header->next->prev = temp; //sets the prev of head to temp
    header->next = temp; //sets the next of head to the temp
    count++;
	temp->clock = 0;
	temp->use = 0;
	temp->reference = 1;
}

//This function adds 'x' as the last item. runs in O(1).
void Deque::addLast(int x){
    node *temp = new node;
    assert(temp != NULL); //assert that temp is not NULL
    node *header = head;
    temp->data = x;
    temp->next = header; //sets the next of temp to the head
    temp->prev = header->prev; //sets the prev of the temp to the 'prev' of head (last node)
    header->prev->next = temp; //sets the last node's 'next' to the temp
    header->prev = temp; //sets the prev of the head to the temp
    count++;
	temp->clock = 0;
	temp->use = 0;
	temp->reference = 1;
}

//This function removes the first item and returns it. Runs in O(1).
int Deque::removeFirst(){
    int num;
	assert(count != 0); //assert that deque is not empty
    node *header = head;
    node *first = header->next; //pointer to the first node -- makes it easier for me to track deletion (avoids too many arrows)
    num = first->data; //returning this value (node to be deleted)
    header->next = first->next; //sets the 'next' of the head to the 2nd node in the list
    first->next->prev =  header; //sets the 'prev' of first (first node) to the head
    delete(first); //deletes the first node
    count--;
    return num;
}

//This function removes the last item and returns it. Runs in O(1).
int Deque::removeLast(){
    int num;
	assert(count != 0); //assert that deque is not empty
    node *header = head;
    node *last = header->prev; //pointer to the last node -- makes it easier for me to track deletion (avoids too many arrows)
    num = last->data; //returning this value (node to be deleted)
    last->prev->next = header; //sets the 'next' of the 2nd to last node to head
    header->prev = last->prev; //sets the 'prev' of head to the 2nd to last node
    delete(last); //deletes the last node
    count--;
	return num;
}

//This function returns the data of the first node. Runs in O(1).
int Deque::getFirst(){
	assert(count != 0);//assert that deque is not empty
    return head->next->data;
}

//This function returns the data of the last node. Runs in O(1).
int Deque::getLast(){
	assert(count != 0); //assert that deque is not empty
    return head->prev->data;
}

void Deque::print() {
	node* temp = head->next;
	if(this->count == 0 ) {
		cout << "Nothing to print." << endl;
		return;
	}
	if(this->count == 1) {
		cout << "data -> " << temp->data << " clock -> " << temp->clock << endl;
		return;
	}
	while( temp->next != head->next ) {
		cout << "data -> " << temp->data << " clock -> " << temp->clock << " reference -> " << temp->reference << " used -> " << temp->use << endl;
		temp = temp->next;
	}
	cout << endl;
}

/* Find the node with the given value. */
node* Deque::find(int val) {
	bool look = false;
	node* temp = head->next;
    /* Find the node with the given value. */
	while(temp->next != head->next)	{
		if(temp->data == val) {
			look = true;
			break;
		}
		temp = temp->next;
	}
	
	if(look == true) {
		return temp;
	} else {
		return NULL;
	}

}

/* Set the 'time' (LRU) and 'use' (LFU) field of the node (found by 'find()'). */
void Deque::setTime(int val, int clock) {
	node* temp = find(val); /* First find the node. */
	temp->clock = clock;	/* Set the time value. */
	temp->use = temp->use + 1;
}

/* Sets the 'time' (LRU) and 'use' (LFU) field for the last node. This is a method to make the implementation easier for the page algorithms. */
void Deque::timeSetLast(int clock) {
	head->prev->clock = clock;
	head->prev->use = head->prev->use + 1;
}

/* This is a helper-method for LRU to remove the node with the lowest 'time' (least recently used). */
void Deque::removeOldest() {
	if(head->next == NULL) 
		return;

	node* temp = head->next;
	node* oldest = temp;

	while(temp->next != head) {
		if(temp->clock < oldest->clock) {
			oldest = temp;
		}
		temp = temp->next;
	}
	
	oldest->prev->next = oldest->next;
	oldest->next->prev = oldest->prev;
	free(oldest); /* Remove the node. */
	count--;

}

/* Helper-method for setting the reference bit (used in second chance). */
void Deque::setReferenceBit(int val) {
	node* temp = find(val);
	temp->reference = 1;	
}

/* Helper-method used in second chance to rotate the deque. */
void Deque::moveBack(int val) {
	assert(head != NULL);

	if(head->next == NULL) {
		return;
	}

	node* temp = find(val);
	if(temp == NULL) {
		return;
	}

	if(temp == head->prev) {
		temp->reference = 0;
		return;	
	}

	/* Remove the node and place it in front. */
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	temp->next = head;
	temp->prev = head->prev;
	head->prev->next = temp;
	head->prev = temp;
	
	temp->reference = 0;
	return;

}

/* This is a helper-method (used in second chance) to get the reference bit of the node. It is used to determine if the deque
 * needs to be rotated any further.
*/
int Deque::getFirstReference() {
	if(head->next != NULL) {
		return head->next->reference;
	} else {
		return -1;
	}
}

/* Helper-method to remove the least frequently used node. Note that if the 'use' fields are the same, then we compare 'time'. */
void Deque::removeLFU() {
	assert(head != NULL);
	if(size() == 0) {
		return;
	}

	node* temp = head->next;
	node* low = temp;
	
	while( temp != head) {
		if(temp->use < low->use) {
			low = temp;
		} else if(temp->use == low->use) {
			if(temp->clock < low->clock) {
				low = temp;
			}
		}
		temp = temp->next;
	}

	/* Remove low time */
	low->prev->next = low->next;
	low->next->prev = low->prev;
	free(low);
	count--;
}

/* Helper-method to remove a random node for the random algorithm. */
void Deque::removeRandom() {
	assert(head != NULL);
    time_t t;
    srand((unsigned) time(&t));
	int random = rand() % count + 1; //picks number from 1 .. d->size()
	//cout << "Random is: " << random << endl;
	int counter = 1;
	node* temp = head->next;

	while((counter <= count)) {
		if(counter == random) {
			break;
		}
		counter++;
		temp = temp->next;
	}

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
	count--;

}

//This is the destructor. It runs in O(n).
Deque::~Deque(){
    node *header = head;
    while(header->next != header){ //loops till header is = to itself (list is circular)
      	node *temp = header->next; //temp is the next node
       	header->next = temp->next; //sets the 'next' of the header to the temp's next
        delete(temp); //deletes temp and then continues with the while loop or returns if given right condition
    }
    delete(header);
}


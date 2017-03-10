#include<iostream>
#include<iomanip>
#include<fstream>
#include "deque.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		cout << "You do not have enough inputs." << endl;
		return -1;
	}

	int tableSize = atoi(argv[1]);
	int pageFaults = 0;
	int cycles = 0;
	Deque* d = new Deque;
	char input[1024];
	int size = 1024;

	while(fgets(input, size, stdin)) {
	    int num = atoi(input);	

        if(num <= 0) {
			//cout << "Enter a positive value." << endl;
		} else {
			cycles++;
			if(d->find(num) != NULL) { /* If already in cache, change reference bit to 1. */
				d->setReferenceBit(num);	
			} else if(d->size() == tableSize) { /* If full, rotate deque till first node has reference bit 0. */
				pageFaults++;
				while(d->getFirstReference() != 0) { /* Rotate the deque. */
					d->moveBack(d->getFirst());
				}	
				/* Now the first node has a reference bit of 0. */
				d->removeFirst();
				d->addLast(num);
			} else { /* Not found and size < cache limit, simply add to the back. */
				pageFaults++;
				d->addLast(num);
				d->setReferenceBit(num);
		    }
		}

    }
	
    cout << cycles << endl << pageFaults << endl;

}


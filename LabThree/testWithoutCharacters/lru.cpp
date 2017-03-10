#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdio.h>
#include "deque.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		cout << "You do not have enough inputs." << endl;
		return 1;
	}

	int tableSize = atoi(argv[1]);
	int cycles = 0;
	int pageFaults = 0;
	Deque* d = new Deque;
    char input[1024];
    int size = 1024;


	while(fgets(input, size, stdin)) {
		int num = atoi(input);
		if(num <= 0) {
			//cout << "Enter a positive value." << endl;
		} else {
			cycles++;
		
            if(d->find(num) != NULL) { /* If found, replace 'time' with current time. */
				d->setTime(num, cycles);		
			} else if(d->size() == tableSize) { /* If full, find lowest 'time' and replace. */
				pageFaults++;			
				d->removeOldest();
				d->addLast(num);
				d->timeSetLast(cycles);
			} else { /* Simply add to back if size < cache limit && not found. */
				pageFaults++;
				d->addLast(num);
				d->timeSetLast(cycles);
			}
		}
	}

	cout << cycles << endl << pageFaults << endl;

}

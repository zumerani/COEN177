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
	int cycles = 0; /* Keeps track of elements tracked. */
	int pageFaults = 0;
	Deque* d = new Deque;
	string l = "";
	
	while(!cin.eof()) {
		getline(cin, l);
        if (isdigit(l.c_str()[0])) {
		    int count = 0;
            char temp[10000];
			while (l[count] != '\0') {
				temp[count] = l[count];
				count++;
			}
			temp[count] = '\0';
			int num = atoi(temp);
	
			if(num >= 0) {
				cycles++;
				if(d->find(num) != NULL) { /* If found, replace 'time' with current time. */
					d->setTime(num, cycles);
				} else if(d->size() == tableSize) { /* If cache is full, find lowest 'time' and replace. */
					d->removeLFU();
					d->addLast(num);
					d->timeSetLast(cycles);
					pageFaults++;
				} else { /* If not found && size < cache limit, add to the back. */
					pageFaults++;
					d->addLast(num);
					d->timeSetLast(cycles);
				}
			}
	
		}
	}

	cout << cycles << endl << pageFaults << endl;

}


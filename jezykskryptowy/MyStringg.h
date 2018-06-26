#pragma once
#include <cstdio>

class MyStringg {
public:
	MyStringg *next;
	char *name;
	int Size; 

	void add(char *tab, int size) {
		name = new char[size + 1];
		for (int a = 0; a < size; a++) {
			name[a] = tab[a];
			if (a + 1 == size)
				name[a + 1] = NULL;
		}
		
	}
	~MyStringg() {
		delete name;
	}

};

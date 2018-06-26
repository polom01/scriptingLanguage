#pragma once

class Variable {
public:
	Variable *next;
	char *name;
	int value;
	bool Visible;
	bool didNULL;
	
	void add(char *tab , int size , int val , bool visible) {
		name = new char[size+1];
		this->Visible = visible;
		for (int a = 0; a < size; a++) {
			name[a] = tab[a];
			if(a+1==size)
			name[a + 1] = NULL;
		}
		value = val;
	}

	~Variable() {
		if(name!=nullptr)
		delete name;
	}

};
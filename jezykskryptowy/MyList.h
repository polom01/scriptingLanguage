#pragma once
#include"Variable.h"

#include<cstdio>
#include<iostream>



class MyList {
public:
	Variable *first;

	MyList() {
		first = NULL;
	}

	void setValue(char *tab , int Val) {
		Variable	*tmp = first;
		int size = getSize(tab);
		while (tmp != NULL) {
			int odp = 0;
			if (size == getSize(tmp->name)) {
				for (int a = 0; a <= size; a++) { //moze <= spr!!!!!! albo zmienic w funkcji
					if (tab[a] == tmp->name[a])odp++;
					if (odp == size + 1)  tmp->value=Val;//
				}
			}
			tmp = tmp->next;
		}
	}

	void addElement(char *tab, int size, int val , bool visible) {
		Variable *newOne = new Variable;
		if (first == NULL) {
			first = newOne;
			first->add(tab, size, val , visible);
			first->next = NULL;
		}
		else {
			Variable	*tmp = first;
			while (tmp->next != NULL) { tmp = tmp->next; }
			tmp->next = newOne;
			newOne->add(tab, size, val , visible);
			newOne->next = NULL;
		}
	}

	void printAll() {
		if (first == NULL) {
			std::cout << "brak elementow";
		}
		else {
			Variable *tmp = first;
			int wwww = 0;
			while (tmp != NULL && wwww<100 ) {//&& 
				wwww++;
				if (tmp->Visible == true) {
				//	std::cout << tmp->name << "  " << tmp->didNULL << std::endl;
					if (tmp->didNULL == false) {
						std::cout << tmp->name << "  " << tmp->value << std::endl;
					}
					else {
						std::cout << tmp->name << "  Nul" << std::endl;
					}
					tmp = tmp->next;
				}
			}
		}
	}

	int  operator [](char *tab) {// dziala
		Variable	*tmp = first;
		int size = getSize(tab);
		while(tmp!=NULL) { 
			int odp = 0;
			if (size == getSize(tmp->name)) {
				for (int a = 0; a <= size; a++){ 
					if (tab[a] == tmp->name[a])odp++;
					if (odp == size+1) return tmp->value;//
			}
			}
			tmp = tmp->next; 
		}


		return EOF;
   }
	int getSize(char * tab) {  
		int count = 0;
		while (tab[count]) {
			count++;
		}

		return count;
	}
	/////////////////////////////////////////////////////////////NULEEEEEEEE////////////////////////////////////////////
	void setNull(char *tab , bool did){
		Variable	*tmp = first;
		int size = getSize(tab);
		while (tmp != NULL) {
			int odp = 0;
			if (size == getSize(tmp->name)) {
				for (int a = 0; a <= size; a++) { 
					if (tab[a] == tmp->name[a])odp++;
					if (odp == size + 1)  tmp->didNULL = did;//
				}
			}
			tmp = tmp->next;
		}
	}
	bool getNull(char *tab) {
		Variable	*tmp = first;
		int size = getSize(tab);
		while (tmp != NULL) {
			int odp = 0;
			if (size == getSize(tmp->name)) {
				for (int a = 0; a <= size; a++) { 
					if (tab[a] == tmp->name[a])odp++;
					if (odp == size + 1) return tmp->didNULL;//
				}
			}
			tmp = tmp->next;
		}
		return true;
	}

	void clear() {

		while (first->next != NULL) {
			Variable *tmp = first;
			Variable *tmpNext = NULL;
			while (tmp->next != NULL) {
				if (tmp->next->next == NULL)tmpNext = tmp;

				tmp = tmp->next;
			}
			if (first->next != NULL)
				tmpNext->next = NULL;
			delete tmp;
		}
		first = NULL;

	}


};
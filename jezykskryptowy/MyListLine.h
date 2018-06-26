#pragma once
#include "MyStringg.h"
#include<cstdio>
#include<iostream>



class MyListLine {
public:
	MyStringg *first;


	MyListLine() {
		first = NULL;
	}

	void addElement(char *tab, int size) {
		MyStringg *newOne = new MyStringg;
		if (first == NULL) {
			first = newOne;
			first->add(tab, size);
			first->next = NULL;
			first->Size = size+1;
		}
		else {
			MyStringg	*tmp = first;
			while (tmp->next != NULL) { tmp = tmp->next; }
			tmp->next = newOne;
			newOne->add(tab, size);
			newOne->next = NULL;
			newOne->Size = size+1;
		}
	}


	MyStringg*  operator [](int index) {
		MyStringg	*tmp = first;
		while (index >0) {
			index--;
			tmp = tmp->next;
		}


		return tmp;
	}



	void clear() {

		while (first->next != NULL) {
			MyStringg *tmp = first;
			MyStringg *tmpNext=NULL;
			while (tmp->next != NULL) {
				if (tmp->next->next == NULL)tmpNext=tmp;

				tmp = tmp->next;
			}
			if(first->next!=NULL)
			tmpNext->next = NULL;
			delete tmp;
		}
		first = NULL;

		}







	void printAll() {
		if (first == NULL) {
			std::cout << "brak elementow";
		}
		else {
			MyStringg *tmp = first;
			while (tmp != NULL) {
				//std::cout << tmp->name << "tyle razy  "<< std::endl;
				tmp = tmp->next;
			}
		}
	}


};

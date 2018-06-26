#include <iostream>
//using namespace std;
#include"MyStringg.h"
#include"MyListLine.h"
#include "Variable.h"
#include"MyList.h"
#include"Calculations.h"
#include <ctype.h>
#include<math.h>
#define LONG 2000
#define OPERATIONS 100
#define LONGVARIABLE 100

#define TMPSIZE 100
MyList myListVariable;
MyListLine myListLine;
int buildWhile(int count, int howMany, char* tab, bool firstLoope, MyListLine listLine);
int buildIf(int count, int howMany, char* tab, bool firstLoope, MyListLine listLine);
int CountOperations;
int HowManyUseOperation;
bool returnTrue;

void stringInterpreter(MyListLine List, int startt);
int calculate(char *tmpRight);
int checkEquation(char cmd1, char cmd2) {  

	if ((cmd1 == '!') && (cmd2 == '=')) return 200;
	else if ((cmd1 == '=') && (cmd2 == '=')) return 300;
	else if ((cmd1 == '<') && (cmd2 == '=')) return 400;
	else if ((cmd1 == '>') && (cmd2 == '=')) return 500;
	else if (cmd1 == '=') return 1;
	else if (cmd1 == '<') return 1;
	else if (cmd1 == '>') return 1;
	else return EOF;

}

int checkEquation2(char cmd1, char cmd2) {  

	if ((cmd1 == '!') && (cmd2 == '=')) return 200;
	else if ((cmd1 == '=') && (cmd2 == '=')) return 300;
	else if ((cmd1 == '<') && (cmd2 == '=')) return 400;
	else if ((cmd1 == '>') && (cmd2 == '=')) return 500;
	else if (cmd2 == '=') return 1;
	else if (cmd2 == '<') return 1;
	else if (cmd2 == '>') return 1;
	else return EOF;

}

int checkEnd(char cmd1) {
	if (cmd1 == '=') return 1;
	else if (cmd1 == '<') return 1;
	else if (cmd1 == '>') return 1;
	else return EOF;
}
//kolejnosc wykonywania dzialan
int parseEnum(char cmd) {


	return cmd == '=' ? 0 :
		cmd == '!' ? 2 :
		cmd == '|' ? 1 :
		cmd == '<' ? 4 :
		cmd == '>' ? 4 :
		cmd == '+' ? 5 :
		cmd == '-' ? 5 :
		cmd == '/' ? 6 :
		cmd == '*' ? 7 :
		cmd == '%' ? 8 :
		cmd == '!' ? 9 :
		cmd == '- u' ? 10 :
		cmd == ' ' ? 20 :  //przerwa miedzy znakami
		cmd == '0' ? -10 :  //liczby
		cmd == '1' ? -10 :
		cmd == '2' ? -10 :
		cmd == '3' ? -10 :
		cmd == '4' ? -10 :
		cmd == '5' ? -10 :
		cmd == '6' ? -10 :
		cmd == '7' ? -10 :
		cmd == '8' ? -10 :
		cmd == '9' ? -10 :
		-10;
}


bool didNumber(char cmd) {

	return cmd == '0' ? true :  
		cmd == '1' ? true :
		cmd == '2' ? true :
		cmd == '3' ? true :
		cmd == '4' ? true :
		cmd == '5' ? true :
		cmd == '6' ? true :
		cmd == '7' ? true :
		cmd == '8' ? true :
		cmd == '9' ? true :
		false;
}



int  addVariables(int size, char *tab, char whereStart) {
	int skip = 0;
	int longVariable = 0;
	char variable[LONG];
	int a;
	for (a = whereStart; a < size; a++) {

		if (tab[a - 1] == ' ' && didNumber(tab[a]) && isspace(tab[a - 1])) return a - 1;


		if (checkEnd(tab[a]) != EOF) break;

		if (isspace(tab[a])) {
			if (longVariable > 0) {
				variable[longVariable] = NULL;
				if (myListVariable[variable] == EOF) {
					myListVariable.addElement(variable, longVariable, NULL, true);
					myListVariable.setNull(variable, true);
					longVariable = 0;
				}
				else {
					skip = a - longVariable;
					break;
				}
			}
			else longVariable = 0;
		}
		else { //tworzenie slowa
			variable[longVariable] = tab[a];
			longVariable++;
		}
	}

	if (longVariable > 0 && myListVariable[variable] == EOF && checkEnd(tab[a - 1]) != EOF) {
		myListVariable.addElement(variable, longVariable, NULL, true);
		myListVariable.setNull(variable, true);
	}
	else {
		skip = a - longVariable;
	}

	return skip; //zwraca na co aktualnie ma pokazywac wskaznik


}




char * OdwrotnaNotacjaPl(char *tab) {
	char *tabPl = new char[LONG];
	char stos[LONG];
	int tabPlCount = 0;
	int stosCount = 0;
	int count = 0;
	while (tab[count] != NULL) {
		if (isspace(tab[count])) {
			count++;
			continue; 
		}
		else if (tab[count] == '-') {
			int checking = count;
			checking++;
			int scor = 0;
			while (tab[checking] == ' ') {
				checking++;
			}
			if (((int)tab[checking] >= 'a' && (int)tab[checking] <= 'z') || ((int)tab[checking] >= 'A' && (int)tab[checking] <= 'Z') || ((int)tab[checking] >= '0' && (int)tab[checking] <= '9')) {
				scor++;

			}
			int cc = count - 1;
			while (cc>0 && isspace(tab[cc])) {
				cc--;
			}


			if (((int)tab[cc] >= 'a' && (int)tab[cc] <= 'z') || ((int)tab[cc] >= 'A' && (int)tab[cc] <= 'Z') || ((int)tab[cc] >= '0' && (int)tab[cc] <= '9')) {
				scor--;
			}

			if (scor == 1) {
				tabPl[tabPlCount++] = tab[count++];
			}
		}

		tabPl[tabPlCount];
		stos[stosCount];
		if (tab[count] == '(') {
			stos[stosCount] = tab[count];
			stosCount++;
		}
		else if (tab[count] == ')') {
			stosCount--;
			while (stos[stosCount] != '(') {
				tabPl[tabPlCount] = stos[stosCount];
				tabPlCount++;
				stosCount--;
			}
			//stosCount++;
		}
		else if (parseEnum(tab[count]) == -10) { //liczby i zmienne
			tabPl[tabPlCount] = tab[count];
			tabPlCount++;
		}
		else if (parseEnum(stos[stosCount - 1]) < parseEnum(tab[count])) {
		
			stos[stosCount] = tab[count];
			tabPl[tabPlCount] = ' ';
			tabPlCount++;
			stosCount++;
		}
		else if (parseEnum(stos[stosCount - 1]) >= parseEnum(tab[count])) {
		

			if (stosCount > 0) {
				stosCount--;
			}
			while ((stos[stosCount] != '(') && (stosCount >= 0)) {
				tabPl[tabPlCount] = stos[stosCount];
				tabPlCount++;
				stosCount--;
				if (parseEnum(stos[stosCount]) < parseEnum(tab[count]) || (stosCount == 0)) {
					stosCount++;
					stos[stosCount] = tab[count];
					stosCount++;
					break;
				}
			}
			//stosCount++;
		}
		count++;
	}

	for (int i = stosCount - 1; i >= 0; i--) {
		tabPl[tabPlCount] = stos[i];
		if ((stos[i] != '(') && (stos[i] != ')'))
			tabPlCount++;
	}
	tabPl[tabPlCount] = NULL;
	int a = 0;
	/*
	while (tabPl[a]) {
	std::cout << tabPl[a];
	a++;
	}
	std::cout << std::endl;
	*/
	delete tab;
	return tabPl;

}



void stringDivide(char *tab, int howMany) {
	////1
	int count = 0;
	int countOpe = 0;
	char counterOperations[OPERATIONS];
	while (count <= howMany) {
		if (didNumber(tab[count])) {
			counterOperations[countOpe] = tab[count];
			countOpe++;
			count++;
			continue;
		}
		else if (tab[count] != ' ') break;

		count++;
	}
	myListLine.addElement(counterOperations, countOpe);

	////2
	count = addVariables(howMany, tab, count);  //dodawanie zmiennych
												//test
												/*
												myListVariable.printAll();

												for (int j = count; j < howMany; j++)
												std::cout << tab[j];
												//test
												*/

												////3
	int place = count;
	while (count <= howMany)
	{
		char sign = '`';
		if (tab[count] == '@') {

			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j < count; j++) {
					tmp[zacz++] = tab[j];
				}

				tmp[zacz] = NULL;
				myListLine.addElement(tmp, zacz);

			}
			count = buildWhile(count, howMany, tab, true, myListLine); //break;   !!!!!!!!!!!!
			place = count;
		}
		else if (tab[count] == '?') {
			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j < count; j++) {
					tmp[zacz++] = tab[j];
				}
				//	tmp[zacz++] = '}';
				tmp[zacz] = NULL;
				myListLine.addElement(tmp, zacz);

			}
			count = buildIf(count, howMany, tab, true, myListLine);
			place = count;
		}
		int tmpCount = count;
		if (((int)tab[tmpCount] >= 'a' && (int)tab[tmpCount] <= 'z') || ((int)tab[tmpCount] >= 'A' && (int)tab[tmpCount] <= 'Z') || ((int)tab[tmpCount] >= '0' && (int)tab[tmpCount] <= '9')) {

			while (tab[count + 1] == ' ') {
				count++;
				if ((count < howMany) && (((int)tab[count + 1] >= 'a' && (int)tab[count + 1] <= 'z') || ((int)tab[count + 1] >= 'A' && (int)tab[count + 1] <= 'Z') || ((int)tab[count + 1] >= '0' && (int)tab[count + 1] <= '9') || tab[count + 1] == '@' || tab[count + 1] == '?')) {
					char tmp[LONG];
					int zacz = 0;
					for (int j = place; j <= count; j++) {
						tmp[zacz++] = tab[j];
					}
					tmp[zacz] = NULL;
					myListLine.addElement(tmp, zacz);

					place = count;
				}

			}
		}
		count++;
	}


	//////////ostanie dodanie
	if (place != count) {
		char tmp[LONG];
		int zacz = 0;
		for (int j = place; j <= count; j++) {
			tmp[zacz++] = tab[j];
		}
		tmp[zacz] = NULL;
		myListLine.addElement(tmp, zacz);
	}
	//////////

	int p = 0;

	/*
	while (myListLine[p] != NULL) {
	std::cout << std::endl << myListLine[p]->name;
	p++;
	}
	*/
	////

}


int buildWhile(int count, int howMany, char* tab, bool firstLoope, MyListLine listLine) {
	int placeNr1 = count;
	int ile1 = 0;
	int ile2 = -1;
	while ((tab[count] != '}' || ile1>0 || ile2>0) && count <= howMany) {
		if (tab[count] == '(') ile1++;
		else if (tab[count] == ')')ile1--;
		else if (tab[count] == '{') ile2++;
		else if (tab[count] == '}')ile2--;
		count++;
	}

	char tmp[LONG];
	int zacz = 0;
	for (int j = placeNr1; j <= count; j++) { //zmiana na <=
		tmp[zacz++] = tab[j];
	}
	tmp[zacz] = NULL;
	listLine.addElement(tmp, zacz);


	return count + 1;
}



int buildIf(int count, int howMany, char* tab, bool firstLoope, MyListLine listLine) {
	int placeNr1 = count;
	int ile1 = 0;
	int ile2 = -1;
	while (tab[count] != '}' || ile1>0 || ile2>0) {
		if (tab[count] == '(') ile1++;
		else if (tab[count] == ')')ile1--;
		else if (tab[count] == '{') ile2++;
		else if (tab[count] == '}')ile2--;
		count++;
	}

	char tmp[LONG];
	int zacz = 0;
	for (int j = placeNr1; j < count; j++) {
		tmp[zacz++] = tab[j];
	}
	tmp[zacz++] = '}';
	tmp[zacz] = NULL;
	listLine.addElement(tmp, zacz);


	return count + 1;
}

bool checkCondition(char *tab, bool didFirst, bool didnegation) {
	if (CountOperations - HowManyUseOperation <= 0)return 0;
	//	std::cout << "warunek : " <<tab<<"   "<< HowManyUseOperation << std::endl;
	bool didOk = false;
	if (didFirst == true) {
		int jj = 0;
		while (tab[jj] != NULL) {
			if (tab[jj] == '=' || tab[jj] == '>' || tab[jj] == '<' || tab[jj] == '!' || tab[jj] == '&' || tab[jj] == '|') {
				if (tab[jj + 1] == NULL)jj = jj;
				else jj++;
				HowManyUseOperation++;
			}
			jj++;
		}
	}

	int count = 0;
	char *tmpLeft = NULL;
	char *tmpRight = NULL;
	char * work = NULL;
	int countWork = 0;
	char oper[2] = " ";
	while (tab[count] != NULL) {
		if (count == 0 || tab[count] == '>' || tab[count] == '<' || tab[count] == '=' || tab[count] == '!') {
			oper[0] = tab[count];
			if (tab[count + 1] == '=') {
				oper[1] = '=';
				count++;
			}
			if (tmpLeft == NULL) {
				tmpLeft = new char[TMPSIZE];
				work = tmpLeft;
				countWork = 0;
				if (count>0)	count++;
				else work[countWork++] = tab[count++];
				continue;
			}
			else if (tmpRight == NULL) {
				tmpRight = new char[TMPSIZE];
				work[countWork] = NULL;
				work = tmpRight;
				countWork = 0;
				count++;
				continue;
			}
			else {
				delete tmpLeft;
				tmpLeft = tmpRight;
				work[countWork] = NULL;
				tmpRight = new char[TMPSIZE];
				work = tmpRight;
				countWork = 0;
				count++;
				continue;
			}
		}
		else  if (tab[count] == '|') {
			char tmp[100];
			int i = 0;
			count++;
			while (tab[count] != NULL)tmp[i++] = tab[count++];
			tmp[i] = NULL;

			bool odp = checkCondition(tmp, false, false);
			if (odp == true) {
				if (tmpLeft != NULL && tmpRight != NULL) {
					work[countWork] = NULL;
					tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
					tmpRight = OdwrotnaNotacjaPl(tmpRight);
					int v1 = calculate(tmpLeft);
					int v2 = calculate(tmpRight);
					return true;
				}
				else if (tmpLeft != NULL) {
					work[countWork] = NULL;
					tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
					int v1 = calculate(tmpLeft);
					return true;

				}
				else return true;
			}
			else {
				if (tmpLeft != NULL && tmpRight != NULL) {
					work[countWork] = NULL;
					//	std::cout << "warunek : " << tmpLeft << " 1 " << oper << " 2 " << tmpRight << std::endl;
					tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
					tmpRight = OdwrotnaNotacjaPl(tmpRight);
					int v1 = calculate(tmpLeft);
					int v2 = calculate(tmpRight);
					//std::cout << "weszlo do : 	if (tmpLeft != NULL && tmpRight != NULL) {  "<<"> <" << std::endl;
					///licznik operacji
					if (oper[1] == '=') {
						switch (oper[0])
						{
						case '>':return v1 >= v2;
						case '<':return v1 <= v2;
						case '=':return v1 == v2;
						case '!':return v1 != v2;
						}
					}
					else {
						switch (oper[0])
						{
						case '>':return v1 > v2;
						case '<':return v1 < v2;
						}
					}
				}
				else if (tmpLeft != NULL) {
					//std::cout << "warunek : " << tmpLeft << std::endl;
					tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
					int v1 = calculate(tmpLeft);
					if (myListVariable[tmpLeft] != EOF) {
						if (myListVariable.getNull(tmpLeft) == true) return 0;
						else return 1;
					}
					else return NULL;
				}
			}
		}
		else if (tab[count] == '&') {
			char tmp[100];
			int i = 0;
			count++;
			while (tab[count] != NULL)tmp[i++] = tab[count++];
			tmp[i] = NULL;
			bool odp = checkCondition(tmp, false, false);
			if (!didFirst && odp == false) {
				return odp;
			}
			didOk = odp;
			//////////////////////////////////////
			if (odp == true) {
				if (tmpLeft != NULL && tmpRight != NULL) {
					work[countWork] = NULL;
					//	
					tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
					tmpRight = OdwrotnaNotacjaPl(tmpRight);
					int v1 = calculate(tmpLeft);
					int v2 = calculate(tmpRight);
					//std::cout << "weszlo do : 	if (tmpLeft != NULL && tmpRight != NULL) {  "<<"> <" << std::endl;
				
					if (oper[1] == '=') {
						switch (oper[0])
						{
						case '>':return v1 >= v2;
						case '<':return v1 <= v2;
						case '=':return v1 == v2;
						case '!':return v1 != v2;
						}
					}
					else {
						switch (oper[0])
						{
						case '>':return v1 > v2;
						case '<':return v1 < v2;
						}
					}
				}
				else if (tmpLeft != NULL) {
					//std::cout << "warunek : " << tmpLeft << std::endl;
					work[countWork] = NULL;
					if (didnegation == true) {
						tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
						int v1 = calculate(tmpLeft);
						if (myListVariable[tmpLeft] != EOF) {
							if (myListVariable.getNull(tmpLeft) == true) return 1;
							else return 0;
						}
						else return 1;
					}
					else {
						tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
						int v1 = calculate(tmpLeft);
						if (myListVariable[tmpLeft] != EOF) {
							if (myListVariable.getNull(tmpLeft) == true) return 0;
							else return 1;
						}
						else return NULL;
					}
				}
			}
			else return false;

			/////////////////////////////////
		}
		work[countWork++] = tab[count++];

	}
	work[countWork] = NULL;

	if (tmpLeft != NULL && tmpRight != NULL) {
		//	std::cout << "warunek : " << tmpLeft << " 1 " << oper << " 2 " << tmpRight << std::endl;
		tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
		tmpRight = OdwrotnaNotacjaPl(tmpRight);
		int v1 = calculate(tmpLeft);
		int v2 = calculate(tmpRight);
		//std::cout << "weszlo do : 	if (tmpLeft != NULL && tmpRight != NULL) {  "<<"> <" << std::endl;
		///licznik operacji
		if (oper[1] == '=') {
			switch (oper[0])
			{
			case '>':return v1 >= v2;
			case '<':return v1 <= v2;
			case '=':return v1 == v2;
			case '!':return v1 != v2;
			}
		}
		else {
			switch (oper[0])
			{
			case '>':return v1 > v2;
			case '<':return v1 < v2;
			}
		}
	}
	else if (tmpLeft != NULL) {
		//std::cout << "warunek : " << tmpLeft << std::endl;
		tmpLeft = OdwrotnaNotacjaPl(tmpLeft);
		int v1 = calculate(tmpLeft);
		if (myListVariable[tmpLeft] != EOF) {
			if (myListVariable.getNull(tmpLeft) == true) return 0;
			else return 1;
		}
		else return NULL;
	}

	return false;

}



void startWhile(char * tab) { //dowobic destruktor   !!!!!!!!
							  //std::cout << tab << "   " << HowManyUseOperation << std::endl;
	bool negacja = false;
	int count = 0;
	char tmpCondition[50];
	int countCondition = 0;
	int howMany = 0;
	MyListLine newOne;
	while (tab[count] != NULL) {
		howMany++;
		count++;
	}
	count = 0;
	//liczenie ile jest elementow

	while (tab[count] != '(') {
		if (tab[count] == NULL) return;
		else count++;
	}
	while (tab[count] != ')') {
		if (tab[count] == ' ')count++;
		else if (tab[count] == '!' && tab[count + 1] != '=') {
			negacja = true;
			HowManyUseOperation++;//////////////////////////////////////////////here
			count++;
		}
		else tmpCondition[countCondition++] = tab[count++];
	}
	tmpCondition[countCondition] = NULL;
	count++;
	//warunek dorobic na kilka nawiasow
	/////////////////////////////////

	while (tab[count] != '{') {
		if (tab[count++] == NULL) return;
	}
	count++;

	int place = count;
	while (count <= howMany) {
		if (tab[count] == '@') {

			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j <= count; j++) {
					tmp[zacz++] = tab[j];
				}
				tmp[zacz] = NULL;
				newOne.addElement(tmp, zacz);
			}
			count = buildWhile(count, howMany, tab, true, newOne); //break;   !!!!!!!!!!!!
			place = count;
		}
		else if (tab[count] == '?') {
			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j <= count; j++) {
					tmp[zacz++] = tab[j];
				}
				tmp[zacz] = NULL;
				newOne.addElement(tmp, zacz);
			}
			count = buildIf(count, howMany, tab, true, newOne);
			place = count;
			if (tab[count] >= '?')count = buildIf(count, howMany, tab, true, newOne);
			place = count;
		}
		int tmpCount = count;
		if (((int)tab[tmpCount] >= 'a' && (int)tab[tmpCount] <= 'z') || ((int)tab[tmpCount] >= 'A' && (int)tab[tmpCount] <= 'Z') || ((int)tab[tmpCount] >= '0' && (int)tab[tmpCount] <= '9') || tab[tmpCount] == ')') {

			while (isspace(tab[count + 1]) || tab[count + 1] == '}') {
				count++;
				if ((count < howMany) && (((int)tab[count + 1] >= 'a' && (int)tab[count + 1] <= 'z') || ((int)tab[count + 1] >= 'A' && (int)tab[count + 1] <= 'Z') || ((int)tab[count + 1] >= '0' && (int)tab[count + 1] <= '9') || tab[count + 1] == '@' || tab[count + 1] == '?' || tab[count] == '}')) {
					char tmp[LONG];
					int zacz = 0;
					for (int j = place; j < count; j++) {
						tmp[zacz++] = tab[j];
					}
					tmp[zacz] = NULL;
					newOne.addElement(tmp, zacz);
					place = count;
				}

			}
		}
		count++;

	}

	//newOne.printAll();

	//////////////////////////////  somo sprawdzenie daje +1

	HowManyUseOperation++;
	while (checkCondition(tmpCondition, true, negacja)) {
		if (negacja)HowManyUseOperation++;
	
		HowManyUseOperation++;
	
		stringInterpreter(newOne, 0);
	}
	newOne.clear();
	///////////////// interpretacja
}
void startIf(char * tab) {
	//std::cout << "startIf "<<tab << std::endl;
	bool negacja = false;
	int count = 0;
	char tmpCondition[50];
	int countCondition = 0;
	int howMany = 0;
	MyListLine newOne;
	while (tab[count] != NULL) {
		howMany++;
		count++;
	}
	count = 0;
	//liczenie ile jest elementow

	while (tab[count] != '(') {
		if (tab[count] == NULL) return;
		else count++;
	}
	while (tab[count] != ')') {
		if (isspace(tab[count]))count++;
		else if (tab[count] == '!') {
			negacja = true;
			count++;
		}
		else tmpCondition[countCondition++] = tab[count++];
	}
	tmpCondition[countCondition] = NULL;
	count++;
	
	/////////////////////////////////

	while (tab[count] != '{') {
		if (tab[count++] == NULL) return;
	}
	count++;

	int place = count;
	while (count <= howMany) {
		if (tab[count] == '@') {

			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j <= count; j++) {
					tmp[zacz++] = tab[j];
				}
				tmp[zacz] = NULL;
				newOne.addElement(tmp, zacz);
			}
			count = buildWhile(count, howMany, tab, true, newOne); 
			place = count;
		}
		else if (tab[count] == '?') {
			if (place != count) {
				char tmp[LONG];
				int zacz = 0;
				for (int j = place; j <= count; j++) {
					tmp[zacz++] = tab[j];
				}
				tmp[zacz] = NULL;
				newOne.addElement(tmp, zacz);
			}
			count = buildIf(count, howMany, tab, true, newOne);
			place = count;
		}
		int tmpCount = count;
		if (((int)tab[tmpCount] >= 'a' && (int)tab[tmpCount] <= 'z') || ((int)tab[tmpCount] >= 'A' && (int)tab[tmpCount] <= 'Z') || ((int)tab[tmpCount] >= '0' && (int)tab[tmpCount] <= '9') || tab[tmpCount] == ')') {

			while (isspace(tab[count + 1]) || tab[count + 1] == '}') {
				count++;
				if ((count < howMany) && (((int)tab[count + 1] >= 'a' && (int)tab[count + 1] <= 'z') || ((int)tab[count + 1] >= 'A' && (int)tab[count + 1] <= 'Z') || ((int)tab[count + 1] >= '0' && (int)tab[count + 1] <= '9') || tab[count + 1] == '@' || tab[count + 1] == '?' || tab[count] == '}')) {
					char tmp[LONG];
					int zacz = 0;
					for (int j = place; j < count; j++) {
						tmp[zacz++] = tab[j];
					}
					tmp[zacz] = NULL;
					newOne.addElement(tmp, zacz);
					place = count;
				}

			}
		}
		count++;

	}
	//newOne.printAll();

	//////////////////////////////
	//std::cout << "weszlo do : 	void startIf(char * tab) {  " << std::endl;
	HowManyUseOperation++;
	if (negacja == false) {

		if (checkCondition(tmpCondition, true, false)) {
			//	std::cout << "start check action" << std::endl;
			stringInterpreter(newOne, 0);
		}
	}
	else {
		HowManyUseOperation++;
		if (!checkCondition(tmpCondition, true, false)) {
			stringInterpreter(newOne, 0);
		}

	}

}

bool checkMinus(char *tab, int count) {
	while (count >= 0) {
		if (isspace(tab[count])) count--;
		else if (tab[count] < '0')return true;
		else {
			return false;
		}

	}
	return true;
}

bool checkMinus2(char *tab, int count) {
	while (tab[count] != NULL) {
		if (tab[count] == ' ') count++;
		else if (tab[count] >= '0' && tab[count] <= '9')return true;
		else {
			return false;
		}

	}
	return true;
}


int calculate(char *tmpRight) {
	//std::cout << tmpRight << std::endl;
	if (CountOperations - HowManyUseOperation <= 0) return NULL;  //
																
	int stos[50];
	int stosCount = 0;
	char* tab = NULL;
	int count = 0;
	int index = 0;
	while (tmpRight[count] != NULL) {// 
		if (tmpRight[count] != ' ') {
			if (tab == NULL) {
				tab = new char[TMPSIZE];
			}
			if (tmpRight[count] > ' ' && tmpRight[count] <= '/') {
				if (tmpRight[count] == '-' && checkMinus2(tmpRight, count + 1) && checkMinus(tmpRight, count - 1) && tmpRight[count + 1] != NULL) {
					tab[index++] = tmpRight[count++];  //wyjatek np -12
				}
				else {
					////////dodanie do stosa
					if (index > 0) {
						int value = 0;
						if (tab[0] <= '9') {  //liczby
							int a = 0;
							if (tab[0] == '-') a = 1;
							while (tab[a] <= ' ' && tab[a] != NULL)a++;
							while (a < index) {

								value += ((int)tab[a] - (int)'0')*pow(10.0, (double)(index - a - 1));
								a++;
							}
							if (tab[0] == '-') value = -value;
						}
						else {  //tutaj zmiennen w razie problemow dodac na -
							tab[index] = NULL;
							value = myListVariable[tab];
							if (value == EOF) returnTrue = true;
						}
						stos[stosCount++] = value;
						index = 0;
						delete tab;
						tab = NULL;
					}
					////////dodanie do stosa

					int v2 = stos[--stosCount];

					int v1 = stos[--stosCount];

					///licznik operacji
					if (tmpRight[count] == '/' && v2 == 0) {
						HowManyUseOperation++;
						stos[stosCount++] = NULL;
						count++;
						returnTrue = true;
						continue;
					}
					else if (tmpRight[count] == '%' && v2 == 0) {
						HowManyUseOperation++;
						stos[stosCount++] = NULL;
						count++;
						returnTrue = true;
						continue;
					}
					switch (tmpRight[count])     
					{
					case '+': v1 += v2;  HowManyUseOperation++;   break;
					case '-': v1 -= v2; HowManyUseOperation++;   break;
					case '*': v1 *= v2; HowManyUseOperation++;   break;
					case '/': v1 /= v2; HowManyUseOperation++;   break;
					case '%': v1 = v1 % v2; HowManyUseOperation++;   break;
					}
					stos[stosCount++] = v1;


					count++;
					continue;
				}
			}
			tab[index++] = tmpRight[count];

		}
		else if (tab != NULL) {
			int value = 0;
			if (tab[0] <= '9') {  //liczby
				int a = 0;
				if (tab[0] == '-') a = 1;
				while (a < index) {
					if (tab[a] == ' ')a++;
					else {
						value += ((int)tab[a] - (int)'0')*pow(10.0, (double)(index - a - 1));
						a++;
					}
				}
				if (tab[0] == '-') value = -value;
			}
			else {  
				tab[index] = NULL;
				value = myListVariable[tab];
				if (value == EOF) {
					returnTrue = true;
					value = NULL;
				}
			}
			stos[stosCount++] = value;
			index = 0;
			delete tab;
			tab = NULL;
		}

		count++;
	}


	if (stosCount == 0) {
		int value = 0;
		if (tab[0] <= '9') {  //liczby
			int a = 0;
			if (tab[0] == '-') a = 1;
			while (a < index) {
				value += ((int)tab[a] - (int)'0')*pow(10.0, (double)(index - a - 1));
				a++;
			}
			if (tab[0] == '-') value = -value;
		}
		else {  
			tab[index] = NULL;
			value = myListVariable[tab];
			if (value == EOF)returnTrue = true;
		}
		stos[stosCount++] = value;
		index = 0;
		delete tab;
		tab = NULL;

	}

	return stos[0];
}

void merging(char *tmpLeft, int value, char *oper, int numberOperation) { 
	if (CountOperations - HowManyUseOperation <= 0) return;  //
															 //std::cout<<"to jest wartosc : " << value << std::endl;
	char tmp[LONGVARIABLE];
	int count = 0;
	while (isspace(tmpLeft[count]))count++;
	if (tmpLeft[count] <= '9') {
		HowManyUseOperation++;
		if (CountOperations - HowManyUseOperation > 0)HowManyUseOperation++;
		return;
	}
	else {
		int a = 0;
		while (tmpLeft[count] != NULL && tmpLeft[count] != ' ') {  
			tmp[a++] = tmpLeft[count];
			count++;
		}
		tmp[a] = NULL;
		if (myListVariable[tmp] == EOF) {
			myListVariable.addElement(tmp, a, value, false);
			if (returnTrue == true) {
				myListVariable.setNull(tmp, true);
				returnTrue = false;
			}
			else {
				myListVariable.setNull(tmp, false);
			}
			//std::cout << "weszlo do : 		if (myListVariable[tmp] == EOF) {   "<<"=" << std::endl;
			HowManyUseOperation++;
		}
		else {
			if (returnTrue == true) {
				myListVariable.setNull(tmp, true);
				returnTrue = false;
			}
			else {
				myListVariable.setNull(tmp, false);
			}
			myListVariable.setValue(tmp, value);
			//	std::cout << "weszlo do : 	  esle    {if (returnTrue == true) { " << "=" << std::endl;
			HowManyUseOperation++;
		}
	}
}


void stringInterpreter(MyListLine List, int startt) {

	int index = 0;
	int numberOfOperation = 0;

	if (startt == 1) {
		int a = 0;
		double size = 0;
		while (List[0]->name[(int)size] != NULL && !isspace(List[0]->name[(int)size])) { size++; }

		while (a < size) {
			numberOfOperation += ((int)List[0]->name[a] - (int)'0')*pow(10.0, (double)(size - a - 1));
			a++;
		}
		CountOperations = numberOfOperation;
		HowManyUseOperation = 0;
	}

	if (CountOperations - HowManyUseOperation <= 0) return;
	//std::cout << "to jest ta liczba : "<<numberOfOperation << std :: endl;

	int line = startt;

	while (List[line] != NULL) {
		int placeX = 0;
		while (isspace(List[line]->name[placeX]))placeX++;

		if (List[line]->name[placeX] == '@') startWhile(List[line]->name);
		else if (List[line]->name[placeX] == '?') startIf(List[line]->name);
		else {

			char *tmp = List[line]->name;
			while (tmp[placeX] != NULL)placeX++;
			char *tmpLeft = NULL;
			char *tmpRight = NULL;
			char *tmpWork;
			int x = 0;
			char oper[4] = " ";
			int numberOperations = 0;
			for (int i = placeX - 1; i >= 0; i--) {

				if (i > 0 && checkEquation2(tmp[i - 1], tmp[i])>0) {
					if (tmpRight == NULL) {
						tmpRight = new char[placeX];
						tmpWork = tmpRight;
					}
					else if (tmpLeft == NULL) {
						tmpLeft = new char[placeX];
						tmpWork = tmpLeft;
					}
					else {
						tmpRight = OdwrotnaNotacjaPl(tmpRight);  //ok
						merging(tmpLeft, calculate(tmpRight), oper, numberOperations);

					
						delete tmpRight;
						tmpRight = tmpLeft;
						tmpLeft = new char[placeX];
						tmpWork = tmpLeft;

					}
					for (int j = placeX - 1; j > i - 1; j--) {
						tmpWork[placeX - 1 - j] = tmp[i + placeX - j];
					}
					tmpWork[placeX - i] = NULL;
					//	std::cout <<"po petli : "<< tmpWork << std::endl;					
					oper[(numberOperations + 1) % 4] = tmp[i];
					numberOperations++;
					placeX = i - 1;
					if (checkEquation2(tmp[i - 1], tmp[i]) != 1) {
						oper[(numberOperations - 1) % 4] = tmp[i - 1];
						numberOperations++;
						placeX -= 1;
						i--; //dodatkowa zabrana czesc
					}

				}
				else if (i == 0) {
					if (tmpRight == NULL) {
						;
					}
					else if (tmpLeft == NULL) {
						tmpLeft = new char[placeX];
						tmpWork = tmpLeft;
						for (int j = placeX - 1; j >= i - 1; j--) {
							tmpWork[placeX - 1 - j] = tmp[i + placeX - 1 - j];
						}
						tmpWork[placeX - i + 1] = NULL;
						//std::cout << "to jest ta nazwa " << tmpWork << std::endl;
						tmpRight = OdwrotnaNotacjaPl(tmpRight);  //ok
						merging(tmpLeft, calculate(tmpRight), oper, numberOperations);

						//spr wykonane obliczenia  !!!!!!!!!!!!!!!
						delete tmpRight;
					}
					else { //przypadek kiedy sa 2 w pamieci
						tmpRight = OdwrotnaNotacjaPl(tmpRight);  //ok
						merging(tmpLeft, calculate(tmpRight), oper, numberOperations);
						delete tmpRight;
						tmpRight = tmpLeft;
						tmpLeft = new char[placeX];
						tmpWork = tmpLeft;
						for (int j = placeX - 1; j >= i - 1; j--) {
							if (tmp[i + placeX - 1 - j] < '?'&&tmp[i + placeX - 1 - j] > ';') tmpWork[placeX - 1 - j] = ' '; ///////////////UWAGA NIE SPRAWDZANE NA WSZYSTJ+KICH!!!!!!!!!!!!
							else {
								tmpWork[placeX - 1 - j] = tmp[i + placeX - 1 - j];
							}
						}
						tmpWork[placeX - i + 1] = NULL;
						//std::cout << "to jest ta nazwa " << tmpWork << std::endl;
						tmpRight = OdwrotnaNotacjaPl(tmpRight);  //ok
						merging(tmpLeft, calculate(tmpRight), oper, numberOperations);

					}
				}
			}
		}
		line++;

	}
}


int main() {

	char MyCode[100 * LONG];
	char Code[LONG];
	int howMany = 0;
	int spr = 0;
	while (std::cin.getline(Code, LONG) ) {// && spr<13 do testow
		spr++;
		int indexx = 0;
		while ((Code[indexx])) {
			MyCode[howMany++] = Code[indexx++];

		}
		MyCode[howMany++] = ' ';

	}
	MyCode[howMany] = NULL;



	stringDivide(MyCode, howMany);
	stringInterpreter(myListLine, 1);

	std::cout << HowManyUseOperation << std::endl;

	myListVariable.printAll();
	myListLine.clear();
	myListVariable.clear();


	return 0;
}
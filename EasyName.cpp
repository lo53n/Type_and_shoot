#include "EasyName.h"

void Easy_name::setName(string name){
	name += addName();
	Modifier::setName(name);
}

string Easy_name::addName(){

	vector<string> nazwy;
	fstream plik;
	plik.open("EasyName.txt", ios::in);
	if (plik.good()){
		string napis;
		while (!plik.eof()){
			getline(plik, napis);
			nazwy.push_back(napis);
		}
		plik.close();
	}
	return nazwy[rand() % nazwy.size()];
}
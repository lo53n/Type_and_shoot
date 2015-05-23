#include "HardName.h"

void Hard_name::setName(string name) {
	name += addName();
	Modifier::setName(name);
}

string Hard_name::addName(){
	vector<string> nazwy;
	fstream plik;
	plik.open("HardName.txt", ios::in);
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
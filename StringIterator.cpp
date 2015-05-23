#include "StringIterator.h"

void Stringiterator::first(){
	index = 0;
}

void Stringiterator::next(){
		index++;
}

bool Stringiterator::isDone(){
	if (index > str->Count())
		index = str->Count();
	return index == str->Count();
}

string Stringiterator::currentItem(){
	string tmp(1, str->result[index]);
	return tmp;
}

string Stringiterator::getRest(){
	return str->result.substr(index);
}

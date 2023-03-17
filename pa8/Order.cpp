/*
Gavin Stark
gestark
pa7
*/
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(int argc, char **argv){
	Dictionary* D = new Dictionary();
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	std::string s;
	int count = 0;
	while(getline(in, s)){
		count++;
		D->setValue(s, count);
	}
	out << D->to_string() << endl;
	out << D->pre_string();

}
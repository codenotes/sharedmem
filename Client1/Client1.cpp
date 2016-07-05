// Client1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;
extern "C"
{
	int client(char *sharedMemName, char * properVectorName);
	int host(char *sharedMemName,char * properVectorName);
	void tearDown(char *sharedMemName);
	void mapclient(char * sharedMapName, char * properMapName, std::map<int, std::string> &yourmap);
	void maphost(char * sharedMapName, char * properMapName);
	void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName);
}


int main()
{
	//host("boobs");
	maphost("boobs", "boobMap");
	int c;

	cin >> c;
    return 0;
}


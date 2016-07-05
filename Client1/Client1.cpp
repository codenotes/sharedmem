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
	void getSharedMemoryMap(char * sharedMapName, std::map<int, std::string> &yourmap);
	void setSharedMemoryMap(char * sharedMapName, std::map<int, std::string> yourmap);
	void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName);
}


int main()
{
	//host("boobs");
	std::map<int, std::string> map1;
	map1[0] = "map1";
	setSharedMemoryMap("boobs1", map1);
	map1[0] = "map2";
	setSharedMemoryMap("boobs2", map1);
	int c;

	cin >> c;
    return 0;
}


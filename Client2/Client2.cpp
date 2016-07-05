// Client2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

extern "C"
{
	int client(char *sharedMemName, char * properVectorName);
	int host(char *sharedMemName, char * properVectorName);
	void tearDown(char *sharedMemName);
	void mapclient(char * sharedMapName, char * properMapName, std::map<int, std::string> &yourmap);
	void maphost(char * sharedMapName, char * properMapName);
	void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName);
}


int main()
{
	int x;

	addToSharedMap(5, "greg", "boobs", "boobMap");
	std::map<int, std::string> mymap;

	mapclient("boobs","boobMap",mymap);
	cout << mymap.size() << endl;

	cin >> x;
	//tearDown("boobs");
    return 0;
}


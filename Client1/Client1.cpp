// Client1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>

using namespace boost::interprocess;
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
	/*const char * shm_name = "shared_memory_segment";
	shared_memory_object::remove(shm_name);


	try
	{
		managed_shared_memory segment(create_only, shm_name, 65536);
	}
	catch (boost::interprocess::interprocess_exception& e)
	{
		printf("Error opening %s\n", e.what());
	}

	return 0;
*/
	
	//host("boobs");
	std::map<int, std::string> map1;
	map1[0] = "map1";
	setSharedMemoryMap("init", map1);
	
	map1[0] = "map2";
	setSharedMemoryMap("boobs2", map1);
	int c;

	cin >> c;
    return 0;
}


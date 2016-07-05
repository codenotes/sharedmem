// sharedmem.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>

extern "C"
{

	__declspec(dllexport) void clearmap(char * sharedMapName, char * properMapName)
	{

		using namespace boost::interprocess;
		typedef int    KeyType;
		typedef std::string  MappedType;
		typedef std::pair<const int, std::string> ValueType;

		//Alias an STL compatible allocator of for the map.
		//This allocator will allow to place containers
		//in managed shared memory segments
		typedef allocator<ValueType, managed_shared_memory::segment_manager>
			ShmemAllocator;
		typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

		managed_shared_memory segment(open_only, sharedMapName);          //segment size in bytes
		ShmemAllocator alloc_inst(segment.get_segment_manager());
		
		MyMap *mymap = segment.find<MyMap>(properMapName).first;

		mymap->clear();


		

	}


	__declspec(dllexport) void setSharedMemoryMap(char * sharedMapName, char * properMapName, std::map<int, std::string> yourmap)
	{
		using namespace boost::interprocess;

		//Remove shared memory on construction and destruction
		//struct shm_remove
		//{ 
		//	shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		//	~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		//} remover;
		shared_memory_object::remove(sharedMapName);

		//Shared memory front-end that is able to construct objects
		//associated with a c-string. Erase previous shared memory with the name
		//to be used and create the memory segment at the specified address and initialize resources
		managed_shared_memory segment
		(create_only
			, sharedMapName //segment name
			, 65536);          //segment size in bytes

							   //Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
							   //so the allocator must allocate that pair.
		typedef int    KeyType;
		typedef std::string  MappedType;
		typedef std::pair<const int, std::string> ValueType;

		//Alias an STL compatible allocator of for the map.
		//This allocator will allow to place containers
		//in managed shared memory segments
		typedef allocator<ValueType, managed_shared_memory::segment_manager>
			ShmemAllocator;

		//Alias a map of ints that uses the previous STL-like allocator.
		//Note that the third parameter argument is the ordering function
		//of the map, just like with std::map, used to compare the keys.
		typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

		//Initialize the shared memory STL-compatible allocator
		ShmemAllocator alloc_inst(segment.get_segment_manager());

		//Construct a shared memory map.
		//Note that the first parameter is the comparison function,
		//and the second one the allocator.
		//This the same signature as std::map's constructor taking an allocator
		MyMap *mymap =
			segment.construct<MyMap>(properMapName)      //object name
			(std::less<int>() //first  ctor parameter
				, alloc_inst);     //second ctor parameter

								   //Insert data in the map
		/*for (int i = 0; i < 100; ++i) {
			mymap->insert(std::pair<const int, float>(i, (float)i));
		}*/
		for (auto it = yourmap.begin(); it != yourmap.end(); it++)
		{
			mymap->insert(std::pair<const int, std::string>(it->first, it->second));
		}
	//	mymap->insert(std::pair<const int, std::string>(0, "booger"));
	//	mymap->insert(std::pair<const int, std::string>(1, "boobs"));


	//	return 0;
	}

	__declspec(dllexport) void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName)
	{
		using namespace boost::interprocess;
		typedef int    KeyType;
		typedef std::string  MappedType;
		typedef std::pair<const int, std::string> ValueType;

		//Alias an STL compatible allocator of for the map.
		//This allocator will allow to place containers
		//in managed shared memory segments
		typedef allocator<ValueType, managed_shared_memory::segment_manager>
			ShmemAllocator;
		typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

		managed_shared_memory segment(open_only, sharedMapName);          //segment size in bytes
		ShmemAllocator alloc_inst(segment.get_segment_manager());

		MyMap *mymap = segment.find<MyMap>(properMapName).first;

		//(std::less<int>() 			, alloc_inst);

		(*mymap)[index] = property;


	}

	__declspec(dllexport) void getSharedMemoryMap(char * sharedMapName, char * properMapName, std::map<int,std::string> &yourmap)
	{
		using namespace boost::interprocess;
		typedef int    KeyType;
		typedef std::string  MappedType;
		typedef std::pair<const int, std::string> ValueType;

		//Alias an STL compatible allocator of for the map.
		//This allocator will allow to place containers
		//in managed shared memory segments
		typedef allocator<ValueType, managed_shared_memory::segment_manager>
			ShmemAllocator;
		typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

		managed_shared_memory segment(open_only, sharedMapName );          //segment size in bytes
		ShmemAllocator alloc_inst(segment.get_segment_manager());

		MyMap *mymap = segment.find<MyMap>(properMapName).first;

			//(std::less<int>() 			, alloc_inst);
		
		int i=0;

		for (auto it = mymap->begin(); it != mymap->end(); it++)
		{
			yourmap[it->first] = it->second;
			printf("got:%s\n", it->second.c_str());
		}

		
		//printf("got:%s\n", mymap->operator[](1).c_str());
		//(*mymap)[2] = "dunno";

		//Find the vector using the c-string name
		//MyVector *myvector = segment.find<MyVector>("MyVector").first;

	}

}
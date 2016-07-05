#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include <stdio.h>
#include <boost/foreach.hpp>
#include <iostream>
#include <functional>
#include <utility>

using namespace boost::interprocess;

//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
//This allocator will allow placing containers in the segment
typedef allocator<std::string, managed_shared_memory::segment_manager>  ShmemAllocator;

//Alias a vector that uses the previous STL-like allocator so that allocates
//its values from the segment
typedef vector<std::string, ShmemAllocator> MyVector;

extern "C"
{

	__declspec(dllexport) void tearDown(char * sharedMemName)
	{
		//managed_shared_memory segment(open_only, sharedMemName);
		//MyVector *myvector = segment.find<MyVector>("MyVector").first;
		//segment.destroy<MyVector>("MyVector");

		shared_memory_object::remove(sharedMemName);
	/*	struct shm_remove
		{
			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
			~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		} remover;*/

	}

//Main function. For parent process argc == 1, for child process argc == 2
__declspec(dllexport) int host(char * sharedMemName, char * properVectorName)//int argc, char *argv[])
{
	//if (argc == 1) { //Parent process
					 //Remove shared memory on construction and destruction
		/*struct shm_remove
		{
			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
			~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		} remover;*/
	shared_memory_object::remove(sharedMemName);
		//Create a new segment with given name and size
		managed_shared_memory segment(create_only, sharedMemName, 65536);

		//Initialize shared memory STL-compatible allocator
		const ShmemAllocator alloc_inst(segment.get_segment_manager());

		//Construct a vector named "MyVector" in shared memory with argument alloc_inst
		MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);

	//	for (int i = 0; i < 100; ++i)  //Insert data in the vector
		//	myvector->push_back(i);
		myvector->push_back(std::string("hi there"));


		//Launch child process
		//std::string s(argv[0]); s += " child ";
		//if (0 != std::system(s.c_str()))
		//	return 1;
		printf("needfull\n");
		//Check child has destroyed the vector
		//if (segment.find<MyVector>("MyVector").first)
			//return 1;
	//}
	//	int c;
	//	std::cin >> c;

	return 0;
};

__declspec(dllexport) int client(char * sharedMemName, char * properVectorName)
{
	//Child process
		//Open the managed segment
	managed_shared_memory segment(open_only, sharedMemName);

	//Find the vector using the c-string name
	MyVector *myvector = segment.find<MyVector>("MyVector").first;

	//Use vector in reverse order
	//std::sort(myvector->rbegin(), myvector->rend());

	


	for (auto it = myvector->begin(); it != myvector->end(); ++it) 
	{
	
		//printf("got:%d\n", *it);
		printf("got:%s\n", (*it).c_str());
	}

	//When done, destroy the vector from the segment
	
		
	return 0;
}

}
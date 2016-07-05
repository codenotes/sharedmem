#include <string>
#include <map>



extern "C"
{
	int client(char *sharedMemName, char * properVectorName);
	int host(char *sharedMemName, char * properVectorName);
	void tearDown(char *sharedMemName);
	void getSharedMemoryMap(char * sharedMapName, std::map<int, std::string> &yourmap);
	void setSharedMemoryMap(char * sharedMapName, std::map<int, std::string> yourmap);
	void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName);
}

enum SharedMemMapInitProps
{
	INITIAL_SF_TO_LOAD_PATH=0
};

typedef std::map<int,std::string> _memMapType;
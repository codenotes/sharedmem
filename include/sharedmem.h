#include <string>
#include <map>




struct PresetMapStruct;


enum SharedMemMapInitProps
{
	INITIAL_SF_TO_LOAD_PATH = 0,
	PLUGIN_PATH = 1,
	DESCRIPTIVE_NAME = 2,
	NO_CONSOLE
};


extern "C"
{
	int client(char *sharedMemName, char * properVectorName);
	int host(char *sharedMemName, char * properVectorName);
	void tearDown(char *sharedMemName);
	void getSharedMemoryMap(char * sharedMapName, std::map<int, std::string> &yourmap);
	void setSharedMemoryMap(char * sharedMapName, std::map<int, std::string> yourmap);
	void addToSharedMap(int index, std::string property, char * sharedMapName, char * properMapName);
	void setSharedMemoryFileLocation(char * sharedMapFileName);
	void getSharedMemoryFileLocation(char * sharedMapFileName);
	void setSharedElement(char * sharedMapName, int index, std::string value);
	void getSharedElement(char * sharedMapName, int index, std::string &value);
	void setSharedElement2(char * sharedMapName, int index, char * value);
	void getSharedElement2(char * sharedMapName, int index, char * value);
	void getPresetArrayFromMap(char * sharedMapName, PresetMapStruct ** presetArray, int * size);
	void setPresetArrayFromMap(char * sharedMapName, PresetMapStruct * presetArray, int size);
	void deletePresetArrayFromMap(PresetMapStruct ** presetArray);
}


typedef std::map<int,std::string> _memMapType;
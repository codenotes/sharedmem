struct PresetMapStruct
{
	int presetID;
	int bank;
	int channel;
	char name[512];
	char sfName[1024];
	int currentSound;


};


#define ASSIGNPRESETS 0x7D
#define LOADSF 0x7E
#define LOADSF_2 0x7F
#define REMOVE_SF 0x66
#define REMOVE_PRESET 0x67
#define TEST_SYSEX 0x68
#define ASSIGNPRESETS_2 0x69
#define ASSIGNPRESETS_3 0x64
#define SET_GAIN 0x65
#define UNLOAD_PRESET 0x63
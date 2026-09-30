// Game/Class_10AA71F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

class Class_10AA71F0
{
public:
    int FUN_10aa71f0(FILE* File, int Param);

    char Unknown00[0x0C];
    int Unknown0C;
    char Unknown10[0x10];
    int Unknown20;
};

// FUNCTION: 0x10AA71F0 ?FUN_10aa71f0@Class_10AA71F0@@QAEHPAU_iobuf@@H@Z
int Class_10AA71F0::FUN_10aa71f0(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, Unknown0C, Unknown20);
    return 1;
}

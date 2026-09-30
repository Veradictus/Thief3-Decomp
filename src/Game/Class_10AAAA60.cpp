// Game/Class_10AAAA60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern char DAT_10e6d9e0[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

class Class_10AAAA60
{
public:
    int FUN_10aaaa60(FILE* File, int Param);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10AAAA60 ?FUN_10aaaa60@Class_10AAAA60@@QAEHPAU_iobuf@@H@Z
int Class_10AAAA60::FUN_10aaaa60(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, DAT_10e6d9e0, Unknown08);
    return 1;
}

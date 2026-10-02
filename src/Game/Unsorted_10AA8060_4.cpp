// Game/Unsorted_10AA8060_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6d988[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

class Class_10E6C170
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10aa80b0(FILE* File, int Param);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AA80B0 ?FUN_10aa80b0@Class_10E6C170@@UAEHPAU_iobuf@@H@Z
int Class_10E6C170::FUN_10aa80b0(FILE* File, int Param)
{
    fprintf(File, DAT_10e6d988, Unknown08);
    return 1;
}

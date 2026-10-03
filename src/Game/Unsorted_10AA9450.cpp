// Game/Unsorted_10AA9450.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern char DAT_10e6d9b4[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

struct Class_10E6C2E4_Unknown10
{
    const char* Unknown00;
    char Unknown04[0x14];
};

class Class_10E6C2E4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10aa96c0(FILE* File, int Param);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10E6C2E4_Unknown10* Unknown10;
};

// FUNCTION: 0x10AA96C0 ?FUN_10aa96c0@Class_10E6C2E4@@UAEHPAU_iobuf@@H@Z
int Class_10E6C2E4::FUN_10aa96c0(FILE* File, int Param)
{
    for (int i = 0; i < Unknown08; i++)
        fprintf(File, DAT_10e6c0f0, DAT_10e6d9b4, Unknown10[i].Unknown00);
    return 1;
}

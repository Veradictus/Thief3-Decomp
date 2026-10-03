// Game/Unsorted_10AA8420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern "C" int fprintf(FILE* File, const char* Format, ...);

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1090A780
{
public:
    ~Class_1090A780()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

class Class_10AA83E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();

    Class_1090A780 FUN_10aa83e0();
};

class Class_10E6D990 : public Class_10AA83E0
{
public:
    virtual int FUN_10aa8490(FILE* File, int Param);

    char Unknown04[4];
    char* Unknown08;
};

// FUNCTION: 0x10AA8490 ?FUN_10aa8490@Class_10E6D990@@UAEHPAU_iobuf@@H@Z
int Class_10E6D990::FUN_10aa8490(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, Unknown08, FUN_10aa83e0().Unknown00);
    return 1;
}

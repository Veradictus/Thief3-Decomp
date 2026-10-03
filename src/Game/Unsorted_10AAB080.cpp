// Game/Unsorted_10AAB080.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

extern char DAT_10e6c0f0[];

extern char DAT_10e6da0c[];

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

class Class_10AAB060
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();

    Class_1090A780 FUN_10aab060();
};

class Class_10E6DA1C : public Class_10AAB060
{
public:
    virtual int FUN_10aab080(FILE* File, int Param);
};

// FUNCTION: 0x10AAB080 ?FUN_10aab080@Class_10E6DA1C@@UAEHPAU_iobuf@@H@Z
int Class_10E6DA1C::FUN_10aab080(FILE* File, int Param)
{
    fprintf(File, DAT_10e6c0f0, DAT_10e6da0c, FUN_10aab060().Unknown00);
    return 1;
}

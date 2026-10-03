// Game/Unsorted_10B17100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1
};

class FName
{
public:
    FName(const char* Name, EFindName FindType = FNAME_Add);

    unsigned long Value;
};

extern const char DAT_10e6f4d8[];

class Class_10A174E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3(FName Name);
};

Class_10A174E0* FUN_10a18230();

class Class_10B15960
{
public:
    void FUN_10b15d70(int A);
};

class WindowManager : public Class_10B15960
{
};

extern WindowManager* GWindowManager;

class Class_10E5B7C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
};

class Class_10E79228 : public Class_10E5B7C8
{
public:
    virtual void FUN_10b17100();
};

// FUNCTION: 0x10B17100 ?FUN_10b17100@Class_10E79228@@UAEXXZ
void Class_10E79228::FUN_10b17100()
{
    if (FUN_10a18230()->Virtual3(DAT_10e6f4d8))
        GWindowManager->FUN_10b15d70(1);
}

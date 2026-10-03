// Game/Unsorted_10ACF9A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e7080c[];

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

class Class_10A174E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3(FName Name);
};

Class_10A174E0* FUN_10a18230();

class Class_10B82390;

class Class_10ACF9A0
{
public:
    int FUN_10acf9a0(int A);
    Class_10B82390* FUN_10acf690(int A);
};

// FUNCTION: 0x10ACF9A0 ?FUN_10acf9a0@Class_10ACF9A0@@QAEHH@Z
int Class_10ACF9A0::FUN_10acf9a0(int A)
{
    if (!FUN_10a18230()->Virtual3(DAT_10e7080c))
        return 0;
    return FUN_10acf690(A) != 0;
}

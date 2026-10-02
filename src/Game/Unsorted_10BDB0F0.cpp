// Game/Unsorted_10BDB0F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10E94578 : public Class_10BC4160
{
public:
    virtual void Virtual1();
    virtual void FUN_10bdb0f0();

    void FUN_10bc5b50();
};

// FUNCTION: 0x10BDB0F0 ?FUN_10bdb0f0@Class_10E94578@@UAEXXZ
void Class_10E94578::FUN_10bdb0f0()
{
    if (FUN_10bc4160()->FUN_10aa82d0() == 0)
        FUN_10bc5b50();
}

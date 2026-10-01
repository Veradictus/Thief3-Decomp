// Game/Unsorted_10BED160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e975a0[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E975A0 : public Class_10E90D70
{
public:
    Class_10E975A0* FUN_10bed440(int A, int B);

    bool Unknown40;
    int Unknown44;
    bool Unknown48;
    bool Unknown49;
    FArray Unknown4C;
    FArray Unknown58;
    int Unknown64;
    bool Unknown68;
    int Unknown6C;
    int Unknown70;
    int Unknown74;
    int Unknown78;
    int Unknown7C;
    bool Unknown80;
};

class Class_10E94578
{
public:
    virtual void Virtual0();

    void FUN_10bc5b50();
};

class Class_10E97488 : public Class_10E94578
{
public:
    virtual void Virtual0();
    virtual void FUN_10bee9a0();

    void FUN_10bedca0();

    char Unknown04[0x54];
    int Unknown58;
    int Unknown5C;
};

// FUNCTION: 0x10BED440 ?FUN_10bed440@Class_10E975A0@@QAEPAV1@HH@Z
Class_10E975A0* Class_10E975A0::FUN_10bed440(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown44 = 0;
    Unknown49 = false;
    Unknown4C.FArray::FArray();
    Unknown40 = true;
    Unknown00 = DAT_10e975a0;
    Unknown48 = true;
    Unknown58.FArray::FArray();
    Unknown64 = 0;
    Unknown68 = false;
    Unknown6C = 0;
    Unknown70 = 0;
    Unknown74 = 0;
    Unknown78 = 0;
    Unknown7C = 0;
    Unknown80 = false;
    return this;
}

// FUNCTION: 0x10BEE9A0 ?FUN_10bee9a0@Class_10E97488@@UAEXXZ
void Class_10E97488::FUN_10bee9a0()
{
    if (Unknown58 >= 1)
    {
        if (Unknown5C >= Unknown58)
            FUN_10bc5b50();
        else
            FUN_10bedca0();
    }
}

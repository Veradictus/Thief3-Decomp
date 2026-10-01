// Game/Unsorted_10BB3730.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10bb3830(int A, int B, int C);

class Class_10E8C8E4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10bb3ae0(int A, int B, int C);
};

int FUN_1090ecc0(void* A, void* B, int C);

class Class_10E90914
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual bool FUN_10bb44f0(Class_10E90914* Other);

    int Unknown04;
};

class Class_10BB48E0
{
public:
    int Unknown00;
};

extern Class_10BB48E0* DAT_10ff6694;

// FUNCTION: 0x10BB3AE0 ?FUN_10bb3ae0@Class_10E8C8E4@@UAEXHHH@Z
void Class_10E8C8E4::FUN_10bb3ae0(int A, int B, int C)
{
    FUN_10bb3830(A, B, C);
}

// FUNCTION: 0x10BB44F0 ?FUN_10bb44f0@Class_10E90914@@UAE_NPAV1@@Z
bool Class_10E90914::FUN_10bb44f0(Class_10E90914* Other)
{
    return FUN_1090ecc0(&Other->Unknown04, &Unknown04, 1) == 0;
}

// FUNCTION: 0x10BB4510 ?FUN_10bb4510@@YAHXZ
int FUN_10bb4510()
{
    if (DAT_10ff6694)
        return DAT_10ff6694->Unknown00;
    return 0;
}

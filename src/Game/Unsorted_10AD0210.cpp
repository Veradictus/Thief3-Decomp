// Game/Unsorted_10AD0210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f3e42c;

extern void* DAT_10f3e424;

extern void* DAT_10f3e43c;

extern int DAT_10f010c0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

extern Class_10F46DA0* DAT_10f46da0;

// FUNCTION: 0x10AD0900 ?FUN_10ad0900@@YGHHHH@Z
int __stdcall FUN_10ad0900(int p1, int p2, int p3)
{
    return 1;
}

// FUNCTION: 0x10AD0910 ?FUN_10ad0910@@YAHXZ
int FUN_10ad0910()
{
    return 0x91;
}

// FUNCTION: 0x10AD0920 ?FUN_10ad0920@@YGHHHH@Z
int __stdcall FUN_10ad0920(int A, int B, int C)
{
    DAT_10f46da0->Virtual5(0x44, DAT_10f35dec->Unknown08, -1, 0);
    return 1;
}

// FUNCTION: 0x10AD0950 ?FUN_10ad0950@@YAHXZ
int FUN_10ad0950()
{
    return 0x92;
}

// FUNCTION: 0x10AD0960 ?FUN_10ad0960@@YGHHHH@Z
int __stdcall FUN_10ad0960(int A, int B, int C)
{
    DAT_10f46da0->Virtual5(0x46, DAT_10f35dec->Unknown08, -1, 0);
    return 1;
}

// FUNCTION: 0x10AD09B0 ?FUN_10ad09b0@@YAHXZ
int FUN_10ad09b0()
{
    return 0x86;
}

// FUNCTION: 0x10AD09C0 ?FUN_10ad09c0@@YAHXZ
int FUN_10ad09c0()
{
    return 0x84;
}

// FUNCTION: 0x10AD0A00 ?FUN_10ad0a00@@YAHXZ
int FUN_10ad0a00()
{
    return 0x93;
}

// FUNCTION: 0x10AD0A10 ?FUN_10ad0a10@@YAHXZ
int FUN_10ad0a10()
{
    return 0x97;
}

// FUNCTION: 0x10AD0A20 ?FUN_10ad0a20@@YAHXZ
int FUN_10ad0a20()
{
    return 0x9b;
}

// FUNCTION: 0x10AD1C70 ?FUN_10ad1c70@@YAXXZ
void FUN_10ad1c70()
{
    DAT_10f3e42c++;
}

// FUNCTION: 0x10AD1D60 ?FUN_10ad1d60@@YAPAXXZ
void* FUN_10ad1d60()
{
    return DAT_10f3e424;
}

// FUNCTION: 0x10AD1D70 ?FUN_10ad1d70@@YAPAXXZ
void* FUN_10ad1d70()
{
    return DAT_10f3e43c;
}

// FUNCTION: 0x10AD2130 ?FUN_10ad2130@@YAPAHXZ
int* FUN_10ad2130()
{
    return (int*)&DAT_10f010c0;
}

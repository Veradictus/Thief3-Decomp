// Game/Unsorted_10C13CD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e98c80[];

class Class_10E98C80
{
public:
    Class_10E98C80();

    void* VTable;
    char Unknown04[8];
    int Unknown0c;
    int Unknown10;
    int Unknown14;
};

extern void* DAT_10e8c1f0[];

extern void* DAT_10e97bc8[];

class Class_10E6DC88
{
public:
    void FUN_10aaf500();
};

class Class_10E8C1F0 : public Class_10E6DC88
{
public:
    char Unknown00[0xc];
    void* Field0c;
    void FUN_10c13e80();
};

class Class_10E700F0 {
public:
    virtual void FUN_10c13ea0(int, int, int, int);
};

// FUNCTION: 0x10C13E80 ?FUN_10c13e80@Class_10E8C1F0@@QAEXXZ
void Class_10E8C1F0::FUN_10c13e80()
{
    *(void**)this = DAT_10e8c1f0;
    Field0c = DAT_10e97bc8;
    FUN_10aaf500();
}

// FUNCTION: 0x10C13EA0 ?FUN_10c13ea0@Class_10E700F0@@UAEXHHHH@Z
void Class_10E700F0::FUN_10c13ea0(int p1, int p2, int p3, int p4)
{
}

// FUNCTION: 0x10C15B90 ??0Class_10E98C80@@QAE@XZ
Class_10E98C80::Class_10E98C80()
{
    VTable = DAT_10e98c80;
    Unknown0c = 0;
    Unknown10 = 0;
    Unknown14 = 0;
}

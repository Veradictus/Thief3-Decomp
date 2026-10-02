// Game/Unsorted_10A6A150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B660
{
public:
    virtual void FUN_10a6ad50(int Type, int A, int B, int C);

    void FUN_10a6ac80(int A, int B, int C);
};

class Class_1091ca00
{
public:
    bool FUN_1091ca00(int p1);
};

class Class_1091DEE0
{
public:
    Class_1091ca00* FUN_1091dee0(int p1);
};

extern Class_1091DEE0* DAT_10f2c928;

class Class_10A6A150
{
public:
    void FUN_10a6a150();

    char Unknown00[4];
    bool Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A6A150 ?FUN_10a6a150@Class_10A6A150@@QAEXXZ
void Class_10A6A150::FUN_10a6a150()
{
    Unknown04 = false;
    Class_1091DEE0* Mgr = DAT_10f2c928;
    if (Mgr)
    {
        Class_1091ca00* Obj = Mgr->FUN_1091dee0(0);
        if (Obj)
            Obj->FUN_1091ca00(Unknown08);
    }
}

// FUNCTION: 0x10A6AD50 ?FUN_10a6ad50@Class_10E6B660@@UAEXHHHH@Z
void Class_10E6B660::FUN_10a6ad50(int Type, int A, int B, int C)
{
    if (Type >= 0x2a && Type <= 0x2b)
        FUN_10a6ac80(A, B, C);
}

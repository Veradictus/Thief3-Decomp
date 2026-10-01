// Game/Unsorted_10B364E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520_Member;

class Class_10B1D660
{
public:
    void FUN_10b1d660();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
    Class_10B1D660* Unknown0C;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E7C3A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10b36620(int p1, int p2, int p3);
};

class Class_10B1B8A0
{
public:
    void FUN_10b1b8a0(int A);
};

Class_10B1B8A0* FUN_10b1b600();

class Class_10B374E0
{
public:
    void FUN_10b374e0(int A, Class_10B374E0* B, int C);

    char Unknown00[0x4];
    int Unknown04;
};

// FUNCTION: 0x10B36620 ?FUN_10b36620@Class_10E7C3A4@@UAEHHHH@Z
int Class_10E7C3A4::FUN_10b36620(int p1, int p2, int p3)
{
    DAT_10f35dec->Unknown0C->FUN_10b1d660();
    return 1;
}

// FUNCTION: 0x10B374E0 ?FUN_10b374e0@Class_10B374E0@@QAEXHPAV1@H@Z
void Class_10B374E0::FUN_10b374e0(int A, Class_10B374E0* B, int C)
{
    if (B->Unknown04 == Unknown04)
        FUN_10b1b600()->FUN_10b1b8a0(A);
}

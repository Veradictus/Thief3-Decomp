// Game/Unsorted_10A7DDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef unsigned char BYTE;

struct FColor
{
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}

    BYTE B;
    BYTE G;
    BYTE R;
    BYTE A;
};

class Class_10E6BED8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void FUN_10a7dde0(int A, BYTE* Data, int C, int D);
};

// FUNCTION: 0x10A7DDE0 ?FUN_10a7dde0@Class_10E6BED8@@UAEXHPAEHH@Z
void Class_10E6BED8::FUN_10a7dde0(int A, BYTE* Data, int C, int D)
{
    FColor* Dest = (FColor*)Data;
    FColor Color(10, 5, 60, 255);
    for (int Y = 0; Y < 8; Y++)
    {
        for (int X = 0; X < 8; X++)
        {
            *Dest++ = Color;
        }
    }
}

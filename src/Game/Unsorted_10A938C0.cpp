// Game/Unsorted_10A938C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10a46770
{
public:
    void FUN_10a46770(int p1);
};

class APlayerPawn
{
public:
    char Unknown00[0x208];
    Class_10a46770 Unknown208;
};

APlayerPawn* FUN_10983ca0(APlayerPawn* Obj);

struct Struct_10AA3520
{
    char Unknown00[0x08];
    APlayerPawn* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E6CC64
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a939b0(int A, int B, int C);
};

// FUNCTION: 0x10A939B0 ?FUN_10a939b0@Class_10E6CC64@@UAEHHHH@Z
int Class_10E6CC64::FUN_10a939b0(int A, int B, int C)
{
    if (DAT_10f35dec)
    {
        APlayerPawn* Obj = DAT_10f35dec->Unknown08;
        if (Obj)
        {
            APlayerPawn* Pawn = FUN_10983ca0(Obj);
            if (Pawn)
                Pawn->Unknown208.FUN_10a46770(0);
        }
    }
    return 1;
}

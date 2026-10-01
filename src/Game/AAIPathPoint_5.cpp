// Game/AAIPathPoint_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AAIPathPoint;

class Class_10993EC0
{
public:
    virtual void FUN_10adb3a0();
};

class Class_10BC0AB0
{
public:
    void FUN_10bc0ab0(AAIPathPoint* P);
};

class AAIPathPoint : public Class_10993EC0
{
public:
    virtual void Virtual0();

    char Unknown04[0xBC];
    Class_10BC0AB0 UnknownC0;
};

// FUNCTION: 0x10BBEF80 ?Virtual0@AAIPathPoint@@UAEXXZ
void AAIPathPoint::Virtual0()
{
    Class_10993EC0::FUN_10adb3a0();
    UnknownC0.FUN_10bc0ab0(this);
}

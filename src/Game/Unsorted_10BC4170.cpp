// Game/Unsorted_10BC4170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bf7f90
{
public:
    void FUN_10bf7f90(int p1, int p2);
};

class Class_10E8BE68_Member
{
public:
    char Unknown00[0xc];
    Class_10bf7f90* Unknown0c;
};

class Class_10E8BE68
{
public:
    virtual void Virtual0();

    Class_10E8BE68_Member* Unknown04;
};

// FUNCTION: 0x10BC41F0 ?Virtual0@Class_10E8BE68@@UAEXXZ
void Class_10E8BE68::Virtual0()
{
    Unknown04->Unknown0c->FUN_10bf7f90(0, 1);
}

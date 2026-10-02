// Game/Unsorted_10BB0B10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40;

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

struct Struct_10BB0C30
{
    char Unknown00[0x10];
    Class_10DBD510* Unknown10;
};

class Struct_10BB0B90
{
public:
    char Unknown00[0x118];
    Struct_10BB0C30* Unknown118;
};

Struct_10BB0B90* FUN_10bb0b90(int A);

// FUNCTION: 0x10BB0C30 ?FUN_10bb0c30@@YAPAVClass_10BBDB40@@H@Z
Class_10BBDB40* FUN_10bb0c30(int A)
{
    Struct_10BB0B90* Owner = FUN_10bb0b90(A);
    if (Owner && Owner->Unknown118 && Owner->Unknown118->Unknown10)
        return Owner->Unknown118->Unknown10->FUN_10dbd510();
    return 0;
}

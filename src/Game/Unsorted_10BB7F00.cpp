// Game/Unsorted_10BB7F00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB10
{
public:
    int FUN_10bbdb10(int Id);
};

class Class_10BBDB40 : public Class_10BBDB10
{
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

class Class_10BB7F00
{
public:
    int FUN_10bb7f00();

    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

// FUNCTION: 0x10BB7F00 ?FUN_10bb7f00@Class_10BB7F00@@QAEHXZ
int Class_10BB7F00::FUN_10bb7f00()
{
    return Unknown08->FUN_10dbd510()->FUN_10bbdb10(0x40800544);
}

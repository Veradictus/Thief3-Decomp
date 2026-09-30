// Game/Class_10A35300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A34B90
{
public:
    void FUN_10a34b90(int A);
};

class Class_10A34CD0
{
public:
    void FUN_10a34cd0(int A);
};

class Class_10A35300
{
public:
    void FUN_10a35300(int A);

    char Unknown00[0x4];
    Class_10A34B90 Unknown04;
    char Unknown05[0x1B];
    Class_10A34CD0 Unknown20;
};

// FUNCTION: 0x10A35300 ?FUN_10a35300@Class_10A35300@@QAEXH@Z
void Class_10A35300::FUN_10a35300(int A)
{
    Unknown04.FUN_10a34b90(0x80);
    Unknown20.FUN_10a34cd0(0x80);
}

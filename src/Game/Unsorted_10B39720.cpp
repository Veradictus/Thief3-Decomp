// Game/Unsorted_10B39720.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_Field0c_D {
public:
    void FUN_10b46fd0();
};

class Class_10B39780 {
public:
    char Unknown00[0xc];
    Class_Field0c_D* Unknown0c;

    void FUN_10b39780();
};

class Class_10B3A460
{
public:
    char Unknown00[0x2C];

    Class_10B3A460* FUN_10b3a460(int p1);
};

// FUNCTION: 0x10B39780 ?FUN_10b39780@Class_10B39780@@QAEXXZ
void Class_10B39780::FUN_10b39780()
{
    Unknown0c->FUN_10b46fd0();
}

// FUNCTION: 0x10B3A460 ?FUN_10b3a460@Class_10B3A460@@QAEPAV1@H@Z
Class_10B3A460* Class_10B3A460::FUN_10b3a460(int p1)
{
    return this + p1;
}

// Game/Class_10E939E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e939e0[];

class Class_10E93710
{
public:
    Class_10E93710(int A, int B);

    void** Unknown00;
};

class Class_10E939E0 : public Class_10E93710
{
public:
    Class_10E939E0* FUN_10bd51e0(int A, int B);
};

// FUNCTION: 0x10BD51E0 ?FUN_10bd51e0@Class_10E939E0@@QAEPAV1@HH@Z
Class_10E939E0* Class_10E939E0::FUN_10bd51e0(int A, int B)
{
    this->Class_10E93710::Class_10E93710(A, B);
    Unknown00 = DAT_10e939e0;
    return this;
}

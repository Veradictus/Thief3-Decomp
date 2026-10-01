// Game/Unsorted_10C3EDB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9b570[];

void FUN_10a37340(int p1);

class Class_10E9B570
{
public:
    Class_10E9B570* FUN_10c3edb0(int Id);

    void** Unknown00;
    int Unknown04;
};

// FUNCTION: 0x10C3EDB0 ?FUN_10c3edb0@Class_10E9B570@@QAEPAV1@H@Z
Class_10E9B570* Class_10E9B570::FUN_10c3edb0(int Id)
{
    Unknown04 = Id;
    Unknown00 = DAT_10e9b570;
    FUN_10a37340(Id);
    return this;
}

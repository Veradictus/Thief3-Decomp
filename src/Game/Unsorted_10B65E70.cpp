// Game/Unsorted_10B65E70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A556F0
{
public:
    void FUN_10a556f0(int A);
};

class Class_10B65E70
{
public:
    void FUN_10b65e70(int A);

    char Unknown00[0x200];
    Class_10A556F0* Unknown200;
};

// FUNCTION: 0x10B65E70 ?FUN_10b65e70@Class_10B65E70@@QAEXH@Z
void Class_10B65E70::FUN_10b65e70(int A)
{
    if (Unknown200)
        Unknown200->FUN_10a556f0(A);
}

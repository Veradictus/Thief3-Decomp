// Game/Unsorted_10A58520.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A24370
{
public:
    void FUN_10a24370(int p1);
};

class Class_10A588A0
{
public:
    void FUN_10a588a0(int p1);

    char Unknown00[0x188];
    Class_10A24370* Unknown188;
};

// FUNCTION: 0x10A588A0 ?FUN_10a588a0@Class_10A588A0@@QAEXH@Z
void Class_10A588A0::FUN_10a588a0(int p1)
{
    if (Unknown188)
        Unknown188->FUN_10a24370(p1);
}

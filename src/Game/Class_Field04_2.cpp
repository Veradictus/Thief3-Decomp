// Game/Class_Field04_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AD70
{
public:
    void FUN_10b7ad70();
    void FUN_10b7ae90();
};

class Class_Field04
{
public:
    void FUN_10b46f90();

    char Unknown00[0x08];
    Class_10B7AD70* Unknown08[2];
};

// FUNCTION: 0x10B46F90 ?FUN_10b46f90@Class_Field04@@QAEXXZ
void Class_Field04::FUN_10b46f90()
{
    for (int i = 0; i < 2; i++)
        Unknown08[i]->FUN_10b7ad70();
}

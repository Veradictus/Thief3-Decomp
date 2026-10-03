// Game/Unsorted_10B91320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10DAAF90
{
public:
    void FUN_10daaf90(const Class_10DAAF90* Other);

    char Unknown00[0x10];
};

class Class_10B912E0
{
public:
    void FUN_10b90980(int Count);

    int Unknown00;
    int Unknown04;
    Class_10DAAF90* Unknown08;
};

class Class_10B91800 : public Class_10B912E0
{
public:
    void FUN_10b91320(int A);
};

// FUNCTION: 0x10B91320 ?FUN_10b91320@Class_10B91800@@QAEXH@Z
void Class_10B91800::FUN_10b91320(int A)
{
    Class_10B91800* Other = (Class_10B91800*)A;
    FUN_10b90980(Other->Unknown00);
    for (int i = 0; i < Unknown00; i++)
        Unknown08[i].FUN_10daaf90(&Other->Unknown08[i]);
}

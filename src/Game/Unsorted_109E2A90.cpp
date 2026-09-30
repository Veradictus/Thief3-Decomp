// Game/Unsorted_109E2A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E36F0
{
public:
    void FUN_109e36f0(int a, int b);

    char Unknown00[0xD0];
    int UnknownD0;
    int UnknownD4;
};

class Class_109E3710
{
public:
    void FUN_109e3710(int* p1, int* p2);
    char Unknown00[0xD0];
    int UnknownD0;
    int UnknownD4;
};

// FUNCTION: 0x109E36F0 ?FUN_109e36f0@Class_109E36F0@@QAEXHH@Z
void Class_109E36F0::FUN_109e36f0(int a, int b)
{
    UnknownD0 = a;
    UnknownD4 = b;
}

// FUNCTION: 0x109E3710 ?FUN_109e3710@Class_109E3710@@QAEXPAH0@Z
void Class_109E3710::FUN_109e3710(int* p1, int* p2)
{
    *p1 = UnknownD0;
    *p2 = UnknownD4;
}

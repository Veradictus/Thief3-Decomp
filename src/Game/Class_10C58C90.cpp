// Game/Class_10C58C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C49740
{
public:
    void FUN_10c49740(int* A, int B);
};

struct Info_10C58C90
{
    char Unknown00[0xDC];
    Class_10C49740 UnknownDC;
};

class Class_10C58C90
{
public:
    void FUN_10c58c90(int A, int B);

    Info_10C58C90* Unknown00;
};

// FUNCTION: 0x10C58C90 ?FUN_10c58c90@Class_10C58C90@@QAEXHH@Z
void Class_10C58C90::FUN_10c58c90(int A, int B)
{
    int Value = A;
    Unknown00->UnknownDC.FUN_10c49740(&Value, B);
}

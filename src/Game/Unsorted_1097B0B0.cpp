// Game/Unsorted_1097B0B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1097B760
{
public:
    void FUN_1097b760(int A);
    void FUN_10979d20(int A, int B, int C);
    void FUN_10979670(int A, int B);
};


class Class_1097CBE0
{
public:
    void FUN_1097c880(int A);
    void FUN_1097cbe0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x1097B760 ?FUN_1097b760@Class_1097B760@@QAEXH@Z
void Class_1097B760::FUN_1097b760(int A)
{
    FUN_10979d20(A, 0, 0);
    FUN_10979670(A, 0x1000);
}

// FUNCTION: 0x1097CBE0 ?FUN_1097cbe0@Class_1097CBE0@@QAEXXZ
void Class_1097CBE0::FUN_1097cbe0()
{
    FUN_1097c880(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

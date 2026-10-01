// Game/Unsorted_10C40750.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C40C50
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    bool Unknown11;
};

class Class_10C40160
{
public:
    Struct_10C40C50* FUN_10c40160(int A, int B);
};

class Class_10C40C50
{
public:
    void FUN_10c40c50(int A, int B, int C, int* D, bool E);

    int Unknown00;
    Class_10C40160 Unknown04;
};

// FUNCTION: 0x10C40C50 ?FUN_10c40c50@Class_10C40C50@@QAEXHHHPAH_N@Z
void Class_10C40C50::FUN_10c40c50(int A, int B, int C, int* D, bool E)
{
    Struct_10C40C50* Node = Unknown04.FUN_10c40160(1, 0);
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = C;
        Node->Unknown0C = *D;
        Node->Unknown10 = E;
        Node->Unknown11 = false;
    }
}

// Game/Unsorted_10A32DA0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A334E0
{
    Struct_10A334E0() : Unknown00(0), Unknown04(-1), Unknown08(-1), Unknown0C(-1) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E66474
{
public:
    virtual void FUN_10a33ce0(int A, int B, int C, int D);

    void FUN_10a33040(int Index, Struct_10A334E0 Item);
    void FUN_10a334e0();
    void FUN_10a33b70(int A, int B, int C);
    void FUN_10a33c60();

    char Unknown04[0x50];
    bool Unknown54;
};

// FUNCTION: 0x10A33CE0 ?FUN_10a33ce0@Class_10E66474@@UAEXHHHH@Z
void Class_10E66474::FUN_10a33ce0(int A, int B, int C, int D)
{
    switch (A)
    {
    case 1:
        FUN_10a33c60();
        break;
    case 0x5A:
        FUN_10a33c60();
        if (Unknown54)
        {
            FUN_10a334e0();
            FUN_10a33c60();
        }
        break;
    case 0x70:
        FUN_10a33b70(B, C, D);
        break;
    }
}

// Game/Unsorted_10A32DA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A334E0
{
    Struct_10A334E0() : Unknown00(0), Unknown04(-1), Unknown08(-1), Unknown0C(-1) {}
    Struct_10A334E0(const Struct_10A334E0& Other) : Unknown00(Other.Unknown00), Unknown04(Other.Unknown04), Unknown08(Other.Unknown08), Unknown0C(Other.Unknown0C) {}
    ~Struct_10A334E0();

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

// FUNCTION: 0x10A334E0 ?FUN_10a334e0@Class_10E66474@@QAEXXZ
void Class_10E66474::FUN_10a334e0()
{
    for (int i = 0; i < 5; i++)
        FUN_10a33040(i, Struct_10A334E0());
}

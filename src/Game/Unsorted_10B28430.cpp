// Game/Unsorted_10B28430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7AD54
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10b28b60();

    void FUN_10b289f0(bool p1);
};

struct Struct_10B28950
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B28950
{
public:
    void FUN_10b28430(int A);
    void FUN_10b28950(int A, const Struct_10B28950& B, const Struct_10B28950& C, const Struct_10B28950& D, int E,
                      int F, int G);

    char Unknown00[0x50];
    int Unknown50;
    Struct_10B28950 Unknown54;
    Struct_10B28950 Unknown60;
    Struct_10B28950 Unknown6C;
    int Unknown78;
    int Unknown7C;
};

// FUNCTION: 0x10B28950 ?FUN_10b28950@Class_10B28950@@QAEXHABUStruct_10B28950@@00HHH@Z
void Class_10B28950::FUN_10b28950(int A, const Struct_10B28950& B, const Struct_10B28950& C, const Struct_10B28950& D,
                                  int E, int F, int G)
{
    Unknown50 = E;
    Unknown54 = B;
    Unknown60 = C;
    Unknown6C = D;
    Unknown78 = F;
    Unknown7C = G;
    FUN_10b28430(A);
}

// FUNCTION: 0x10B28B60 ?FUN_10b28b60@Class_10E7AD54@@UAEXXZ
void Class_10E7AD54::FUN_10b28b60()
{
    FUN_10b289f0(false);
}

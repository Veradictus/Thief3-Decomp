// Game/Unsorted_10B79180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B79A30
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B79A30
{
public:
    void FUN_10b79340(int A);
    void FUN_10b79a30(int A, const Struct_10B79A30& B, const Struct_10B79A30& C, const Struct_10B79A30& D, int E,
                      int F, int G);

    char Unknown00[0x50];
    int Unknown50;
    Struct_10B79A30 Unknown54;
    Struct_10B79A30 Unknown60;
    Struct_10B79A30 Unknown6C;
    int Unknown78;
    int Unknown7C;
};

// FUNCTION: 0x10B79A30 ?FUN_10b79a30@Class_10B79A30@@QAEXHABUStruct_10B79A30@@00HHH@Z
void Class_10B79A30::FUN_10b79a30(int A, const Struct_10B79A30& B, const Struct_10B79A30& C, const Struct_10B79A30& D,
                                  int E, int F, int G)
{
    Unknown50 = E;
    Unknown54 = B;
    Unknown60 = C;
    Unknown6C = D;
    Unknown78 = F;
    Unknown7C = G;
    FUN_10b79340(A);
}

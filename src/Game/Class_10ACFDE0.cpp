// Game/Class_10ACFDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330;

struct Struct_10AD0040
{
    char Unknown00[0xE8];
    Class_1098E330* UnknownE8;
    int UnknownEC;
};

class Class_10ACFDE0
{
public:
    int FUN_10acfde0(int A, Class_1098E330* B);
    int FUN_10ad0040(int A, Struct_10AD0040* B);
};

// FUNCTION: 0x10AD0040 ?FUN_10ad0040@Class_10ACFDE0@@QAEHHPAUStruct_10AD0040@@@Z
int Class_10ACFDE0::FUN_10ad0040(int A, Struct_10AD0040* B)
{
    return FUN_10acfde0(A, B->UnknownEC == 0 ? 0 : B->UnknownE8);
}

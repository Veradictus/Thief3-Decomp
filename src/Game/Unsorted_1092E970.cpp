// Game/Unsorted_1092E970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_1092E970
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1092E8F0
{
public:
    void FUN_1091f380(int A);
    void FUN_1092e970(const Class_1092E8F0& Other);

    int Unknown00;
    int Unknown04;
    Struct_1092E970* Unknown08;
};

// FUNCTION: 0x1092E970 ?FUN_1092e970@Class_1092E8F0@@QAEXABV1@@Z
void Class_1092E8F0::FUN_1092e970(const Class_1092E8F0& Other)
{
    FUN_1091f380(Other.Unknown00);
    for (int i = 0; i < Unknown00; i++)
        Unknown08[i] = Other.Unknown08[i];
}

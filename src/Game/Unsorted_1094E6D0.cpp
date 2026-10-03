// Game/Unsorted_1094E6D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10F2C744
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(int A, int B, int C, const char* Name, int* Out);
};

extern Class_10F2C744* DAT_10f2c744;

struct Struct_1094E6D0_Group
{
    char Unknown00[0x18];
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
};

class Class_1094E6D0
{
public:
    void FUN_1094e6d0(int Index, int A, int B, int C, int D);

    char Unknown00[0x108];
    Struct_1094E6D0_Group* Unknown108;
    char Unknown10C[8];
    int Unknown114;
    int Unknown118;
};

// FUNCTION: 0x1094E6D0 ?FUN_1094e6d0@Class_1094E6D0@@QAEXHHHHH@Z
void Class_1094E6D0::FUN_1094e6d0(int Index, int A, int B, int C, int D)
{
    Unknown108[Index].Unknown18 = A;
    Unknown108[Index].Unknown1C = B;
    Unknown108[Index].Unknown20 = C;
    Unknown108[Index].Unknown24 = D;
    if (Index == 0)
    {
        FUN_10905aa0()->Virtual8(0, 0);
        DAT_10f2c744->Virtual3(0, 0x10, 0, "BlendMesh::m_ShadowVertex", &Unknown114);
        DAT_10f2c744->Virtual3(1, 0x10, 0, "BlendMesh::m_ShadowVertex", &Unknown118);
        FUN_10905aa0()->Virtual9();
    }
}

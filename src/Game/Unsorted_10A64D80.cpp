// Game/Unsorted_10A64D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A64E20 {
public:
    char Unknown00[0x168];
    int Unknown168;
    void FUN_10a64e20(int* in);
};

struct Class_10A64E30_Member
{
    int Unknown00;
};

class Class_10A64E30
{
public:
    char Unknown00[0x164];
    Class_10A64E30_Member Unknown164;
    void FUN_10a64e30(const Class_10A64E30_Member* p1);
};

// FUNCTION: 0x10A64E20 ?FUN_10a64e20@Class_10A64E20@@QAEXPAH@Z
void Class_10A64E20::FUN_10a64e20(int* in)
{
    Unknown168 = *in;
}

// FUNCTION: 0x10A64E30 ?FUN_10a64e30@Class_10A64E30@@QAEXPBUClass_10A64E30_Member@@@Z
void Class_10A64E30::FUN_10a64e30(const Class_10A64E30_Member* p1)
{
    Unknown164 = *p1;
}

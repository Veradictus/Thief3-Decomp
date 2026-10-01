// Game/Unsorted_10BC2090.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bbefb0;

struct Struct_10BC2090
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10BC2090
{
public:
    void FUN_10bc1c00(void* p1, Class_10bbefb0* p2);
    void FUN_10bc2090(Class_10bbefb0* p1);

    Struct_10BC2090* Unknown00;
};

// FUNCTION: 0x10BC2090 ?FUN_10bc2090@Class_10BC2090@@QAEXPAVClass_10bbefb0@@@Z
void Class_10BC2090::FUN_10bc2090(Class_10bbefb0* p1)
{
    FUN_10bc1c00(&Unknown00->Unknown0C, p1);
}

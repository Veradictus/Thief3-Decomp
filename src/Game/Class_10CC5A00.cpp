// Game/Class_10CC5A00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10CC5A00
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

struct Struct_10CC5A00_30
{
    int Unknown00;
    char Unknown04[0xC];
    int Unknown10;
    char Unknown14[0xC];
    int Unknown20;
};

class Class_10CC5A00
{
public:
    void FUN_10cc5a00(Struct_10CC5A00* Out);

    char Unknown00[0x30];
    Struct_10CC5A00_30* Unknown30;
};

// FUNCTION: 0x10CC5A00 ?FUN_10cc5a00@Class_10CC5A00@@QAEXPAUStruct_10CC5A00@@@Z
void Class_10CC5A00::FUN_10cc5a00(Struct_10CC5A00* Out)
{
    Out->Unknown00 = Unknown30->Unknown00;
    Out->Unknown04 = Unknown30->Unknown10;
    Out->Unknown08 = Unknown30->Unknown20;
    Out->Unknown0C = 0;
}

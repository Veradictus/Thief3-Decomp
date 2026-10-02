// Game/Unsorted_10B4DBB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B4DFD0
{
    char Unknown00[0x550];
    char Unknown550;
};

class Class_10E7E970
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10b4dfd0(Struct_10B4DFD0* A);

    void FUN_10b4da00(Struct_10B4DFD0* A);

    char Unknown04[0xD];
    bool Unknown11;
};

// FUNCTION: 0x10B4DFD0 ?FUN_10b4dfd0@Class_10E7E970@@UAEXPAUStruct_10B4DFD0@@@Z
void Class_10E7E970::FUN_10b4dfd0(Struct_10B4DFD0* A)
{
    if (A->Unknown550 == 2 && !Unknown11)
        FUN_10b4da00(A);
    Virtual4();
}

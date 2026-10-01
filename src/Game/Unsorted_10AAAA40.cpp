// Game/Unsorted_10AAAA40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d990(void* Writer, int* Value);

class Class_10E6D9E8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aaaa40(void* Writer, int Unused1, int Unused2);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AAAA40 ?FUN_10aaaa40@Class_10E6D9E8@@UAEXPAXHH@Z
void Class_10E6D9E8::FUN_10aaaa40(void* Writer, int Unused1, int Unused2)
{
    FUN_10d3d990(Writer, &Unknown08);
}

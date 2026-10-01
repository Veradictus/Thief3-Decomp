// Game/Unsorted_10AAB570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d2d0(void* Writer, int Value);

class Class_10E6DA40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aab570(void* Writer, int Unused1, int Unused2);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AAB570 ?FUN_10aab570@Class_10E6DA40@@UAEXPAXHH@Z
void Class_10E6DA40::FUN_10aab570(void* Writer, int Unused1, int Unused2)
{
    FUN_10d3d2d0(Writer, Unknown08);
}

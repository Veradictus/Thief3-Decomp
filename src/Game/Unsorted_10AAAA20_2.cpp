// Game/Unsorted_10AAAA20_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3ddc0(void* Reader, int* Out);

class Class_10E6D9E8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aaaa20(void* Reader, int Version, int Unused);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AAAA20 ?FUN_10aaaa20@Class_10E6D9E8@@UAEXPAXHH@Z
void Class_10E6D9E8::FUN_10aaaa20(void* Reader, int Version, int Unused)
{
    FUN_10d3ddc0(Reader, &Unknown08);
}

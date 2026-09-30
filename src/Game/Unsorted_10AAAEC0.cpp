// Game/Unsorted_10AAAEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d3b0(void* Reader, int* Out);

class Class_10E6DA40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aab540(void* Reader, int Version, int Unused);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AAB540 ?FUN_10aab540@Class_10E6DA40@@UAEXPAXHH@Z
void Class_10E6DA40::FUN_10aab540(void* Reader, int Version, int Unused)
{
    if (Version > 12)
    {
        FUN_10d3d3b0(Reader, &Version);
        Unknown08 = Version;
    }
}

// Game/Unsorted_10B55830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B56210
{
public:
    virtual void Virtual0();
    virtual bool Virtual1(int A, int B, int C);
};

class Class_10E81DE8
{
public:
    virtual void Virtual0();
    virtual bool FUN_10b56210(int A, int B, int C);

    char Unknown04[0x1CC];
    Object_10B56210* Unknown1D0;
};

// FUNCTION: 0x10B56210 ?FUN_10b56210@Class_10E81DE8@@UAE_NHHH@Z
bool Class_10E81DE8::FUN_10b56210(int A, int B, int C)
{
    if (Unknown1D0 && Unknown1D0->Virtual1(A, B, C))
        return true;
    return false;
}

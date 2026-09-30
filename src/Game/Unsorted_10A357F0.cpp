// Game/Unsorted_10A357F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Static_10A35EA0
{
    char Unknown00[0xC];
    bool Unknown0C;

    Static_10A35EA0() { Unknown0C = false; }
    ~Static_10A35EA0() {}
};

class Class_10A35EE0
{
public:
    void FUN_10a35ee0(int p1, int p2);
    void FUN_10a35940();

    char Unknown00[0x80];
    int Unknown80;
};

// FUNCTION: 0x10A35EA0 ?FUN_10a35ea0@@YAPAUStatic_10A35EA0@@XZ
Static_10A35EA0* FUN_10a35ea0()
{
    static Static_10A35EA0 Instance;
    return &Instance;
}

// FUNCTION: 0x10A35EE0 ?FUN_10a35ee0@Class_10A35EE0@@QAEXHH@Z
void Class_10A35EE0::FUN_10a35ee0(int p1, int p2)
{
    Unknown80 = p1;
    FUN_10a35940();
}

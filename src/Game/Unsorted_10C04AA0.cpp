// Game/Unsorted_10C04AA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memmove(void* Dest, const void* Src, unsigned Count);

struct Struct_10C04B70
{
    char Unknown00[0x1C];
};

class Class_10C04B70
{
public:
    void FUN_10c04b70(int From, int To, int Count);

    int Unknown00;
    int Unknown04;
    Struct_10C04B70* Unknown08;
};

// FUNCTION: 0x10C04B70 ?FUN_10c04b70@Class_10C04B70@@QAEXHHH@Z
void Class_10C04B70::FUN_10c04b70(int From, int To, int Count)
{
    if (From != To && Count)
        memmove(Unknown08 + To, Unknown08 + From, Count * sizeof(Struct_10C04B70));
}

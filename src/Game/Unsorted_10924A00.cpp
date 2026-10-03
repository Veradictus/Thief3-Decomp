// Game/Unsorted_10924A00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10924B30_Slot
{
    void* Unknown00;
    char Unknown04[0x1C];
};

class Class_10924B30
{
public:
    bool FUN_10924b30(int Index, int A);
    bool FUN_109246b0(Struct_10924B30_Slot* Slot, int A);

    char Unknown00[0x48];
    Struct_10924B30_Slot Unknown48[3];
    int UnknownA8;
};

// FUNCTION: 0x10924B30 ?FUN_10924b30@Class_10924B30@@QAE_NHH@Z
bool Class_10924B30::FUN_10924b30(int Index, int A)
{
    if (Index != -1)
    {
        if (Unknown48[Index].Unknown00)
        {
            if (FUN_109246b0(&Unknown48[Index], A))
                UnknownA8 = Index;
        }
    }
    return false;
}

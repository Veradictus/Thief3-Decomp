// Game/Unsorted_10B22C40_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B22C80
{
    char Unknown00[0x440];
    int Unknown440;
    char Unknown444[0x1C];
    int Unknown460;
};

class Class_10B22D60
{
public:
    void FUN_10b229c0(void** Slot, int Value);
    void FUN_10b22c80();

    char Unknown00[4];
    Struct_10B22C80* Unknown04;
    char Unknown08[0x88];
    void* Unknown90;
    void* Unknown94;
};

// FUNCTION: 0x10B22C80 ?FUN_10b22c80@Class_10B22D60@@QAEXXZ
void Class_10B22D60::FUN_10b22c80()
{
    FUN_10b229c0(&Unknown90, 0);
    if (Unknown04->Unknown440)
        FUN_10b229c0(&Unknown94, 0x1a);
    else
        FUN_10b229c0(&Unknown94, 0x17);
    Unknown04->Unknown460 = 0;
}

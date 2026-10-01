// Game/Unsorted_10B1D1C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

extern int DAT_10ff36e8;

extern void* DAT_10ff36fc[];

extern void* DAT_10ff3708[];

extern Class_10AF8250 DAT_10ff3724;

void FUN_10a36b00(int A, void** B, void** C, int D, int E, Class_10AF8250 F, int G);

// FUNCTION: 0x10B1D1E0 ?FUN_10b1d1e0@@YAXH@Z
void FUN_10b1d1e0(int Mode)
{
    if (Mode == 1)
        FUN_10a36b00(DAT_10ff36e8, DAT_10ff3708, DAT_10ff36fc, 0, 0, DAT_10ff3724, 0);
}

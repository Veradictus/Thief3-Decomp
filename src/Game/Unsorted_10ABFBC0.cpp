// Game/Unsorted_10ABFBC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10AC10E0
{
public:
    int FUN_10ac10e0();

    char Unknown00[0xC];
    int Unknown0C;
    char Unknown10[0x20];
    float Unknown30;
};

// FUNCTION: 0x10AC10E0 ?FUN_10ac10e0@Class_10AC10E0@@QAEHXZ
int Class_10AC10E0::FUN_10ac10e0()
{
    if (Unknown30 > DAT_10eafbdc && Unknown0C == 4)
        return 1;
    return 0;
}

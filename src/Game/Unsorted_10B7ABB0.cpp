// Game/Unsorted_10B7ABB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_109B6630
{
public:
    float FUN_109b6630(int A);
};

class Class_10B7AC10
{
public:
    float FUN_10b7ac10();

    char Unknown00[4];
    Class_109B6630* Unknown04;
    char Unknown08[0xC];
    int Unknown14;
};

// FUNCTION: 0x10B7AC10 ?FUN_10b7ac10@Class_10B7AC10@@QAEMXZ
float Class_10B7AC10::FUN_10b7ac10()
{
    if (Unknown04 == 0)
        return DAT_10eafbdc;
    return Unknown04->FUN_109b6630(Unknown14);
}

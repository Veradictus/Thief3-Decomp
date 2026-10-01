// Game/Unsorted_10B3AE90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EArmUse
{
    EAU_FREE,
    EAU_FORCED_BODY,
    EAU_FORCED_ARMS
};

class AGarrett
{
public:
    char Unknown00[0x54D];
    unsigned char ArmUse;
};

class Class_10B25200
{
public:
    void FUN_10b24d90();
};

class Class_10B255F0 : public Class_10B25200
{
};

Class_10B255F0* FUN_10b25cd0();

class Class_10B3ADC0
{
public:
    void FUN_10b3ae90(AGarrett* Garrett);
};

// FUNCTION: 0x10B3AE90 ?FUN_10b3ae90@Class_10B3ADC0@@QAEXPAVAGarrett@@@Z
void Class_10B3ADC0::FUN_10b3ae90(AGarrett* Garrett)
{
    Garrett->ArmUse = EAU_FREE;
    FUN_10b25cd0()->FUN_10b24d90();
}

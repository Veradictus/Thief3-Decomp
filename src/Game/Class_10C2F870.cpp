// Game/Class_10C2F870.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10C2F870
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C2F870
{
public:
    void FUN_10c2f870(const Info_10C2F870* In);

    char Unknown00[0x74];
    Info_10C2F870 Unknown74;
    char Unknown80[0x1F];
    char Unknown9F;
};

// FUNCTION: 0x10C2F870 ?FUN_10c2f870@Class_10C2F870@@QAEXPBUInfo_10C2F870@@@Z
void Class_10C2F870::FUN_10c2f870(const Info_10C2F870* In)
{
    Unknown9F = 1;
    Unknown74 = *In;
}

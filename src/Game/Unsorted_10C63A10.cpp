// Game/Unsorted_10C63A10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10C63A10
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C63A10
{
public:
    void FUN_10c63a10(const Info_10C63A10* In);

    char Unknown00[0x20];
    Info_10C63A10 Unknown20;
};

// FUNCTION: 0x10C63A10 ?FUN_10c63a10@Class_10C63A10@@QAEXPBUInfo_10C63A10@@@Z
void Class_10C63A10::FUN_10c63a10(const Info_10C63A10* In)
{
    Unknown20 = *In;
}

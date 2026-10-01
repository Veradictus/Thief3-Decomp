// Game/Unsorted_10BB8160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10BB8160
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BB8160
{
public:
    void FUN_10bb8160(const Info_10BB8160* In);

    char Unknown00[0x2B0];
    Info_10BB8160 Unknown2B0;
};

// FUNCTION: 0x10BB8160 ?FUN_10bb8160@Class_10BB8160@@QAEXPBUInfo_10BB8160@@@Z
void Class_10BB8160::FUN_10bb8160(const Info_10BB8160* In)
{
    Unknown2B0 = *In;
}

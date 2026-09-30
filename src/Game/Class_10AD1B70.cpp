// Game/Class_10AD1B70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10AD1B70
{
    char Unknown00[0x34];
    int Unknown34;
    int Unknown38;
};

class Class_10AD1B70
{
public:
    void FUN_10ad1b70(const Info_10AD1B70* In);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

// FUNCTION: 0x10AD1B70 ?FUN_10ad1b70@Class_10AD1B70@@QAEXPBUInfo_10AD1B70@@@Z
void Class_10AD1B70::FUN_10ad1b70(const Info_10AD1B70* In)
{
    Unknown04++;
    Unknown08 += In->Unknown34;
    Unknown0C += In->Unknown38;
}

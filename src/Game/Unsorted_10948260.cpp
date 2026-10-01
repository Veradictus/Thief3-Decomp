// Game/Unsorted_10948260.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4a9c8[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_1091E2E0
{
public:
    void FUN_1091e2e0();

    void** Unknown00;
    char Unknown04[0x40];
};

class Class_10E4A9C8 : public Class_1091E2E0
{
public:
    Class_10E4A9C8* FUN_10948600();

    int Unknown44;
    bool Unknown48;
    int Unknown4C;
    char Unknown50[0xC];
    int Unknown5C;
    char Unknown60[4];
    FArray Unknown64;
    FArray Unknown70;
    FArray Unknown7C;
    float Unknown88;
    float Unknown8C;
    float Unknown90;
    int Unknown94;
    char Unknown98[0x18];
    int UnknownB0;
    char UnknownB4[0x28];
    int UnknownDC;
    bool UnknownE0;
};

// FUNCTION: 0x10948600 ?FUN_10948600@Class_10E4A9C8@@QAEPAV1@XZ
Class_10E4A9C8* Class_10E4A9C8::FUN_10948600()
{
    FUN_1091e2e0();
    Unknown00 = DAT_10e4a9c8;
    Unknown64.FArray::FArray();
    Unknown70.FArray::FArray();
    Unknown7C.FArray::FArray();
    Unknown88 = 1.0f;
    Unknown8C = 1.0f;
    Unknown90 = 1.0f;
    Unknown94 = 0;
    UnknownE0 = false;
    Unknown4C = 0;
    UnknownB0 = 0;
    UnknownDC = 0;
    Unknown44 = 4;
    Unknown48 = true;
    Unknown5C = -1;
    return this;
}

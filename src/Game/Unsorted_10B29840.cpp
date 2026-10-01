// Game/Unsorted_10B29840.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7b120[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E6B078
{
public:
    Class_10E6B078();

    void** Unknown00;
    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0xCC];
};

class Class_10E7B120 : public Class_10E6B078
{
public:
    Class_10E7B120* FUN_10b2ab70();

    FArray Unknown1B8;
    bool Unknown1C4;
    bool Unknown1C5;
    int Unknown1C8;
    FArray Unknown1CC;
    int Unknown1D8;
    int Unknown1DC;
    bool Unknown1E0;
    float Unknown1E4;
    float Unknown1E8;
    float Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
};

// FUNCTION: 0x10B2AB70 ?FUN_10b2ab70@Class_10E7B120@@QAEPAV1@XZ
Class_10E7B120* Class_10E7B120::FUN_10b2ab70()
{
    this->Class_10E6B078::Class_10E6B078();
    Unknown00 = DAT_10e7b120;
    Unknown1B8.FArray::FArray();
    Unknown1C4 = true;
    Unknown1C5 = false;
    Unknown1C8 = 0;
    Unknown1CC.FArray::FArray();
    Unknown1D8 = 0;
    Unknown1DC = 0;
    Unknown1E0 = true;
    Unknown1E4 = 18.0f;
    Unknown1E8 = 3.0f;
    Unknown1EC = 1.0f;
    Unknown1F0 = 3;
    Unknown1F4 = 0;
    return this;
}

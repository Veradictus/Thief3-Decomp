// Game/Unsorted_10B61D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e84088[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10E84088 : public Class_10B78780
{
public:
    Class_10E84088* FUN_10b61e10();

    FArray Unknown190;
    FArray Unknown19C;
    FArray Unknown1A8;
    FArray Unknown1B4;
    FArray Unknown1C0;
    FArray Unknown1CC;
    bool Unknown1D8;
    int Unknown1DC;
};

// FUNCTION: 0x10B61E10 ?FUN_10b61e10@Class_10E84088@@QAEPAV1@XZ
Class_10E84088* Class_10E84088::FUN_10b61e10()
{
    FUN_10b78780();
    Unknown00 = DAT_10e84088;
    Unknown190.FArray::FArray();
    Unknown19C.FArray::FArray();
    Unknown1A8.FArray::FArray();
    Unknown1B4.FArray::FArray();
    Unknown1C0.FArray::FArray();
    Unknown1CC.FArray::FArray();
    Unknown1D8 = false;
    Unknown1DC = 0;
    return this;
}

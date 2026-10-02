// Game/Unsorted_109523D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109523D0
{
public:
    bool FUN_109523d0(int Mask);

    char Unknown00[0x30];
    int Unknown30;
};

struct Info_10952690
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    float Unknown0C;
};

class Class_10936AC0
{
public:
    void FUN_10937280(int A, Info_10952690* Info);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10952640
{
public:
    void FUN_10952640();

    char Unknown00[0x4C];
    bool Unknown4C;
    char Unknown4D[0x23];
    int Unknown70;
    int Unknown74;
    int Unknown78;
    float Unknown7C;
};

// FUNCTION: 0x109523D0 ?FUN_109523d0@Class_109523D0@@QAE_NH@Z
bool Class_109523D0::FUN_109523d0(int Mask)
{
    for (int i = 0; i < 9; i++)
    {
        int Bit = 1 << i;
        if ((Mask & Bit) && !(Unknown30 & Bit))
            return false;
    }
    return true;
}

// FUNCTION: 0x10952640 ?FUN_10952640@Class_10952640@@QAEXXZ
void Class_10952640::FUN_10952640()
{
    float W = 0.0f;
    if (Unknown4C)
        W = Unknown7C;
    Info_10952690 Info;
    Info.Unknown0C = W;
    Info.Unknown00 = Unknown70;
    Info.Unknown04 = Unknown74;
    Info.Unknown08 = Unknown78;
    DAT_10f31be0->FUN_10937280(0, &Info);
}

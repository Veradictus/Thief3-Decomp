// Game/Unsorted_109E29F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E2A50;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_109E2A50* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_109E2A50
{
public:
    void FUN_109e2a50();
};

class Config
{
public:
    static Config* Instance();

    bool GetFloat(const char* Section, const char* Key, float* Value, const char* File);
};

extern const char DAT_10e4ac38[];

extern const char DAT_10e5b298[];

extern const char DAT_10e5b28c[];

// FUNCTION: 0x109E29F0 ?FUN_109e29f0@@YAXMPAH@Z
void FUN_109e29f0(float Fraction, int* Result)
{
    float MaxVolume;
    float MinVolume;
    Config::Instance()->GetFloat(DAT_10e4ac38, DAT_10e5b298, &MinVolume, 0);
    Config::Instance()->GetFloat(DAT_10e4ac38, DAT_10e5b28c, &MaxVolume, 0);
    *Result = (int)(((MaxVolume - MinVolume) * Fraction + MinVolume) * 32768.0f);
}

// FUNCTION: 0x109E2A50 ?FUN_109e2a50@Class_109E2A50@@QAEXXZ
void Class_109E2A50::FUN_109e2a50()
{
    if (DAT_10f46da0)
    {
        DAT_10f46da0->Virtual1(this, 0x24, -1, -1);
        DAT_10f46da0->Virtual1(this, 0x25, -1, -1);
    }
}

// Game/Unsorted_10952410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10955AA0
{
public:
    void FUN_10955aa0(int Mode);

    int Unknown00;
    int Unknown04;
    int Mode;
    char Unknown0C[4];
    int Unknown10;
    int Unknown14;
    char Unknown18[0x20];
};

class Class_10E4ADC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void FUN_109524a0();

    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0xC];
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
    float Unknown38;
    float Unknown3C;
    float Unknown40;
    int Unknown44;
    int Unknown48;
    bool Unknown4C;
    bool Unknown4D;
    bool Unknown4E;
    bool Unknown4F;
    bool Unknown50;
    int Unknown54;
    int Unknown58;
    float Unknown5C;
    int Unknown60;
    int Unknown64;
    int Unknown68;
    float Unknown6C;
    float Unknown70;
    float Unknown74;
    float Unknown78;
    float Unknown7C;
    float Unknown80;
    float Unknown84;
    float Unknown88;
    float Unknown8C;
    Class_10955AA0 Unknown90[9];
    int Unknown288;
    bool Unknown28C;
    int Unknown290;
};

// FUNCTION: 0x109524A0 ?FUN_109524a0@Class_10E4ADC0@@UAEXXZ
void Class_10E4ADC0::FUN_109524a0()
{
    for (int i = 0; i < 9; i++)
        Unknown90[i].FUN_10955aa0(i);
    for (int j = 0; j < 9; j++)
        Unknown90[j].Unknown04 = -1;
    Unknown0C = -1;
    Unknown34 = -1;
    Unknown2C = 0;
    Unknown30 = 0;
    Unknown28 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown4C = false;
    Unknown44 = 0;
    Unknown48 = 0;
    Unknown4E = false;
    Unknown54 = 0;
    Unknown4F = false;
    Unknown58 = 0;
    Unknown50 = false;
    Unknown288 = 0;
    Unknown28C = false;
    Unknown290 = 0;
    Unknown60 = 0;
    Unknown64 = 0;
    Unknown68 = 0;
    Unknown38 = 1.0f;
    Unknown3C = 0.5f;
    Unknown40 = 0.5f;
    Unknown4D = true;
    Unknown5C = 1.0f;
    Unknown6C = 1.0f;
    Unknown70 = 1.0f;
    Unknown74 = 1.0f;
    Unknown78 = 1.0f;
    Unknown7C = 1.0f;
    Unknown80 = 1.0f;
    Unknown84 = 1.0f;
    Unknown88 = 1.0f;
    Unknown8C = 1.0f;
}

// Game/Unsorted_10AAB8D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Config
{
public:
    static Config* Instance();

    bool GetFloat(const char* Section, const char* Key, float* Value, const char* File);
};

extern void* DAT_10e6da90[];

extern const char DAT_10e6dae0[];

extern const char DAT_10e6daf4[];

extern const char DAT_10e6da84[];

class Class_10E6DA90
{
public:
    Class_10E6DA90* FUN_10aabdf0();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    char Unknown10[4];
    bool Unknown14;
    float Unknown18;
    float Unknown1C;
    char Unknown20[0x30];
    int Unknown50;
};

// FUNCTION: 0x10AABDF0 ?FUN_10aabdf0@Class_10E6DA90@@QAEPAV1@XZ
Class_10E6DA90* Class_10E6DA90::FUN_10aabdf0()
{
    Unknown00 = DAT_10e6da90;
    Unknown04 = 0;
    Unknown08 = 1;
    Unknown0C = 0x11;
    Unknown14 = true;
    Unknown50 = 0;
    Config::Instance()->GetFloat(DAT_10e6dae0, DAT_10e6daf4, &Unknown18, 0);
    Config::Instance()->GetFloat(DAT_10e6dae0, DAT_10e6da84, &Unknown1C, 0);
    return this;
}

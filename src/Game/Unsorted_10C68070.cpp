// Game/Unsorted_10C68070.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C685F0
{
public:
    void FUN_10c685f0();
    void FUN_10c682d0();

    char Unknown00[0x74];
    bool Unknown74;
    bool Unknown75;
};

class Config
{
public:
    static Config* Instance();

    bool GetFloat(const char* Section, const char* Key, float* Value, const char* File);
};

class Class_10E9D0BC
{
public:
    Class_10E9D0BC();

    virtual ~Class_10E9D0BC();

    float DefaultInnerRadius;
    float DefaultOuterRadius;
};

// FUNCTION: 0x10C685F0 ?FUN_10c685f0@Class_10C685F0@@QAEXXZ
void Class_10C685F0::FUN_10c685f0()
{
    FUN_10c682d0();
    Unknown74 = true;
    Unknown75 = true;
}

// FUNCTION: 0x10C686C0 ??0Class_10E9D0BC@@QAE@XZ
Class_10E9D0BC::Class_10E9D0BC()
    : DefaultInnerRadius(400.0f), DefaultOuterRadius(1600.0f)
{
    Config::Instance()->GetFloat("Cadence", "DefaultInnerRadius", &DefaultInnerRadius, 0);
    Config::Instance()->GetFloat("Cadence", "DefaultOuterRadius", &DefaultOuterRadius, 0);
}

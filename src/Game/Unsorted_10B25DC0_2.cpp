// Game/Unsorted_10B25DC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    virtual void Virtual0(int A, int B, int C);

    char Unknown04[0x94];
    int Unknown98;
};

extern WindowManager* GWindowManager;

class Config
{
public:
    static Config* Instance();

    bool GetFloat(const char* Section, const char* Key, float* Value, const char* File);
};

extern void* DAT_10e7aaac[];

extern float DAT_10f03038;

extern float DAT_10f0303c;

class Class_10E7AAAC
{
public:
    Class_10E7AAAC();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10B265B0 ?FUN_10b265b0@@YGXPAH0H@Z
void __stdcall FUN_10b265b0(int* A, int* B, int C)
{
    if (*B)
        GWindowManager->Virtual0(C, 3, GWindowManager->Unknown98);
    *B = 0;
    *A = 0;
}

// FUNCTION: 0x10B26690 ??0Class_10E7AAAC@@QAE@XZ
Class_10E7AAAC::Class_10E7AAAC()
{
    Unknown00 = DAT_10e7aaac;
    Config::Instance()->GetFloat("T3Settings", "MenuInputInitialDelay", &DAT_10f03038, 0);
    Config::Instance()->GetFloat("T3Settings", "MenuInputRepeatDelay", &DAT_10f0303c, 0);
}

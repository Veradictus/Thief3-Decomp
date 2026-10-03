// Game/Unsorted_10946B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10946D70 {
public:
    void FUN_10946d70(void* P);
};

class Config
{
public:
    static Config* Instance();

    bool GetBool(const char* Section, const char* Key, bool* Value, const char* File);
};

extern bool DAT_10f34104;

extern bool DAT_10f340f0;

// FUNCTION: 0x10946B30 ?FUN_10946b30@@YA_NXZ
bool FUN_10946b30()
{
    if (!DAT_10f34104)
    {
        DAT_10f340f0 = Config::Instance()->GetBool("Flesh", "UseNewConversion", &DAT_10f340f0, 0) && DAT_10f340f0;
        DAT_10f34104 = true;
    }
    return DAT_10f340f0;
}

// FUNCTION: 0x10946D70 ?FUN_10946d70@Class_10946D70@@QAEXPAX@Z
void Class_10946D70::FUN_10946d70(void* P)
{
    if (P)
        ::operator delete(P);
}

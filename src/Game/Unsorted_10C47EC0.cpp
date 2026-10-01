// Game/Unsorted_10C47EC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C47FA0_Field04
{
public:
    virtual void Virtual0(int B);
};

class Class_10E9BB5C
{
public:
    virtual bool FUN_10c47fa0(int A, int B);

    Class_10C47FA0_Field04* Unknown04;
};

extern void* DAT_10e9bb4c[];

class Config
{
public:
    static Config* Instance();
    void FUN_10910a20(const char* Section, const char* Key, int* Value, int D);
};

class Class_10E9BB4C
{
public:
    Class_10E9BB4C* FUN_10c47f30(bool A);

    void** Unknown00;
    bool Unknown04;
    int MaxLoadedSchemas;
    int Unknown0C;
};

class Class_10C47F80
{
public:
    virtual ~Class_10C47F80();
};

extern Class_10C47F80* DAT_10ff70b8;

// FUNCTION: 0x10C47F30 ?FUN_10c47f30@Class_10E9BB4C@@QAEPAV1@_N@Z
Class_10E9BB4C* Class_10E9BB4C::FUN_10c47f30(bool A)
{
    Unknown00 = DAT_10e9bb4c;
    Unknown04 = A;
    Unknown0C = 0;
    if (A)
    {
        MaxLoadedSchemas = 500;
        Config::Instance()->FUN_10910a20("Cadence", "MaxLoadedSchemas", &MaxLoadedSchemas, 0);
    }
    else
    {
        MaxLoadedSchemas = -1;
    }
    return this;
}

// FUNCTION: 0x10C47F80 ?FUN_10c47f80@@YAXXZ
void FUN_10c47f80()
{
    delete DAT_10ff70b8;
    DAT_10ff70b8 = 0;
}

// FUNCTION: 0x10C47FA0 ?FUN_10c47fa0@Class_10E9BB5C@@UAE_NHH@Z
bool Class_10E9BB5C::FUN_10c47fa0(int A, int B)
{
    Unknown04->Virtual0(B);
    return true;
}

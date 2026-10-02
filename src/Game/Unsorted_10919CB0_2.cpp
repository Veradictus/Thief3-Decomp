// Game/Unsorted_10919CB0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
class Class_109081E0
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

class Class_1091A590
{
public:
    ~Class_1091A590();

    Class_109081E0 Unknown00;
    Class_109081E0 Unknown04;
};

extern const char DAT_10e47660[];

struct Struct_1091A610Header
{
    int Unknown00;
};

struct Struct_1091A610
{
    char* Unknown00;
};

class Class_10919B90
{
public:
    float FUN_10919b90(const char* A, int B, int C);
    float FUN_1091a610(const Struct_1091A610* A, int B);
};

class Class_1091A4F0
{
public:
    void FUN_1091a4f0(int A);
    void FUN_1091a920();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_1091B3F0
{
public:
    void FUN_1091af10(int A);
    void FUN_1091b3f0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x1091A590 ??1Class_1091A590@@QAE@XZ
Class_1091A590::~Class_1091A590()
{
}

// FUNCTION: 0x1091A610 ?FUN_1091a610@Class_10919B90@@QAEMPBUStruct_1091A610@@H@Z
float Class_10919B90::FUN_1091a610(const Struct_1091A610* A, int B)
{
    int Length = !A->Unknown00 ? 0 : ((Struct_1091A610Header*)A->Unknown00 - 1)->Unknown00;
    const char* Text = A->Unknown00 ? A->Unknown00 : DAT_10e47660;
    return FUN_10919b90(Text, Length, B);
}

// FUNCTION: 0x1091A920 ?FUN_1091a920@Class_1091A4F0@@QAEXXZ
void Class_1091A4F0::FUN_1091a920()
{
    FUN_1091a4f0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x1091B3F0 ?FUN_1091b3f0@Class_1091B3F0@@QAEXXZ
void Class_1091B3F0::FUN_1091b3f0()
{
    FUN_1091af10(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

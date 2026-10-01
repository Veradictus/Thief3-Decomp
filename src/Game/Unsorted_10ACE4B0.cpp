// Game/Unsorted_10ACE4B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938
{
public:
    Class_10E67938();

    virtual void Virtual0(int Code, int A, int B, int C);
};

class Class_10E70204 : public Class_10E67938
{
public:
    Class_10E70204();

    virtual void Virtual0(int Code, int A, int B, int C);
};

class Class_10ACEE50
{
public:
    void FUN_10ace920();
    void FUN_10aceaa0();
    void FUN_10acee50();
};

class Class_10E701C8
{
public:
    virtual void FUN_10ace5b0(int Code, int A, int B, int C);
    void FUN_10ace4d0(int A, int B, int C);
};

// FUNCTION: 0x10ACE5B0 ?FUN_10ace5b0@Class_10E701C8@@UAEXHHHH@Z
void Class_10E701C8::FUN_10ace5b0(int Code, int A, int B, int C)
{
    if (Code == 0x10)
        FUN_10ace4d0(A, B, C);
}

// FUNCTION: 0x10ACE5D0 ??0Class_10E70204@@QAE@XZ
Class_10E70204::Class_10E70204()
{
}

// FUNCTION: 0x10ACEE50 ?FUN_10acee50@Class_10ACEE50@@QAEXXZ
void Class_10ACEE50::FUN_10acee50()
{
    FUN_10ace920();
    FUN_10aceaa0();
}

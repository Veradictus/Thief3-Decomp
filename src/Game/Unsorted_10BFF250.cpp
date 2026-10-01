// Game/Unsorted_10BFF250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10C16580
{
public:
    virtual void Virtual0(FArchive& Ar);

    int Unknown04;
};

class Class_10E97AD4
{
public:
    virtual void Virtual0(FArchive& Ar);

    int Unknown04;
    Class_10C16580 Unknown08;
    bool Unknown10;
};

class Class_10BFF600
{
public:
    int FUN_10bff600(int A, const float* B);
    bool FUN_10bff6d0(int A, const float* B);
};

// FUNCTION: 0x10BFF300 ?Virtual0@Class_10E97AD4@@UAEXAAVFArchive@@@Z
void Class_10E97AD4::Virtual0(FArchive& Ar)
{
    Unknown08.Virtual0(Ar);
    Ar.Serialize(&Unknown10, 1);
}

// FUNCTION: 0x10BFF6D0 ?FUN_10bff6d0@Class_10BFF600@@QAE_NHPBM@Z
bool Class_10BFF600::FUN_10bff6d0(int A, const float* B)
{
    return FUN_10bff600(A, B) != 0;
}

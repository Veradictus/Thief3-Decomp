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

class Class_10978090
{
public:
    int FUN_10978090();
};

class Class_10BFF280
{
public:
    int FUN_10bff280();

    char Unknown00[8];
    Class_10978090 Unknown08;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10BAA9D0 : public Class_10c7d570
{
};

class Class_10DBBAE0
{
public:
    Class_10BAA9D0* FUN_10dbbae0();
};

struct Struct_10BFF250_A
{
    char Unknown00[0x2C];
    int Unknown2C;
};

struct Struct_10BFF250_B
{
    char Unknown00[0x2C];
    int Unknown2C;
};

void FUN_10ba91e0(int* A, int* B);

class Class_10BFF460
{
public:
    void FUN_10bff250();

    char Unknown00[4];
    Class_10DBBAE0* Unknown04;
    Class_10978090 Unknown08;
};

// FUNCTION: 0x10BFF250 ?FUN_10bff250@Class_10BFF460@@QAEXXZ
void Class_10BFF460::FUN_10bff250()
{
    Class_10BAA9D0* P = Unknown04->FUN_10dbbae0();
    FUN_10ba91e0(&((Struct_10BFF250_A*)P->FUN_10c7d570())->Unknown2C,
                 &((Struct_10BFF250_B*)Unknown08.FUN_10978090())->Unknown2C);
}

// FUNCTION: 0x10BFF280 ?FUN_10bff280@Class_10BFF280@@QAEHXZ
int Class_10BFF280::FUN_10bff280()
{
    int Result = Unknown08.FUN_10978090();
    if (!Result)
        return Result;
    return Unknown08.FUN_10978090();
}

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

// Game/Unsorted_10BFF330_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAA9D0
{
public:
    bool FUN_10baa9d0(void* A, float B, bool C);
};

class Class_10DBBAE0
{
public:
    Class_10BAA9D0* FUN_10dbbae0();
};

class Class_10BFF460
{
public:
    void* FUN_10bff2a0();
    bool FUN_10bff330();

    char Unknown00[4];
    Class_10DBBAE0* Unknown04;
};

// FUNCTION: 0x10BFF330 ?FUN_10bff330@Class_10BFF460@@QAE_NXZ
bool Class_10BFF460::FUN_10bff330()
{
    void* P = FUN_10bff2a0();
    if (!P)
        return false;
    return Unknown04->FUN_10dbbae0()->FUN_10baa9d0(P, 0.0f, false);
}

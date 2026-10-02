// Game/Unsorted_10BFF330_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

bool FUN_10c00680(void* P);

class Class_10BFF460
{
public:
    bool FUN_10bff460();
    void* FUN_10bff2a0();
};

// FUNCTION: 0x10BFF460 ?FUN_10bff460@Class_10BFF460@@QAE_NXZ
bool Class_10BFF460::FUN_10bff460()
{
    void* P = FUN_10bff2a0();
    if (P)
        return FUN_10c00680(P);
    return false;
}

// Game/Unsorted_10A3C340.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_1090ecc0(void* A, void* B, int C);

class Class_10E66800
{
public:
    virtual void Virtual0();
    virtual int FUN_10a3c600(void* A, void* B);
};

// FUNCTION: 0x10A3C600 ?FUN_10a3c600@Class_10E66800@@UAEHPAX0@Z
int Class_10E66800::FUN_10a3c600(void* A, void* B)
{
    if (FUN_1090ecc0(A, B, 1) == 0)
        return 0;
    return FUN_1090ecc0(A, B, 1) > 0 ? 1 : -1;
}

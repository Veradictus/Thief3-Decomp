// Game/Unsorted_1090F2C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

bool FUN_1090f010(const int* A, const int* B);

int FUN_1090ecc0(void* A, void* B, int C);

class Class_10E499A8
{
public:
    virtual void Virtual0();
    virtual int FUN_1090f3c0(int* A, int* B);
};

// FUNCTION: 0x1090F3C0 ?FUN_1090f3c0@Class_10E499A8@@UAEHPAH0@Z
int Class_10E499A8::FUN_1090f3c0(int* A, int* B)
{
    if (FUN_1090f010(A, B))
        return 0;
    return FUN_1090ecc0(A, B, 1) > 0 ? 1 : -1;
}

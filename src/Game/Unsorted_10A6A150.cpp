// Game/Unsorted_10A6A150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B660
{
public:
    virtual void FUN_10a6ad50(int Type, int A, int B, int C);

    void FUN_10a6ac80(int A, int B, int C);
};

// FUNCTION: 0x10A6AD50 ?FUN_10a6ad50@Class_10E6B660@@UAEXHHHH@Z
void Class_10E6B660::FUN_10a6ad50(int Type, int A, int B, int C)
{
    if (Type >= 0x2a && Type <= 0x2b)
        FUN_10a6ac80(A, B, C);
}

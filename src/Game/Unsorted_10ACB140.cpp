// Game/Unsorted_10ACB140.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A4C5F0
{
public:
    virtual void Virtual0(int Msg, int A, int B, int C);

    void FUN_10acb200(int A, int B, int C);
    void FUN_10acb280(int A, int B, int C);
};

// FUNCTION: 0x10ACB2E0 ?Virtual0@Class_10A4C5F0@@UAEXHHHH@Z
void Class_10A4C5F0::Virtual0(int Msg, int A, int B, int C)
{
    switch (Msg)
    {
    case 1:
        FUN_10acb200(A, B, C);
        break;
    case 0x10:
        FUN_10acb280(A, B, C);
        break;
    }
}

// Game/Unsorted_10B30050.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67FB0
{
public:
    virtual void FUN_10b30150(const float* A, const float* B, int C);

    float Unknown04;
    float Unknown08;
    float Unknown0C;
    float Unknown10;
    bool Unknown14;
    int Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10B30150 ?FUN_10b30150@Class_10E67FB0@@UAEXPBM0H@Z
void Class_10E67FB0::FUN_10b30150(const float* A, const float* B, int C)
{
    Unknown08 = *A;
    Unknown0C = *B;
    Unknown10 = *B - *A;
    Unknown18 = C;
    Unknown1C = 0;
    Unknown04 = Unknown08;
    Unknown14 = false;
}

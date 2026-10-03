// Game/Unsorted_10B47C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int A);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B47C50
{
public:
    void FUN_10b47b20(int A, float B, float C, int D, int E, bool F, bool G, float H);

    char Unknown00[0x4C];
    Class_10BFBD70 Unknown4C;
};

class Class_10B481C0 : public Class_10B47C50
{
public:
    void FUN_10b481c0(int A, float B, float C, int D, int E, bool F, bool G, float H);
};

extern float DAT_10e49684;

// FUNCTION: 0x10B481C0 ?FUN_10b481c0@Class_10B481C0@@QAEXHMMHH_N0M@Z
void Class_10B481C0::FUN_10b481c0(int A, float B, float C, int D, int E, bool F, bool G, float H)
{
    Unknown4C.FUN_10bfbd70(0);
    if (B > DAT_10e49684)
        B = 1.0f;
    FUN_10b47b20(A, B, C, D, E, F, G, H);
}

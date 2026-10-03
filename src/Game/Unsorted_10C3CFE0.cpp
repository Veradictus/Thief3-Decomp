// Game/Unsorted_10C3CFE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" double sin(double);

double FUN_10c00480();

extern float DAT_10e49684;

extern float DAT_10e9afc8;

class Class_10E9AF80
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c3cf10(Class_10E9AF80* Other);
    virtual void Virtual4();
    virtual void FUN_10c3cfe0(float* A, float* B, float* C);

    char Unknown04[8];
    float Unknown0C;
    float Unknown10;
    float Unknown14;
    float Unknown18;
};

// FUNCTION: 0x10C3CFE0 ?FUN_10c3cfe0@Class_10E9AF80@@UAEXPAM00@Z
void Class_10E9AF80::FUN_10c3cfe0(float* A, float* B, float* C)
{
    float T = (FUN_10c00480() - Unknown14) / Unknown18;
    float X = DAT_10e49684 - T;
    float S = sin((DAT_10e49684 - X * X * X) * DAT_10e9afc8);
    *B = S * Unknown0C;
    *A = S * Unknown10;
    *C = 0.0f;
}

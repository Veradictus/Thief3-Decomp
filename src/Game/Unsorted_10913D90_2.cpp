// Game/Unsorted_10913D90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
class Class_109081E0
{
public:
    char* Unknown00;
};

class Class_10914D60
{
public:
    unsigned char FUN_10914d60();
    void FUN_109152e0(int A, Class_109081E0& B, int C);
    void FUN_10915160(int A, Class_109081E0& B, int C);
};

class Class_109140C0
{
public:
    void FUN_109140c0(int A, Class_109081E0& B, int C);
    void FUN_10914100(int A, Class_109081E0& B, int C);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Class_10914D60** Unknown0C;
};

// FUNCTION: 0x109140C0 ?FUN_109140c0@Class_109140C0@@QAEXHAAVClass_109081E0@@H@Z
void Class_109140C0::FUN_109140c0(int A, Class_109081E0& B, int C)
{
    for (int i = Unknown04 - 1; i >= 0; i--)
    {
        Unknown0C[i]->FUN_10915160(A, B, C);
        if (B.Unknown00 && ((int*)B.Unknown00)[-1])
            break;
    }
}

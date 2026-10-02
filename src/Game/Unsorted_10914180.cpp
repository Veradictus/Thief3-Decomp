// Game/Unsorted_10914180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_10915210
{
public:
    void FUN_109152c0(const Class_1090A780& A);
};

class Class_109141C0
{
public:
    void FUN_109141c0(const Class_1090A780& A);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_10915210** Unknown0C;
};

// FUNCTION: 0x109141C0 ?FUN_109141c0@Class_109141C0@@QAEXABVClass_1090A780@@@Z
void Class_109141C0::FUN_109141c0(const Class_1090A780& A)
{
    for (int i = 0; i < Unknown04; i++)
        Unknown0C[i]->FUN_109152c0(A);
}

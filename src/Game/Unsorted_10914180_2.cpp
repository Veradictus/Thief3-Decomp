// Game/Unsorted_10914180_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_10915210
{
public:
    void FUN_109152a0(const Class_1090A780& A, int B);
};

class Class_10914180
{
public:
    void FUN_10914180(const Class_1090A780& A, int B);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_10915210** Unknown0C;
};

// FUNCTION: 0x10914180 ?FUN_10914180@Class_10914180@@QAEXABVClass_1090A780@@H@Z
void Class_10914180::FUN_10914180(const Class_1090A780& A, int B)
{
    for (int i = 0; i < Unknown04; i++)
        Unknown0C[i]->FUN_109152a0(A, B);
}

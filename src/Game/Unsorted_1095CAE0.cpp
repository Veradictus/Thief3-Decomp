// Game/Unsorted_1095CAE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_1095CAE0
{
public:
    Class_1095CAE0* FUN_1095cae0(int A);

    int* Unknown00;
    int Unknown04;
};

// FUNCTION: 0x1095CAE0 ?FUN_1095cae0@Class_1095CAE0@@QAEPAV1@H@Z
Class_1095CAE0* Class_1095CAE0::FUN_1095cae0(int A)
{
    Unknown04 = A;
    Unknown00 = (int*)operator new(A * sizeof(int), 0, 0, 0, 0, 0);
    for (int i = 0; i < Unknown04; i++)
        Unknown00[i] = -1;
    return this;
}

// Game/Unsorted_109276A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109275D0
{
public:
    void FUN_109275d0(int* A, int* B);

    int Unknown00;
    int* Unknown04;
};

class Class_109283D0
{
public:
    void FUN_109283d0(int A);

    char Unknown00[0xC8];
    Class_109275D0 UnknownC8;
};

// FUNCTION: 0x109283D0 ?FUN_109283d0@Class_109283D0@@QAEXH@Z
void Class_109283D0::FUN_109283d0(int A)
{
    int* Where = UnknownC8.Unknown04;
    if (A > 0)
        Where += A;
    UnknownC8.FUN_109275d0(&A, Where);
}

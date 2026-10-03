// Game/Unsorted_10AC99F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AC99F0
{
public:
    void FUN_10ac99f0(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

// FUNCTION: 0x10AC99F0 ?FUN_10ac99f0@Class_10AC99F0@@QAEXH@Z
void Class_10AC99F0::FUN_10ac99f0(int A)
{
    for (int i = 0; i < Unknown04; i++)
    {
        if (Unknown0C[i] == A)
            Unknown0C[i] = 0;
    }
}

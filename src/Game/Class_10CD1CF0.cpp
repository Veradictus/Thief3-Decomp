// Game/Class_10CD1CF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10CD1CF0
{
public:
    void FUN_10cd1cf0(Class_10CD1CF0* A, int B);

    int Unknown00[4];
};

// FUNCTION: 0x10CD1CF0 ?FUN_10cd1cf0@Class_10CD1CF0@@QAEXPAV1@H@Z
void Class_10CD1CF0::FUN_10cd1cf0(Class_10CD1CF0* A, int B)
{
    for (int i = 0; i < 4; i++)
        Unknown00[i] = A->Unknown00[i];
    Unknown00[3] = B;
}

// Game/Unsorted_10BB8650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109BC840
{
public:
    void FUN_109bc840(int A, int B, float C, int D, int E);
};

class Class_10BAA580
{
public:
    Class_109BC840* FUN_10baa580();
};

class Class_10BB86B0
{
public:
    void FUN_10bb86b0(float A);

    int Unknown00;
    int Unknown04;
    Class_10BAA580* Unknown08;
};

// FUNCTION: 0x10BB86B0 ?FUN_10bb86b0@Class_10BB86B0@@QAEXM@Z
void Class_10BB86B0::FUN_10bb86b0(float A)
{
    Class_109BC840* Target = Unknown08->FUN_10baa580();
    if (Target)
        Target->FUN_109bc840(0, 0, A, 0, 0);
}

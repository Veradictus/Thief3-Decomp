// Game/Unsorted_10BB6810.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAA3C0;

class Class_10BB67F0
{
public:
    void* FUN_10bb62a0(void* A, int B, void* C, Class_10BAA3C0* D);
    void* FUN_10bb7130(void* A, int B, int C, int D, int E, Class_10BAA3C0* F, int G, int H);
    void* FUN_10bb7490(int A, int B, int C, int D, Class_10BAA3C0* E, int F, int G);

    void* Unknown00;
};

// FUNCTION: 0x10BB7490 ?FUN_10bb7490@Class_10BB67F0@@QAEPAXHHHHPAVClass_10BAA3C0@@HH@Z
void* Class_10BB67F0::FUN_10bb7490(int A, int B, int C, int D, Class_10BAA3C0* E, int F, int G)
{
    void* Result = FUN_10bb62a0(Unknown00, A, (void*)1, E);
    return FUN_10bb7130(Result, A, B, C, D, E, F, G);
}

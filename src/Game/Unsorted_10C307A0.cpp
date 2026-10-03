// Game/Unsorted_10C307A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C30700_Unknown140
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B);
};

class Class_10C30700
{
public:
    void FUN_10c307a0(int A, int B);

    char Unknown00[0x99];
    bool Unknown99;
    char Unknown9A[0x9E];
    int Unknown138;
    char Unknown13C[4];
    Class_10C30700_Unknown140** Unknown140;
};

// FUNCTION: 0x10C307A0 ?FUN_10c307a0@Class_10C30700@@QAEXHH@Z
void Class_10C30700::FUN_10c307a0(int A, int B)
{
    Unknown99 = true;
    for (int i = 0; i < Unknown138; i++)
        Unknown140[i]->Virtual2(A, B);
    Unknown99 = false;
}

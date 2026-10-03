// Game/Unsorted_10A465F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A462B0
{
public:
    ~Class_10A462B0();

    char Unknown00[0x30];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3b50(int A);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10a46770 : public Class_10AF4BB0
{
public:
    void FUN_10a46770(int Slack);
};

// FUNCTION: 0x10A46770 ?FUN_10a46770@Class_10a46770@@QAEXH@Z
void Class_10a46770::FUN_10a46770(int Slack)
{
    for (int i = 0; i < Unknown04; i++)
        ((Class_10A462B0*)Unknown00)[i].~Class_10A462B0();
    Unknown04 = 0;
    Unknown08 = Slack;
    FUN_10af3b50(0x30);
}

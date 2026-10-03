// Game/Unsorted_10C41560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C40750
{
public:
    void FUN_10c40750();

    Class_10C40750* Unknown00;
    Class_10C40750* Unknown04;
};

class Class_10C423F0
{
public:
    void FUN_10c415d0();

    char Unknown00[0x18];
    Class_10C40750* Unknown18;
    int Unknown1C;
};

class Class_10C41420
{
public:
    virtual void FUN_10c423d0(int A, int B, int C, int D);

    void FUN_10c41ab0(int A);
    void FUN_10c41b10();
};

class Class_10E9B83C : public Class_10C41420
{
public:
    virtual void FUN_10c423d0(int A, int B, int C, int D);
};

// FUNCTION: 0x10C423D0 ?FUN_10c423d0@Class_10E9B83C@@UAEXHHHH@Z
void Class_10E9B83C::FUN_10c423d0(int A, int B, int C, int D)
{
    switch (A)
    {
    case 0x74:
        FUN_10c41ab0(0);
        break;
    case 0x75:
        FUN_10c41b10();
        break;
    }
}

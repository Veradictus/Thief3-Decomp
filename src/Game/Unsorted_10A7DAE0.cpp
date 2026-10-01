// Game/Unsorted_10A7DAE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6BEA8
{
public:
    virtual void Virtual0();
    virtual void FUN_10a7db90();

    Class_10BFBD70 Unknown04;
    int Unknown10;
};

// FUNCTION: 0x10A7DB90 ?FUN_10a7db90@Class_10E6BEA8@@UAEXXZ
void Class_10E6BEA8::FUN_10a7db90()
{
    Unknown04.FUN_10bfbd70(0);
    Unknown10 = 0;
}

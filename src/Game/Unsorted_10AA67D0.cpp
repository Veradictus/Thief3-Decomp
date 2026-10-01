// Game/Unsorted_10AA67D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6D8CC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aa67a0(int Value);
    virtual void Virtual3();
    virtual bool FUN_10aa67d0();

    Class_10BFBD70 Unknown04;
};

// FUNCTION: 0x10AA67D0 ?FUN_10aa67d0@Class_10E6D8CC@@UAE_NXZ
bool Class_10E6D8CC::FUN_10aa67d0()
{
    Class_10BFBD70* Array = &Unknown04;
    int Last = Array->Unknown00 - 1;
    int First = Array->Unknown08[0];
    Array->Unknown08[0] = Array->Unknown08[Last];
    Array->Unknown08[Last] = First;
    Array->FUN_10bfbd70(Array->Unknown00 - 1);
    return Array->Unknown00 == 0;
}

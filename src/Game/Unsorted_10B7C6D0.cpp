// Game/Unsorted_10B7C6D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E4B180_Unknown70;

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    Class_10E4B180_Unknown70** Data;
};

class Class_10E4B180
{
public:
    virtual void Virtual0();

    void FUN_10b7e620(int Mask, Class_10E4B180_Unknown70* Obj);

    char Unknown04[0x34];
    Class_10BFBD70 Unknown38[8];
};

// FUNCTION: 0x10B7E620 ?FUN_10b7e620@Class_10E4B180@@QAEXHPAVClass_10E4B180_Unknown70@@@Z
void Class_10E4B180::FUN_10b7e620(int Mask, Class_10E4B180_Unknown70* Obj)
{
    unsigned int Bit = 1;
    for (int i = 0; i < 8; i++, Bit <<= 1)
    {
        if (Mask & Bit)
        {
            int Index = Unknown38[i].Count;
            Unknown38[i].FUN_10bfbd70(Index + 1);
            Unknown38[i].Data[Index] = Obj;
        }
    }
}

// Game/Unsorted_10B14FB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7A9C0;

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    Class_10E7A9C0** Data;
};

class Class_10B152C0
{
public:
    void FUN_10b152c0(int Mask, Class_10E7A9C0* Obj);

    char Unknown00[0x3C];
    Class_10BFBD70 Unknown3C[32];
};

// FUNCTION: 0x10B152C0 ?FUN_10b152c0@Class_10B152C0@@QAEXHPAVClass_10E7A9C0@@@Z
void Class_10B152C0::FUN_10b152c0(int Mask, Class_10E7A9C0* Obj)
{
    unsigned int Bit = 1;
    for (int i = 0; i < 32; i++, Bit <<= 1)
    {
        if (Mask & Bit)
        {
            int Index = Unknown3C[i].Count;
            Unknown3C[i].FUN_10bfbd70(Index + 1);
            Unknown3C[i].Data[Index] = Obj;
        }
    }
}

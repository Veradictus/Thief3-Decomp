// Game/Unsorted_10C08590.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C08690
{
    char Unknown00[0x78];
    unsigned char Unknown78;
};

class Class_10BFBD70
{
public:
    void FUN_109dff50(int Index);
    void FUN_10c08690(Struct_10C08690* Item);

    int FindIndex(Struct_10C08690* Item)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Item)
                return i;
        }
        return -1;
    }

    int Unknown00;
    int Unknown04;
    Struct_10C08690** Unknown08;
};

// FUNCTION: 0x10C08690 ?FUN_10c08690@Class_10BFBD70@@QAEXPAUStruct_10C08690@@@Z
void Class_10BFBD70::FUN_10c08690(Struct_10C08690* Item)
{
    if (Item->Unknown78 & 4)
    {
        int Index = FindIndex(Item);
        if (Index != -1)
            FUN_109dff50(Index);
    }
}

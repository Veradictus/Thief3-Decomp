// Game/Unsorted_10A56670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A56860
{
public:
    void FUN_10a56860(int Item);
    void FUN_10a56480(int Index);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Unknown120; i++)
        {
            if (Unknown128[i] == Item)
                return i;
        }
        return -1;
    }

    char Unknown00[0x120];
    int Unknown120;
    int Unknown124;
    int* Unknown128;
};

// FUNCTION: 0x10A56860 ?FUN_10a56860@Class_10A56860@@QAEXH@Z
void Class_10A56860::FUN_10a56860(int Item)
{
    FUN_10a56480(FindIndex(Item));
}

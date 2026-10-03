// Game/Unsorted_10C06790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9FBE0
{
public:
    void FUN_10b9f620(int Count);

    int Unknown00;
    int Unknown04;
    char* Unknown08;
};

// FUNCTION: 0x10C06790 ?FUN_10c06790@@YAXPAVClass_10B9FBE0@@@Z
void FUN_10c06790(Class_10B9FBE0* Array)
{
    if (Array->Unknown00 == 0)
    {
        for (int Row = 0; Row < 8; Row++)
        {
            for (int Column = 0; Column < 8; Column++)
            {
                int Index = Array->Unknown00;
                Array->FUN_10b9f620(Index + 1);
                Array->Unknown08[Index] = 0;
            }
        }
    }
}

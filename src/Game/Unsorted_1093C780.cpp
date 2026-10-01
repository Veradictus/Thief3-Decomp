// Game/Unsorted_1093C780.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern bool DAT_10ffc855;

struct Node_1093C7F0
{
    Node_1093C7F0* Unknown00;
    Node_1093C7F0* Unknown04;
    Node_1093C7F0* Unknown08;
};

class Class_1093C670
{
public:
    void FUN_1093c670(Node_1093C7F0* Root);

    void Clear()
    {
        FUN_1093c670(Unknown1C->Unknown04);
        Unknown1C->Unknown04 = Unknown1C;
        Unknown20 = 0;
        Unknown1C->Unknown00 = Unknown1C;
        Unknown1C->Unknown08 = Unknown1C;
    }

    char Unknown00[0x1C];
    Node_1093C7F0* Unknown1C;
    int Unknown20;
};

class Class_1093C7F0
{
public:
    void FUN_1093c7f0();

    char Unknown00[0x1C5C];
    Class_1093C670 Unknown1C5C;
};

// FUNCTION: 0x1093C7F0 ?FUN_1093c7f0@Class_1093C7F0@@QAEXXZ
void Class_1093C7F0::FUN_1093c7f0()
{
    if (!DAT_10ffc855)
        Unknown1C5C.Clear();
}

// Game/Unsorted_10C15DC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C15E60_Node
{
    char Unknown00[4];
    void* Unknown04;
    Struct_10C15E60_Node* Unknown08;
};

class Class_10C15E60
{
public:
    void FUN_10c15e60(void* Source);

    char Unknown00[4];
    Struct_10C15E60_Node* Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C15E60 ?FUN_10c15e60@Class_10C15E60@@QAEXPAX@Z
void Class_10C15E60::FUN_10c15e60(void* Source)
{
    Struct_10C15E60_Node* Node = Unknown04;
    if (!Node)
        return;
    if (Node->Unknown04 == Source)
    {
        Unknown04 = Node->Unknown08;
        Unknown08--;
        return;
    }
    Struct_10C15E60_Node* Prev = Node;
    while (Node)
    {
        if (Node->Unknown04 == Source)
        {
            Prev->Unknown08 = Node->Unknown08;
            Unknown08--;
            return;
        }
        Prev = Node;
        Node = Node->Unknown08;
    }
}

// Game/Unsorted_10930A80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Node_10932350
{
    char Unknown00[0xA8];
    Node_10932350* UnknownA8;
    Node_10932350* UnknownAC;
};

class Class_10932350
{
public:
    void FUN_10932350(Node_10932350* Node);

    Node_10932350* Unknown00;
    Node_10932350* Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10932350 ?FUN_10932350@Class_10932350@@QAEXPAUNode_10932350@@@Z
void Class_10932350::FUN_10932350(Node_10932350* Node)
{
    if (!Node->UnknownA8)
        Unknown00 = Node->UnknownAC;
    else
        Node->UnknownA8->UnknownAC = Node->UnknownAC;
    if (!Node->UnknownAC)
        Unknown04 = Node->UnknownA8;
    else
        Node->UnknownAC->UnknownA8 = Node->UnknownA8;
    Unknown08--;
}

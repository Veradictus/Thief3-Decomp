// Game/Unsorted_10C41B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Node_10C42090;

class Class_10C40730
{
public:
    void FUN_10c40730();

    Node_10C42090* Unknown00;
    char Unknown04[4];
    Node_10C42090* Unknown08;
    char Unknown0C[0x18];
    void* Unknown24;
    char Unknown28;
    char Unknown29;
};

struct Node_10C42090 : public Class_10C40730
{
};

class Class_10C42090
{
public:
    void FUN_10c42090(Node_10C42090* Rootnode);
};

// FUNCTION: 0x10C42090 ?FUN_10c42090@Class_10C42090@@QAEXPAUNode_10C42090@@@Z
void Class_10C42090::FUN_10c42090(Node_10C42090* Rootnode)
{
    for (Node_10C42090* Pnode = Rootnode; !Pnode->Unknown29; Rootnode = Pnode)
    {
        FUN_10c42090(Pnode->Unknown08);
        Pnode = Pnode->Unknown00;
        Rootnode->FUN_10c40730();
        ::operator delete(Rootnode);
    }
}

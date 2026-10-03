// Game/Unsorted_10A86510.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A node of the list (Next, Prev) that the index maps a key to.
struct Entry_10C32C30
{
    Entry_10C32C30* Next;
    Entry_10C32C30* Prev;
};

class Class_10A85940
{
public:
    bool FUN_10a86390(const int& Key);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
};

class Class_10C49740 : public Class_10A85940
{
public:
    bool FUN_10c49740(int* Key, Entry_10C32C30** Out);
};

// A list of nodes (Count, Head, Tail) and the hash table indexing them at +0xC.
class Class_10A87C00
{
public:
    int FUN_10a87340(int A);

    int Count;
    Entry_10C32C30* Head;
    Entry_10C32C30* Tail;
    Class_10C49740 Unknown0C;
};

// FUNCTION: 0x10A87340 ?FUN_10a87340@Class_10A87C00@@QAEHH@Z
int Class_10A87C00::FUN_10a87340(int A)
{
    int Key = A;
    Entry_10C32C30* Found;
    Entry_10C32C30* Node = Unknown0C.FUN_10c49740(&Key, &Found) ? Found : 0;
    if (Head == Node)
        Head = Node->Next;
    if (Tail == Node)
        Tail = Node->Prev;
    if (Node->Next)
        Node->Next->Prev = Node->Prev;
    if (Node->Prev)
        Node->Prev->Next = Node->Next;
    Node->Next = (Entry_10C32C30*)-1;
    Node->Prev = (Entry_10C32C30*)-1;
    Count--;
    Key = A;
    Unknown0C.FUN_10a86390(Key);
    delete Node;
    return A;
}

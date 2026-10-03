// Game/Unsorted_109E5340.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109E5700
{
    Struct_109E5700* Unknown00;
    Struct_109E5700* Unknown04;
};

class Class_109E5700
{
public:
    void FUN_109e5700();

    char Unknown00[0x18];
    Struct_109E5700* Unknown18;
    int Unknown1C;
};

class Class_10A4B960
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

void FUN_10a4b960(Class_10A4B960** Out, int A);

class Class_109E5620
{
public:
    void FUN_109e5620(int A, bool B);

    char Unknown00[0x208];
    int Unknown208;
};

// FUNCTION: 0x109E5620 ?FUN_109e5620@Class_109E5620@@QAEXH_N@Z
void Class_109E5620::FUN_109e5620(int A, bool B)
{
    if (!Unknown208 || B)
    {
        Class_10A4B960* Obj;
        FUN_10a4b960(&Obj, A);
        if (Obj)
            Obj->Virtual2();
    }
}

// FUNCTION: 0x109E5700 ?FUN_109e5700@Class_109E5700@@QAEXXZ
void Class_109E5700::FUN_109e5700()
{
    Struct_109E5700* Node = Unknown18->Unknown00;
    Unknown18->Unknown00 = Unknown18;
    Unknown18->Unknown04 = Unknown18;
    Unknown1C = 0;
    while (Node != Unknown18)
    {
        Struct_109E5700* Next = Node->Unknown00;
        delete Node;
        Node = Next;
    }
}

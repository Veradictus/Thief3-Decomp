// Game/Unsorted_10A71C80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A node of the circular list: Unknown00 is the next link.
class Class_10A10C20
{
public:
    Class_10A10C20* Unknown00;
    Class_10A10C20* Unknown04;
};

class Class_10A72750_Iterator
{
public:
    Class_10A72750_Iterator() {}
    Class_10A72750_Iterator(Class_10A10C20* P) { Node = P; }

    Class_10A10C20* Node;
};

class Class_10A111B0
{
public:
    void FUN_10a111b0();

    char Unknown00[0x18];
    Class_10A10C20* Unknown18;
    int Unknown1C;
};

class Class_10A71DB0
{
public:
    void FUN_10a71db0(int Code, const Class_10A72750_Iterator& It);

    char Unknown00[0x14];
};

class Class_10A72750
{
public:
    Class_10A72750_Iterator FUN_10a72750(Class_10A72750_Iterator Where);

    int Unknown00;
    Class_10A111B0 Unknown04;
};

class Class_10A72D30 : public Class_10A72750
{
public:
    Class_10A72750_Iterator FUN_10a72d30(Class_10A72750_Iterator First, Class_10A72750_Iterator Last);

    Class_10A71DB0 Unknown24;
    int Unknown38;
    int Unknown3C;
};

// FUNCTION: 0x10A72D30 ?FUN_10a72d30@Class_10A72D30@@QAE?AVClass_10A72750_Iterator@@V2@0@Z
Class_10A72750_Iterator Class_10A72D30::FUN_10a72d30(Class_10A72750_Iterator First, Class_10A72750_Iterator Last)
{
    if (First.Node == Unknown04.Unknown18->Unknown00 && Last.Node == Unknown04.Unknown18)
    {
        Unknown04.FUN_10a111b0();
        Unknown24.FUN_10a71db0(9, Class_10A72750_Iterator(Unknown04.Unknown18));
        Unknown38 = 1;
        Unknown3C = 1;
        return Class_10A72750_Iterator(Unknown04.Unknown18->Unknown00);
    }
    while (First.Node != Last.Node)
    {
        Class_10A72750_Iterator Old = First;
        First.Node = First.Node->Unknown00;
        FUN_10a72750(Old);
    }
    return First;
}

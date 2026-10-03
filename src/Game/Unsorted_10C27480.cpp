// Game/Unsorted_10C27480.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C27480
{
    int FindIndex(int Value)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Value)
                return i;
        }
        return -1;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E99340
{
public:
    virtual bool FUN_10c27480(Struct_10C27480* List);
};

struct Struct_10C274B0
{
    int Count;
    int Unknown04;
    int* Items;

    int Find(int Value)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Items[i] == Value)
                return i;
        }
        return -1;
    }
};

class Class_10E99348
{
public:
    virtual bool FUN_10c274b0(Struct_10C274B0* List);
};

// FUNCTION: 0x10C27480 ?FUN_10c27480@Class_10E99340@@UAE_NPAUStruct_10C27480@@@Z
bool Class_10E99340::FUN_10c27480(Struct_10C27480* List)
{
    if (List->FindIndex(6) != -1)
        return true;
    return false;
}

// FUNCTION: 0x10C274B0 ?FUN_10c274b0@Class_10E99348@@UAE_NPAUStruct_10C274B0@@@Z
bool Class_10E99348::FUN_10c274b0(Struct_10C274B0* List)
{
    if (List->Find(5) != -1)
        return true;
    return false;
}

// Game/GameTableKeyRemoval.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C48260.h"
#include "Game/Class_10A85940_Field18.h"

// Original node key/value/next offsets are 0/4/8.
class Class_10C49AB0_Node
{
public:
    int Key;
    int Value;
    Class_10C49AB0_Node* Next;
};

// The original target uses the existing table's fields and both key-trait slots.
class Class_10C49740
{
public:
    bool FUN_10c49ab0(const int& Key);
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    char Pad11[3];
    Class_10C49AB0_Node** Unknown14;
    Class_10A85940_Field18 Unknown18;
};

unsigned int HashBytes(const void* Data, int Length);

// FUNCTION: 0x10C49AB0 ?FUN_10c49ab0@Class_10C49740@@QAE_NABH@Z
bool Class_10C49740::FUN_10c49ab0(const int& Key)
{
    if (!Unknown10 && Unknown04 < Unknown0C * 0.05 && Unknown0C > 64)
        ((Class_10C48260*)this)->Rehash(Unknown0C / 2);
    unsigned int Index;
    {
        const void* Data;
        int Length;
        Unknown18.Virtual0(Key, &Data, &Length);
        Index = HashBytes(Data, Length) & ((1 << Unknown08) - 1);
    }
    for (Class_10C49AB0_Node* Node = Unknown14[Index], *Prev = 0; Node; Prev = Node, Node = Node->Next)
    {
        if (Unknown18.Virtual1(Key, Node->Key) == 0)
        {
            if (Prev || Node->Next)
                Unknown00--;
            if (!Prev)
                Unknown14[Index] = Node->Next;
            else
                Prev->Next = Node->Next;
            Unknown04--;
            delete Node;
            return true;
        }
    }
    return false;
}

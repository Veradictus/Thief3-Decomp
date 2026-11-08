// Game/IntegerHashTableSet.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10EBFF38.h"
#include "Game/Class_10C30DD0_Field18.h"
#include "Game/Class_10C30DD0_Node.h"

unsigned int HashBytes(const void* Data, int Length);

class cIntHashTable
{
public:
    unsigned int Insert(const int& Key, const int& Value);
    unsigned int Set(const int& Key, const int& Value);
    int m_Collisions;
    int m_Count;
    int m_BucketBits;
    int m_BucketCount;
    bool m_FixedSize;
    char Pad11[3];
    Class_10C30DD0_Node** m_Buckets;
    Class_10EBFF38 m_KeyTraits;
};

// FUNCTION: 0x10C32430 ?Set@cIntHashTable@@QAEIABH0@Z
unsigned int cIntHashTable::Set(const int& Key, const int& Value)
{
    unsigned int Index;
    {
        const void* Data;
        int Length;
        ((Class_10C30DD0_Field18*)&m_KeyTraits)->Virtual0(Key, &Data, &Length);
        Index = HashBytes(Data, Length) & ((1 << m_BucketBits) - 1);
    }
    if (!m_Buckets)
        return (unsigned int)-1;
    for (Class_10C30DD0_Node* Node = m_Buckets[Index]; Node; Node = Node->Next)
    {
        if (m_KeyTraits.CompareUnsigned((unsigned int*)&Key, (unsigned int*)&Node->Key) == 0)
        {
            Node->Value = Value;
            return Index;
        }
    }
    return Insert(Key, Value);
}

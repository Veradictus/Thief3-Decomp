// Game/Unsorted_10C00A60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

unsigned int FUN_1090e9b0(const void* Data, int Length);

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_10C00B40_Field18
{
public:
    virtual void Virtual0(const __int64& Key, const void** Data, int* Length);
};

// The hash table of 0x1090F080 (Class_1090F080) over another key type.
class Class_10C00B40
{
public:
    unsigned int FUN_10c00b40(const int& Key);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
    Class_10C00B40_Field18 Unknown18;
};

// FUNCTION: 0x10C00B40 ?FUN_10c00b40@Class_10C00B40@@QAEIABH@Z
unsigned int Class_10C00B40::FUN_10c00b40(const int& Key)
{
    const void* Data;
    int Length;
    Unknown18.Virtual0(Key, &Data, &Length);
    return FUN_1090e9b0(Data, Length) & ((1 << Unknown08) - 1);
}

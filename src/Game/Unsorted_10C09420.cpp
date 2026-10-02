// Game/Unsorted_10C09420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C09420
{
public:
    ~Class_10C09420();
};

struct Struct_10C09520
{
    int Count;
    int Unknown04;
    Class_10C09420** Items;
};

// FUNCTION: 0x10C09520 ?FUN_10c09520@@YAXPAUStruct_10C09520@@@Z
void FUN_10c09520(Struct_10C09520* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}

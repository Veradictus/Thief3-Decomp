// Game/Unsorted_10C01F80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C010D0
{
public:
    ~Class_10C010D0();
};

struct Struct_10C01F80
{
    int Count;
    int Unknown04;
    Class_10C010D0** Items;
};

// FUNCTION: 0x10C01F80 ?FUN_10c01f80@@YAXPAUStruct_10C01F80@@@Z
void FUN_10c01f80(Struct_10C01F80* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}

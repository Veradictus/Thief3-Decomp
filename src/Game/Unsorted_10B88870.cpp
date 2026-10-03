// Game/Unsorted_10B88870.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memcpy(void* Dest, const void* Src, unsigned Count);

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

struct Struct_10B88870
{
    int Unknown00;
    void* Unknown04;
    bool Unknown08;
};

class Class_10B88870
{
public:
    void FUN_10b88870(int Index, const void* Data, int Size);

    Struct_10B88870 Unknown00[1];
};

// FUNCTION: 0x10B88870 ?FUN_10b88870@Class_10B88870@@QAEXHPBXH@Z
void Class_10B88870::FUN_10b88870(int Index, const void* Data, int Size)
{
    if (Size)
    {
        void* Block = operator new(Size, 0, 0, 0, 0, 0);
        Unknown00[Index].Unknown04 = Block;
        memcpy(Block, Data, Size);
        Unknown00[Index].Unknown00 = Size;
        Unknown00[Index].Unknown08 = true;
    }
}

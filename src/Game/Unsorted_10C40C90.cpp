// Game/Unsorted_10C40C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C41000_Shared
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

// A smart pointer: copying it takes another reference through slot 1.
class Class_10C41000_Ptr
{
public:
    Class_10C41000_Ptr(const Class_10C41000_Ptr& Other) : Pointer(Other.Pointer)
    {
        if (Pointer)
            Pointer->Virtual1();
    }

    Class_10C41000_Shared* Pointer;
};

struct Struct_10C41000
{
    int Unknown00;
    Class_10C41000_Ptr Unknown04;
    bool Unknown08;
    bool Unknown09;
};

class Class_10C41000_Handle
{
public:
    Class_10C41000_Handle(const Struct_10C41000& D)
        : Unknown00(D.Unknown00), Unknown04(D.Unknown04), Unknown08(D.Unknown08), Unknown09(D.Unknown09), Unknown0C(0)
    {
    }

    int Unknown00;
    Class_10C41000_Ptr Unknown04;
    bool Unknown08;
    bool Unknown09;
    int Unknown0C;
};

class Class_10C41000
{
public:
    Class_10C41000(int A, int B, int C, const Struct_10C41000& D, bool E);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_10C41000_Handle Unknown0C;
    bool Unknown1C;
    bool Unknown1D;
};

// FUNCTION: 0x10C41000 ??0Class_10C41000@@QAE@HHHABUStruct_10C41000@@_N@Z
Class_10C41000::Class_10C41000(int A, int B, int C, const Struct_10C41000& D, bool E)
    : Unknown00(A), Unknown04(B), Unknown08(C), Unknown0C(D), Unknown1C(E), Unknown1D(false)
{
}

// Game/Unsorted_10AA7B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3ddc0(void* Reader, int* Out);

void FUN_10d3d3b0(void* Reader, int* Out);

class Class_10E6C14C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aa7ed0(void* Reader, int A, int B);
    virtual void FUN_10aa7f00(void* Stream, int A, int B);

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

void FUN_10d3d990(void* Stream, int* Value);

void FUN_10d3d2d0(void* Stream, int Value);

// FUNCTION: 0x10AA7ED0 ?FUN_10aa7ed0@Class_10E6C14C@@UAEXPAXHH@Z
void Class_10E6C14C::FUN_10aa7ed0(void* Reader, int A, int B)
{
    FUN_10d3ddc0(Reader, &Unknown08);
    FUN_10d3d3b0(Reader, &Unknown0C);
}

// FUNCTION: 0x10AA7F00 ?FUN_10aa7f00@Class_10E6C14C@@UAEXPAXHH@Z
void Class_10E6C14C::FUN_10aa7f00(void* Stream, int A, int B)
{
    FUN_10d3d990(Stream, &Unknown08);
    FUN_10d3d2d0(Stream, Unknown0C);
}

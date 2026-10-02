// Game/Unsorted_10BB7680.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E662C0
{
public:
    virtual void Virtual0();
};

class Class_10E90938 : public Class_10E662C0
{
public:
    Class_10E90938(int Value) : Unknown04(Value) {}

    virtual Class_10E90938* FUN_10bb7ba0();

    int Unknown04;
};

// FUNCTION: 0x10BB7BA0 ?FUN_10bb7ba0@Class_10E90938@@UAEPAV1@XZ
Class_10E90938* Class_10E90938::FUN_10bb7ba0()
{
    return new(0, 0, 0, 0, 0) Class_10E90938(Unknown04);
}

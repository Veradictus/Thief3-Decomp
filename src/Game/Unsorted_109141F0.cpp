// Game/Unsorted_109141F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10BFBD70();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E4938C
{
public:
    Class_10E4938C(const Class_109081E0& A);

    virtual void Virtual0();

    Class_10BFBD70 Unknown04;
    Class_109081E0 Unknown10;
};

// FUNCTION: 0x109141F0 ??0Class_10E4938C@@QAE@ABVClass_109081E0@@@Z
Class_10E4938C::Class_10E4938C(const Class_109081E0& A) : Unknown10(A)
{
}

// Game/Unsorted_10A2FCF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();

    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

class Class_10A905A0
{
public:
    Class_10A905A0() {}
    virtual ~Class_10A905A0();
};

class Class_10E66390 : public Class_10A905A0
{
public:
    Class_10E66390(const Class_109081E0& A);

    virtual void Virtual1();
    virtual int FUN_10a2fcb0(Class_10E66390* A);

    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10A2FFA0 ??0Class_10E66390@@QAE@ABVClass_109081E0@@@Z
Class_10E66390::Class_10E66390(const Class_109081E0& A)
{
    Unknown04 = A;
}

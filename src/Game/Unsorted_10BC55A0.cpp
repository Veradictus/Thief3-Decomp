// Game/Unsorted_10BC55A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E50610
{
public:
    virtual ~Class_10E50610() {}
};

class Class_10E90914 : public Class_10E50610
{
public:
    Class_10E90914(const Class_109081E0& A);

    virtual void Virtual1();
    virtual bool FUN_10bb44f0(Class_10E90914* Other);

    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10BC6A30 ??0Class_10E90914@@QAE@ABVClass_109081E0@@@Z
Class_10E90914::Class_10E90914(const Class_109081E0& A) : Unknown04(A)
{
}

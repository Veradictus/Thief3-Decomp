// Game/Unsorted_10A30000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();

    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

class Class_10A30060
{
public:
    virtual ~Class_10A30060();
};

class Class_10E663A0 : public Class_10A30060
{
public:
    Class_10E663A0(const Class_109081E0& A);

    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10A30060 ??0Class_10E663A0@@QAE@ABVClass_109081E0@@@Z
Class_10E663A0::Class_10E663A0(const Class_109081E0& A)
{
    Unknown04 = A;
}

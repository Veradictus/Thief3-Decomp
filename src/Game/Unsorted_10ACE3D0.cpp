// Game/Unsorted_10ACE3D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7018C;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E7018C* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

extern void* DAT_10e7018c[];

class Class_10E67938
{
public:
    ~Class_10E67938();

    void** Unknown00;
};

class Class_10E7018C : public Class_10E67938
{
public:
    ~Class_10E7018C();
};

// FUNCTION: 0x10ACE3D0 ??1Class_10E7018C@@QAE@XZ
Class_10E7018C::~Class_10E7018C()
{
    Unknown00 = DAT_10e7018c;
    DAT_10f46da0->Virtual2(this);
}

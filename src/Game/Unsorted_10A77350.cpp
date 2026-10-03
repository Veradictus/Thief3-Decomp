// Game/Unsorted_10A77350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6BD18;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6BD18* Obj, int A, int B, int C);
};

extern Class_10F46DA0* DAT_10f46da0;

extern void* DAT_10e6bd18[];

class Class_10E67938
{
public:
    Class_10E67938();
    ~Class_10E67938();

    void** Unknown00;
};

class Class_10E6BD18 : public Class_10E67938
{
public:
    Class_10E6BD18();
};

// FUNCTION: 0x10A79050 ??0Class_10E6BD18@@QAE@XZ
Class_10E6BD18::Class_10E6BD18()
{
    Unknown00 = DAT_10e6bd18;
    DAT_10f46da0->Virtual1(this, 0x27, -1, -1);
}

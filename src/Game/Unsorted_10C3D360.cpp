// Game/Unsorted_10C3D360.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9B088_Unknown2C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10E9B020
{
public:
    virtual ~Class_10E9B020() {}
};

class Class_10E9B088 : public Class_10E9B020
{
public:
    virtual ~Class_10E9B088();

    char Unknown04[0x28];
    Class_10E9B088_Unknown2C* Unknown2C;
};

// FUNCTION: 0x10C3D360 ??1Class_10E9B088@@UAE@XZ
Class_10E9B088::~Class_10E9B088()
{
    if (Unknown2C)
        Unknown2C->Virtual2();
}

// FUNCTION: 0x10C3D540 ??_GClass_10E9B088@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10C3D360's definition in this unit.

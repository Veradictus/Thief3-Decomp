// Game/Unsorted_10B7A320_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E822B0
{
public:
    Class_10E822B0();

    virtual ~Class_10E822B0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x68];
};

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10BFBD70();

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E68938
{
public:
    Class_10E68938();

    virtual ~Class_10E68938();

    char Unknown04[0x134];
};

class Class_10B59770
{
public:
    Class_10B59770() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10B59770();

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E88900 : public Class_10E822B0
{
public:
    Class_10E88900();

    virtual ~Class_10E88900();

    int Unknown154;
    int Unknown158;
    int Unknown15C;
    int Unknown160;
    Class_10BFBD70 Unknown164;
    Class_10BFBD70 Unknown170;
    bool Unknown17C;
    Class_10E68938 Unknown180;
    int Unknown2B8;
    int Unknown2BC;
    Class_10B59770 Unknown2C0;
};

// FUNCTION: 0x10B7A6F0 ??0Class_10E88900@@QAE@XZ
Class_10E88900::Class_10E88900()
    : Unknown154(0), Unknown158(0), Unknown15C(-1), Unknown160(-1), Unknown17C(false), Unknown2B8(0),
      Unknown2BC(0)
{
    Unknown0E8 = 6;
}

// FUNCTION: 0x10B7A7B0 ??_GClass_10E88900@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B7A6F0's definition in this unit.

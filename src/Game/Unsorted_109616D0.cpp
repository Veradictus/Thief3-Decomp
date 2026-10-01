// Game/Unsorted_109616D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4b238[];

extern void* DAT_10e4b230[];

class Class_10E4B180
{
public:
    Class_10E4B180();

    void** Unknown00;
    char Unknown04[0x28];
    void** Unknown2C;
};

class Class_10E4B238 : public Class_10E4B180
{
public:
    Class_10E4B238* FUN_109618a0();
};

// FUNCTION: 0x109618A0 ?FUN_109618a0@Class_10E4B238@@QAEPAV1@XZ
Class_10E4B238* Class_10E4B238::FUN_109618a0()
{
    this->Class_10E4B180::Class_10E4B180();
    Unknown00 = DAT_10e4b238;
    Unknown2C = DAT_10e4b230;
    return this;
}

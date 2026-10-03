// Game/Unsorted_109431A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();
    Class_109081E0& FUN_1090a590(const char* In);

    char* Unknown00;
};

class Class_10943490
{
public:
    Class_10943490();

    Class_109081E0 Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10943490 ??0Class_10943490@@QAE@XZ
Class_10943490::Class_10943490()
    : Unknown04(0), Unknown08(0)
{
    Unknown00.FUN_1090a590(DAT_10e47660);
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
}

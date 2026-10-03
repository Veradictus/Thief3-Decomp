// Game/Unsorted_10C61E70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    Class_109081E0(const char* Text);
    Class_109081E0& operator=(const Class_109081E0& Other);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E9CA9C
{
public:
    virtual void Virtual0();
    virtual void __stdcall FUN_10c62760(const char* Text);

    int Unknown04;
    Class_109081E0 Unknown08;
};

// FUNCTION: 0x10C62760 ?FUN_10c62760@Class_10E9CA9C@@UAGXPBD@Z
void __stdcall Class_10E9CA9C::FUN_10c62760(const char* Text)
{
    Unknown08 = Text;
}

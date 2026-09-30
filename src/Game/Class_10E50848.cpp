// Game/Class_10E50848.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF82B0
{
public:
    Class_10AF82B0(const char* A);

    char Unknown00[0xC];
};

class Class_10E50848 : public Class_10AF82B0
{
public:
    Class_10E50848(const char* A, bool B);

    virtual void Virtual0();

    bool Unknown10;
};

// FUNCTION: 0x10983D40 ??0Class_10E50848@@QAE@PBD_N@Z
Class_10E50848::Class_10E50848(const char* A, bool B) : Class_10AF82B0(A)
{
    Unknown10 = B;
}

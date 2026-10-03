// Game/Unsorted_10BD0270_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BD0270
{
public:
    ~Class_10BD0270();
};

class Class_10E93020
{
public:
    void FUN_10bd03d0();

    char Unknown00[0x40];
    Class_10BD0270* Unknown40;
    int Unknown44[4];
};

// FUNCTION: 0x10BD03D0 ?FUN_10bd03d0@Class_10E93020@@QAEXXZ
void Class_10E93020::FUN_10bd03d0()
{
    if (Unknown40)
    {
        delete Unknown40;
        Unknown40 = 0;
        for (int i = 0; i < 3; i++)
            Unknown44[i] = Unknown44[i + 1];
    }
}

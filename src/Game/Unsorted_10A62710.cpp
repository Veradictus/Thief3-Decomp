// Game/Unsorted_10A62710.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.


class Class_1091AA50
{
public:
    void FUN_1091aa50();
};

class Class_10E6A9CC
{
public:
    ~Class_10E6A9CC();

    virtual void Virtual0();

    char Unknown04[8];
    Class_1091AA50* Unknown0C;
};

// FUNCTION: 0x10A62AA0 ??1Class_10E6A9CC@@QAE@XZ
Class_10E6A9CC::~Class_10E6A9CC()
{
    Class_1091AA50* Object = Unknown0C;
    if (Object)
    {
        Object->FUN_1091aa50();
        ::operator delete(Object);
    }
}

// Game/USwooshLinkDataObject_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    virtual void Virtual0();

    char Unknown04[0x28];
};

class Class_10B7C000 : public Class_10E70A50
{
public:
    void FUN_10ad5310();
};

class Class_10E55E78 : public Class_10B7C000
{
public:
    ~Class_10E55E78();

    virtual void Virtual0();
};

class USwooshLinkDataObject : public Class_10E55E78
{
public:
    ~USwooshLinkDataObject();
};

// FUNCTION: 0x109A1120 ??1USwooshLinkDataObject@@QAE@XZ
USwooshLinkDataObject::~USwooshLinkDataObject()
{
    FUN_10ad5310();
}

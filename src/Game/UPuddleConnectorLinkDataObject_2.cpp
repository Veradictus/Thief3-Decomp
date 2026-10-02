// Game/UPuddleConnectorLinkDataObject_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class UPuddleConnectorLinkDataObject : public Class_10E55E78
{
public:
    ~UPuddleConnectorLinkDataObject();
};

// FUNCTION: 0x109A0BD0 ??1UPuddleConnectorLinkDataObject@@QAE@XZ
UPuddleConnectorLinkDataObject::~UPuddleConnectorLinkDataObject()
{
    FUN_10ad5310();
}

// Game/UAssociationLinkDataObject_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class UAssociationLinkDataObject : public Class_10E55E78
{
public:
    ~UAssociationLinkDataObject();
};

// FUNCTION: 0x1099F400 ??1UAssociationLinkDataObject@@QAE@XZ
UAssociationLinkDataObject::~UAssociationLinkDataObject()
{
    FUN_10ad5310();
}

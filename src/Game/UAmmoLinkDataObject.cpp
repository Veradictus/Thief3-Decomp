// Game/UAmmoLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class UAmmoLinkDataObject : public Class_10E55E78
{
public:
    ~UAmmoLinkDataObject();
};

// FUNCTION: 0x1099F370 ??1UAmmoLinkDataObject@@QAE@XZ
UAmmoLinkDataObject::~UAmmoLinkDataObject()
{
    FUN_10ad5310();
}

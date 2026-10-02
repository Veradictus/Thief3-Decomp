// Game/AStimulusModifierObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();
};

class Class_10B7C000 : public Class_10E70A50
{
public:
    void FUN_10ad5310();
};

class Class_10993EC0 : public Class_10B7C000
{
public:
    virtual void FUN_10adb3a0();
};

class AMetaProperty : public Class_10993EC0
{
public:
    ~AMetaProperty();
};

class AStimulusModifierObject : public AMetaProperty
{
public:
    ~AStimulusModifierObject();
};

// FUNCTION: 0x1099BA50 ??1AStimulusModifierObject@@QAE@XZ
AStimulusModifierObject::~AStimulusModifierObject()
{
    FUN_10ad5310();
}

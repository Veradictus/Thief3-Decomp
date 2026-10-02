// Game/AAIFactionModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
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

class AAIModel : public Class_10993EC0
{
public:
    ~AAIModel();
};

class AAIFactionModel : public AAIModel
{
public:
    ~AAIFactionModel();
};

// FUNCTION: 0x109629F0 ??1AAIFactionModel@@QAE@XZ
AAIFactionModel::~AAIFactionModel()
{
    FUN_10ad5310();
}

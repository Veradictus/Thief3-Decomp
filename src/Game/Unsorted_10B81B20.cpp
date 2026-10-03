// Game/Unsorted_10B81B20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10CA8290
{
public:
    void FUN_10ca8290(float A);
};

class Class_10CA8460
{
public:
    Class_10CA8290* FUN_10ca8460(int A);
};

extern float DAT_11006e30;

extern float DAT_10e499a0;

class Class_10B81B20
{
public:
    void FUN_10b81b20(float A);

    char Unknown00[0x94];
    Class_10CA8460* Unknown94;
};

// FUNCTION: 0x10B81B20 ?FUN_10b81b20@Class_10B81B20@@QAEXM@Z
void Class_10B81B20::FUN_10b81b20(float A)
{
    Class_10CA8460* Source = Unknown94;
    if (Source)
    {
        Class_10CA8290* Target = Source->FUN_10ca8460(1);
        if (Target)
        {
            float Scaled = DAT_11006e30 * A;
            Target->FUN_10ca8290(Scaled * DAT_10e499a0);
        }
    }
}

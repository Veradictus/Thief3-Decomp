// Game/Class_10B3ADC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// OR field of parameter with immediate value

class Object_10B3ADC0 {
public:
    char Unknown00[0x450];
    int Field450;
};

class Class_10B3ADC0 {
public:
    void FUN_10b3adc0(Object_10B3ADC0* param);
};

// FUNCTION: 0x10B3ADC0 ?FUN_10b3adc0@Class_10B3ADC0@@QAEXPAVObject_10B3ADC0@@@Z
void Class_10B3ADC0::FUN_10b3adc0(Object_10B3ADC0* param)
{
    param->Field450 |= 0x4;
}

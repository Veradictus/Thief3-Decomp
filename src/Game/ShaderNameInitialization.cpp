// Game/ShaderNameInitialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Physical base prefix used by the shader-name initializer; no object lifetime is emitted.
#include "Game/cString.h"

struct Struct_1093FFE0;

class Class_10E4A538
{
public:
    virtual void FUN_109412f0();
    virtual bool Virtual1();
    virtual void Virtual2();

    ~Class_10E4A538();

    char FUN_10940970();
    void Reset();
    void BuildTextureMatrix(int Width, int Height, Struct_1093FFE0* Out);

    bool Unknown04;
    char Opaque05[3];
    cString Unknown08[47];
    char UnknownC4[0xBC];
    cString Unknown180[47];
    char Pad23C[0xc0];
    int Unknown2FC;
};

class Class_10E49F90 : public Class_10E4A538
{
public:
    virtual bool Virtual1();
};

// FUNCTION: 0x109362D0 ?Virtual1@Class_10E49F90@@UAE_NXZ
bool Class_10E49F90::Virtual1()
{
    if (!Unknown04)
    {
        if (!Class_10E4A538::Virtual1())
            return false;
        Unknown08[0].FUN_1090a590("DirLight11");
        Unknown180[0].FUN_1090a590("DirLight11");
        Unknown08[1].FUN_1090a590("DirLightAlpha11");
        Unknown180[1].FUN_1090a590("DirLightAlpha11");
        Unknown08[2].FUN_1090a590("DirLightSpec11");
        Unknown180[2].FUN_1090a590("DirLightSpec11");
        Unknown08[3].FUN_1090a590("DirLightNormal11");
        Unknown180[3].FUN_1090a590("DirLightNormal11");
        Unknown08[4].FUN_1090a590("DirLightNormalAlpha11");
        Unknown180[4].FUN_1090a590("DirLightNormalAlpha11");
        Unknown08[5].FUN_1090a590("DirLightNormalSpec11");
        Unknown180[5].FUN_1090a590("DirLightNormalSpec11");
        Unknown08[6].FUN_1090a590("OmniLight11");
        Unknown180[6].FUN_1090a590("OmniLight11");
        Unknown08[7].FUN_1090a590("OmniLightAlpha11");
        Unknown180[7].FUN_1090a590("OmniLightAlpha11");
        Unknown08[8].FUN_1090a590("OmniLightSpec11");
        Unknown180[8].FUN_1090a590("OmniLightSpec11");
        Unknown08[9].FUN_1090a590("OmniLightNormal11");
        Unknown180[9].FUN_1090a590("OmniLightNormal11");
        Unknown08[10].FUN_1090a590("OmniLightNormalAlpha11");
        Unknown180[10].FUN_1090a590("OmniLightNormalAlpha11");
        Unknown08[11].FUN_1090a590("OmniLightNormalSpec11");
        Unknown180[11].FUN_1090a590("OmniLightNormalSpec11");
        Unknown08[12].FUN_1090a590("SpotLight11");
        Unknown180[12].FUN_1090a590("SpotLight11");
        Unknown08[13].FUN_1090a590("SpotLightAlpha11");
        Unknown180[13].FUN_1090a590("SpotLightAlpha11");
        Unknown08[14].FUN_1090a590("SpotLightSpec11");
        Unknown180[14].FUN_1090a590("SpotLightSpec11");
        Unknown08[15].FUN_1090a590("SpotLightNormal11");
        Unknown180[15].FUN_1090a590("SpotLightNormal11");
        Unknown08[16].FUN_1090a590("SpotLightNormalAlpha11");
        Unknown180[16].FUN_1090a590("SpotLightNormalAlpha11");
        Unknown08[17].FUN_1090a590("SpotLightNormalSpec11");
        Unknown180[17].FUN_1090a590("SpotLightNormalSpec11");
        Unknown08[18].FUN_1090a590("ProjLight11");
        Unknown180[18].FUN_1090a590("ProjLight11");
        Unknown08[19].FUN_1090a590("ProjLightAlpha11");
        Unknown180[19].FUN_1090a590("ProjLightAlpha11");
        Unknown08[20].FUN_1090a590("Specular11");
        Unknown180[20].FUN_1090a590("Specular11");
        Unknown08[21].FUN_1090a590("Ambient11");
        Unknown180[21].FUN_1090a590("Ambient11");
        Unknown08[22].FUN_1090a590("Ambient11");
        Unknown180[22].FUN_1090a590("AmbientNormal11");
        Unknown08[23].FUN_1090a590("VertAmbLight11");
        Unknown180[23].FUN_1090a590("Ambient11");
        Unknown08[24].FUN_1090a590("VertAmbLight11");
        Unknown180[24].FUN_1090a590("AmbientNormal11");
        Unknown08[25].FUN_1090a590("Ambient11");
        Unknown180[25].FUN_1090a590("AmbientSpec11");
        Unknown08[26].FUN_1090a590("Ambient11");
        Unknown180[26].FUN_1090a590("AmbientNormalSpec11");
        Unknown08[27].FUN_1090a590("VertAmbLight11");
        Unknown180[27].FUN_1090a590("AmbientSpec11");
        Unknown08[28].FUN_1090a590("VertAmbLight11");
        Unknown180[28].FUN_1090a590("AmbientNormalSpec11");
        Unknown08[32].FUN_1090a590("Fog11");
        Unknown180[32].FUN_1090a590("Fog11");
        Unknown08[33].FUN_1090a590("Fog11");
        Unknown180[33].FUN_1090a590("FogAlpha11");
        Unknown08[34].FUN_1090a590("Fog11");
        Unknown180[34].FUN_1090a590("FogAlphaTest11");
        Unknown08[35].FUN_1090a590("AmbientAlphaBlend11");
        Unknown180[35].FUN_1090a590("AmbientAlphaBlend11");
        Unknown08[36].FUN_1090a590("VertAmbLightAlphaBlend11");
        Unknown180[36].FUN_1090a590("AmbientAlphaBlend11");
        Unknown08[37].FUN_1090a590("OmniLightAlphaBlend11");
        Unknown180[37].FUN_1090a590("OmniLightAlphaBlend11");
        Unknown08[38].FUN_1090a590("SpotLightAlphaBlend11");
        Unknown180[38].FUN_1090a590("SpotLightAlphaBlend11");
        Unknown08[39].FUN_1090a590("DirLightAlphaBlend11");
        Unknown180[39].FUN_1090a590("DirLightAlphaBlend11");
        Unknown08[40].FUN_1090a590("OmniLightAlpha11");
        Unknown180[40].FUN_1090a590("OmniLightAlphaDistAtten11");
        Unknown08[41].FUN_1090a590("SpotLightAlpha11");
        Unknown180[41].FUN_1090a590("SpotLightAlphaDistAtten11");
        Unknown08[42].FUN_1090a590("DirLightAlpha11");
        Unknown180[42].FUN_1090a590("DirLightAlphaDistAtten11");
        Unknown04 = true;
    }
    return true;
}

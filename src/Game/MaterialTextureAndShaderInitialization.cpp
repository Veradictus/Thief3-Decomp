// Game/MaterialTextureAndShaderInitialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"

class Class_1093EDB0
{
public:
 bool FUN_1093f180(cString* Name,int Kind,int Flag,int* OutHandle);
 bool FUN_1093f5e0(cString* Name,int Kind,int Flag,int* OutHandle);
};

extern Class_1093EDB0* DAT_10f340c0;

extern bool DAT_10ffc854;

void* FUN_1092cac0(const char* Name,int A,int B,int C,int D,int E);

// Physical POD copy views; unknown channel tails retain their original bytes.
struct MaterialWords775 { unsigned int A,B,C,D; };

struct MaterialChannel775
{
    unsigned int A,B;
    MaterialWords775 First;
    unsigned int C,D;
    MaterialWords775 Second;
    char Unknown30[0x10];
};

struct MaterialInput775
{
    cString TextureNames[4];
    cString VertexName,PixelName;
    MaterialWords775 Parameters;
    unsigned int Flags;
    unsigned char Enabled,Mode;
    char Pad2E[2];
    MaterialChannel775 Channels[4];
    MaterialWords775 Tail;
};

class Class_10E4AA94
{
public:
    virtual ~Class_10E4AA94();
    bool Initialize(MaterialInput775* Input);

    cString VertexName,PixelName;
    int VertexHandle,PixelHandle;
    void* Textures[4];
    MaterialWords775 Parameters;
    unsigned int Flags;
    int Unknown38;
    unsigned char Enabled,Mode;
    char Pad3E[2];
    MaterialChannel775 Channels[4];
    MaterialWords775 Tail;
};

// FUNCTION: 0x1094DBF0 ?Initialize@Class_10E4AA94@@QAE_NPAUMaterialInput775@@@Z
bool Class_10E4AA94::Initialize(MaterialInput775* Input)
{
    VertexHandle = 0;
    PixelHandle = 0;
    VertexName.FUN_1090a590(DAT_10e47660);
    PixelName.FUN_1090a590(DAT_10e47660);
    for (int Index=0; Index<4; ++Index)
    {
        Textures[Index] = 0;
        if (!Input->TextureNames[Index].IsEmpty())
        {
            Textures[Index] = FUN_1092cac0(Input->TextureNames[Index].Unknown00,0,0,0,0,0);
            if (!Textures[Index])
                return false;
        }
    }
    if (!Input->VertexName.IsEmpty())
    {
        if (DAT_10ffc854)
            DAT_10f340c0->FUN_1093f5e0(&Input->VertexName,0,0,&VertexHandle);
        else
            DAT_10f340c0->FUN_1093f180(&Input->VertexName,0,0,&VertexHandle);
    }
    else
        VertexHandle = 2;
    if (!Input->PixelName.IsEmpty())
    {
        if (DAT_10ffc854)
            DAT_10f340c0->FUN_1093f5e0(&Input->PixelName,0,1,&PixelHandle);
        else
            DAT_10f340c0->FUN_1093f180(&Input->PixelName,0,1,&PixelHandle);
    }
    Unknown38 = 0;
    VertexName = Input->VertexName;
    PixelName = Input->PixelName;
    Enabled = Input->Enabled;
    Flags = Input->Flags;
    Parameters = Input->Parameters;
    Mode = Input->Mode;
    Tail = Input->Tail;
    Channels[0].C = Input->Channels[0].C;
    Channels[0].D = Input->Channels[0].D;
    Channels[0].Second = Input->Channels[0].Second;
    Channels[0].First = Input->Channels[0].First;
    Channels[0].A = Input->Channels[0].A;
    Channels[0].B = Input->Channels[0].B;
    Channels[1].C = Input->Channels[1].C;
    Channels[1].D = Input->Channels[1].D;
    Channels[1].Second = Input->Channels[1].Second;
    Channels[1].First = Input->Channels[1].First;
    Channels[1].A = Input->Channels[1].A;
    Channels[1].B = Input->Channels[1].B;
    Channels[2].C = Input->Channels[2].C;
    Channels[2].D = Input->Channels[2].D;
    Channels[2].Second = Input->Channels[2].Second;
    Channels[2].First = Input->Channels[2].First;
    Channels[2].A = Input->Channels[2].A;
    Channels[2].B = Input->Channels[2].B;
    Channels[3].C = Input->Channels[3].C;
    Channels[3].D = Input->Channels[3].D;
    Channels[3].Second = Input->Channels[3].Second;
    Channels[3].First = Input->Channels[3].First;
    Channels[3].A = Input->Channels[3].A;
    Channels[3].B = Input->Channels[3].B;
    return true;
}

// Game/Unsorted_10947430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// FUNCTION: 0x10947430 ?FUN_10947430@@YGPBDI@Z
const char* __stdcall FUN_10947430(unsigned int Type)
{
    const char* Names[19] =
    {
        "BSP Nodes                ",
        "BSP Leaves               ",
        "BSP Polys                ",
        "BSP Planes               ",
        "BSP Rooms                ",
        "BSP Low Tris/Leaf        ",
        "BSP Low Shad Tris/Leaf   ",
        "BSP Avg Tris/Leaf        ",
        "BSP Avg Shad Tris/Leaf   ",
        "BSP Hi  Tris/Leaf        ",
        "BSP Hi  Shad Tris/Leaf   ",
        "BSP Low Objs/Leaf        ",
        "BSP Avg Objs/Leaf        ",
        "BSP Hi  Objs/Leaf        ",
        "BSP Runtime              ",
        "BSP Mesh                 ",
        "BSP sizeof(BContent)     ",
        "BSP sizeof(TriangleGroup)",
        "BSP Avg Triangle Group   ",
    };
    if (Type < 19)
        return Names[Type];
    return "<undefined bspinfo type>";
}

#pragma once

// Definition of a vertex, 32 bit aligned
struct Vertex
{
	float x, y; // position
	float u, v; // texture UV
	float r, g, b, a; // Color-information
};

struct VBOVertex
{
	float x, y;
};
struct VBOTexCoord
{
	float u, v;
};
struct VBOColor
{
	float r,g,b,a;
};

typedef unsigned short int VertexIndex;
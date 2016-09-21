#pragma once
#ifndef PI
#define PI 3.14159265
#endif
#include <string>

#include <sdl.h>
#include <sdl_opengl.h>
#include <GL/glext.h>
#include <SDL_gfxBlitFunc.h>
#include "random.h"


// Packet Identifiers
enum PacketIdent
{
	PACKET_PING				= 0x00,
	PACKET_PONG				= 0x01,
	PACKET_MYNAMEIS			= 0x02,
	PACKET_ANYONETHERE		= 0x03,
	PACKET_WELCOMEIN		= 0x04,
	PACKET_IMFULL			= 0x05,
	PACKET_YOUAREBLACK		= 0x06,
	PACKET_YOUAREWHITE		= 0x07,
	PACKET_YOUAREOBSERVING	= 0x08,
	PACKET_NAMELIST			= 0x09,
	PACKET_IMLEAVING		= 0x0A,
	PACKET_CONNECTIONLOST	= 0x0B,
	PACKET_BLACKMOVE		= 0x0C,
	PACKET_WHITEMOVE		= 0x0D,
	PACKET_MOVEOVER			= 0x0E,
	PACKET_WINNER			= 0x0F,
};
// End of Packet Identifiers

Uint8 GetPacketID(Uint8 in);
Uint8 GetSenderID(Uint8 in);


struct Pos2D
{
	public:
		float x, y;
		Pos2D(float X, float Y);
		//Pos2D(Pos2D& pos2d);
		Pos2D();
};
struct Tint
{
	float R, G, B, A;
	Tint(float r, float g, float b, float a);
	Tint();
};

extern Tint TINT_BLK;
extern Tint TINT_WHT;
extern Tint TINT_RED;
extern Tint TINT_GRN;
extern Tint TINT_BLU;
bool isPowerTwo(int x);

std::string glErrorString(GLenum error);

bool exceptionError();

float degtorad(float deg);
float radtodeg(float rad);
int NextPowTwo(int num);

std::string FormatString(char* string, ...);

SDL_Surface* ResizeSurface(SDL_Surface* srf, int newWidth, int newHeight);
void AlphaBlit(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dest, SDL_Rect* destrect);
void AlphaFillRect(SDL_Surface* src, SDL_Rect* rect, Uint32 RGBA);
bool glExtensionAvailable(std::string extension);

extern PFNGLGENBUFFERSARBPROC		pglGenBuffersARB;
extern PFNGLBINDBUFFERARBPROC		pglBindBufferARB;
extern PFNGLBUFFERDATAARBPROC		pglBufferDataARB;
extern PFNGLDELETEBUFFERSARBPROC	pglDeleteBuffersARB;
extern PFNGLDRAWRANGEELEMENTSPROC	pglDrawRangeElements;

extern int TestCntr;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

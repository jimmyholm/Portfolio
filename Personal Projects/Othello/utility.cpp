#include "utility.h"


PFNGLGENBUFFERSARBPROC		pglGenBuffersARB = 0;
PFNGLBINDBUFFERARBPROC		pglBindBufferARB = 0;
PFNGLBUFFERDATAARBPROC		pglBufferDataARB = 0;
PFNGLDELETEBUFFERSARBPROC	pglDeleteBuffersARB = 0;
PFNGLDRAWRANGEELEMENTSPROC	pglDrawRangeElements = 0;

int TestCntr = 0;

bool isPowerTwo(int x)
{
	return ( (x > 0) && ((x & (x - 1)) == 0) );
}

Tint::Tint(float r, float g, float b, float a) : R(r), G(g), B(b), A(a)
{
}

Tint::Tint() : R(0.0f), G(0.0f), B(0.0f), A(0.0f)
{
}

Pos2D::Pos2D(float X, float Y) : x(X), y(Y)
{
}
Pos2D::Pos2D() : x(0.0f), y(0.0f)
{
}

/*Pos2D::Pos2D(Pos2D& pos2d) : x(pos2d.x), y(pos2d.y)
{

}*/

std::string glErrorString(GLenum error)
{
	switch(error)
	{
		case GL_NO_ERROR:
			return "No error!";
			break;
		case GL_INVALID_ENUM:
			return "An unacceptable value is specified for an enumerated argument.";
			break;
		case GL_INVALID_VALUE:
			return "A numeric argument is out of range.";
			break;
		case GL_INVALID_OPERATION:
			return "The specified operation is not allowed in the current state.";
			break;
		case GL_STACK_OVERFLOW:
			return "This command would cause a stack overflow!";
			break;
		case GL_OUT_OF_MEMORY:
			return "There is not enough memory left to execute the command.";
			break;
		case GL_TABLE_TOO_LARGE:
			return "The specified table exceeds the implementation's maximum supported table size.";
			break;
		default:
			return "Undefined Error!";
	}
	return "Undefined Error!";
}

bool exceptionError()
{
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		throw std::exception(glErrorString(error).c_str());
		return false;
	}
	return true;
}

float degtorad(float deg)
{
	 return (float)(deg * PI / 180);
}

float radtodeg(float rad)
{
	return (float)(rad * 180/PI);
}

int NextPowTwo(int num)
{
	int x = num;
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}

std::string FormatString(char* string, ...)
{
	std::string ret;
	va_list args; va_start(args, string);
	char buf[1024];
	vsprintf_s(buf, 1024, string, args);
	ret = buf;
	return ret;
}

SDL_Surface* ResizeSurface(SDL_Surface* surface, int NewWidth, int NewHeight)
{
	if(surface == NULL)
		return NULL;
	SDL_Surface* ret = SDL_CreateRGBSurface(surface->flags, NewWidth, NewHeight, 32, 0x00FF0000, 0x0000FF00,
											0x000000FF, 0xFF000000);
	AlphaFillRect(ret, 0, 0);
	AlphaBlit(surface, 0, ret, 0);
	SDL_FreeSurface(surface);
	
	return ret;
}

void AlphaBlit(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dest, SDL_Rect* destrect)
{
	if(src == NULL || dest == NULL)
		return;
	SDL_Rect sr, dr;
	if(srcrect == NULL)
	{
		sr.x = 0;
		sr.y = 0;
		sr.w = src->w;
		sr.h = src->h;
	}
	else
		memcpy(&sr, srcrect, sizeof(SDL_Rect));

	if(destrect == NULL)
	{
		dr.x = 0;
		dr.y = 0;
		dr.w = 0;
		dr.h = 0;
	}
	else
		memcpy(&dr, destrect, sizeof(SDL_Rect));

	if(sr.x+sr.w > dest->w)
		sr.w = (sr.x+sr.w) - dest->w;
	if(sr.y+sr.h > dest->h)
		sr.h = (sr.y+sr.h) - dest->h;

	int PixelsToCopy = sr.w * 4;
	if(SDL_MUSTLOCK(src))
		SDL_LockSurface(src);
	if(SDL_MUSTLOCK(dest))
		SDL_LockSurface(dest);
	unsigned char* srcPixels = static_cast<unsigned char*>(src->pixels);
	unsigned char* destPixels = static_cast<unsigned char*>(dest->pixels);

	for(int y = sr.y; y < sr.h; y++)
	{
		unsigned char* source = &srcPixels[sr.x+y*src->pitch];
		unsigned char* destin = &destPixels[dr.x+dr.y+(y-sr.y)*dest->pitch];
		memcpy(destin, source, PixelsToCopy);
	}
	if(SDL_MUSTLOCK(src))
		SDL_UnlockSurface(src);
	if(SDL_MUSTLOCK(dest))
		SDL_UnlockSurface(dest);
}

void AlphaFillRect(SDL_Surface* surface, SDL_Rect* rect, Uint32 RGBA)
{
	if(surface == NULL)
		return;
	SDL_Rect sr;
	if(rect == NULL)
	{
		sr.x = 0;
		sr.y = 0;
		sr.w = surface->w;
		sr.h = surface->h;
	}
	else
		memcpy(&sr, rect, sizeof(SDL_Rect));

	if(sr.x+sr.w > surface->w)
		sr.w = (sr.x+sr.w) - surface->w;
	if(sr.y+sr.h > surface->h)
		sr.h = (sr.y+sr.h) - surface->h;

	int PixelsToFill = sr.w * sizeof(RGBA);
	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
	unsigned char* srcPixels = static_cast<unsigned char*>(surface->pixels);
	for(int y = sr.y; y < sr.h; y++)
	{
		unsigned char* pixels = &srcPixels[sr.x+y*surface->pitch];
		for(int i = 0; i < sr.w; i++)
		{
			*(pixels+(i*4)) = RGBA;
			RGBA = RGBA;
		}
	}
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

bool glExtensionAvailable(std::string extension)
{
	std::string extlist((char*)glGetString(GL_EXTENSIONS));
	if(extension.empty() || extlist.empty())
		return false;
	while(!extlist.empty())
	{
		size_t firstextlength = extlist.find(" ");
		if(extension.length() == firstextlength)
		{
			if(extension == extlist.substr(0, firstextlength))
				return true;
		}
		extlist = extlist.substr(firstextlength+1);
	}
	return true;
}

Uint8 GetPacketID(Uint8 in)
{
	return in & 0x0F;
}

Uint8 GetSenderID(Uint8 in)
{
	return (in & 0xF0) >> 4;
}

Tint TINT_BLK = Tint( .0f , .0f,  .0f, 1.0f);
Tint TINT_WHT = Tint(1.0f, 1.0f, 1.0f, 1.0f);
Tint TINT_RED = Tint(1.0f,  .0f,  .0f, 1.0f);
Tint TINT_GRN = Tint( .0f, 1.0f,  .0f, 1.0f);
Tint TINT_BLU = Tint( .0f,  .0f, 1.0f, 1.0f);
#include "Texture.h"
#include "utility.h"
#include "TextureManager.h"
#include <exception>

DrawInfo::DrawInfo(float X, float Y, int W, int H, float R, float G, float B, float A, bool centered, float Xscale, float Yscale, float rotate) : r(R), g(G), b(B), a(A) 
{
	if(!centered)
	{
		p1.first =	X + W * Xscale;
		p1.second = Y;
		p2.first =	X;
		p2.second =	Y;
		p3.first =	X;
		p3.second = Y + H * Yscale;
		p4.first =	X + W * Xscale;
		p4.second = Y + H * Yscale;
	}
	else
	{
		int hW = W/2;
		int hH = H/2;
		p1.first =	X + hW	+ (hW*(Xscale-1.0f));
		p1.second = Y - hH	- (hH*(Yscale-1.0f));
		p2.first =	X - hW	- (hW*(Xscale-1.0f));
		p2.second = Y - hH	- (hH*(Yscale-1.0f));
		p3.first =	X - hW	- (hW*(Xscale-1.0f));
		p3.second = Y + hH	+ (hH*(Yscale-1.0f));
		p4.first =	X + hW	+ (hW*(Xscale-1.0f));
		p4.second = Y + hH	+ (hH*(Yscale-1.0f));
	}
	if(rotate != 0.0f)
	{
		rotate = degtorad(rotate);
		int hW = W/2;
		int hH = H/2;
		point pp1, pp2, pp3, pp4;
		pp1.first	= hW	+ (hW*(Xscale-1.0f));
		pp1.second	= -hH	- (hH*(Yscale-1.0f));
		pp2.first	= -hW	- (hW*(Xscale-1.0f));
		pp2.second	= -hH	- (hH*(Yscale-1.0f));
		pp3.first	= -hW	- (hW*(Xscale-1.0f));
		pp3.second	= hH	+ (hH*(Yscale-1.0f));
		pp4.first	= hW	+ (hW*(Xscale-1.0f));
		pp4.second	= hH	+ (hH*(Yscale-1.0f));

		point center;
		if(centered)
		{
			center.first	= X;
			center.second	= Y;
		}
		else
		{
			center.first	= X+hW;
			center.second	= Y+hH;
		}

		vmml::matrix<2,2> rotMatrix;
		vmml::vector<2> vertex;
		rotMatrix(0,0) = cos(rotate);
		rotMatrix(0,1) = -sin(rotate);
		rotMatrix(1,0) = sin(rotate);
		rotMatrix(1,1) = cos(rotate);
		vertex[0]	= pp1.first;
		vertex[1]	= pp1.second;
		vertex		= rotMatrix*vertex;
		p1.first	= (float)vertex[0] + center.first;
		p1.second	= (float)vertex[1] + center.second;
		vertex[0]	= pp2.first;
		vertex[1]	= pp2.second;
		vertex		= rotMatrix*vertex;
		p2.first	= (float)vertex[0] + center.first;
		p2.second	= (float)vertex[1] + center.second;
		vertex[0]	= pp3.first;
		vertex[1]	= pp3.second;
		vertex	= rotMatrix*vertex;
		p3.first	= (float)vertex[0] + center.first;
		p3.second	= (float)vertex[1] + center.second;
		vertex[0]	= pp4.first;
		vertex[1]	= pp4.second;
		vertex	= rotMatrix*vertex;
		p4.first	= (float)vertex[0] + center.first;
		p4.second	= (float)vertex[1] + center.second;
	}
}


GLboolean Texture::isTexture()
{
	return glIsTexture(m_texture);
}

bool Texture::LoadTexture(std::string filename)
{
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		throw std::exception(glErrorString(error).c_str());
		return false;
	}
	SDL_Surface* temp = IMG_Load(filename.c_str());
	if(temp == NULL)
	{
		throw std::exception(FormatString("File not found or unreadable: %s", filename.c_str()).c_str());
		return false;
	}
	FileName = filename;
	bool retVal = TextureFromSurface(temp);
	
	return retVal;
}

bool Texture::TextureFromSurface(SDL_Surface* Surface)
{
	if(Surface == NULL)
	{
		char message[1024] = "Given surface is NULL!";
		throw std::exception(message);
		return 0;
	}
	GLenum error = glGetError();
	m_width = Surface->w; m_height = Surface->h;
	SDL_Surface* ResizedSurface;
	if(!isPowerTwo(Surface->w) || !isPowerTwo(Surface->h))
	{
		m_powTwoW = NextPowTwo(m_width);
		m_powTwoH = NextPowTwo(m_height);
		Uint32 flags = Surface->flags;
		ResizedSurface = ResizeSurface(Surface, m_powTwoW, m_powTwoH);
		m_u = (float)m_width/(float)m_powTwoW;
		m_v = (float)m_height/(float)m_powTwoH;
		//SDL_FreeSurface(Surface);
	}
	else
	{
		m_u = 1.0f; m_v = 1.0f;
		m_powTwoW = m_width; m_powTwoH = m_height;
		ResizedSurface = Surface;
	}
	SDL_PixelFormat* format = ResizedSurface->format;
	GLuint flag;
	SDL_Surface* FinalSurface;
	if(format->BytesPerPixel == 4)
	{
		if(format->Rmask == 0xFF000000)
		{
			flag = GL_BGRA;
			FinalSurface = ResizedSurface;
		}
		else if(format->Rmask == 0x0000FF00)
		{
			flag = GL_RGBA;
			FinalSurface = ResizedSurface;
		}
		else if(format->Rmask == 0x00FF0000)
		{
			format->Rmask = 0xFF000000;
			format->Gmask = 0x00FF0000;
			format->Bmask = 0x0000FF00;
			format->Amask = 0x000000FF;
			FinalSurface = SDL_ConvertSurface(ResizedSurface, format, Surface->flags);
			SDL_FreeSurface(ResizedSurface);
			format = FinalSurface->format;
			flag = GL_BGRA;
		}
		else if(format->Rmask == 0x000000FF)
		{
			format->Bmask = 0xFF000000;
			format->Gmask = 0x00FF0000;
			format->Rmask = 0x0000FF00;
			format->Amask = 0x000000FF;
			FinalSurface = SDL_ConvertSurface(ResizedSurface, format, Surface->flags);
			SDL_FreeSurface(ResizedSurface);
			format = FinalSurface->format;
			flag = GL_RGBA;
		}
	}
	else if(format->BytesPerPixel == 3)
	{
		if(format->Rmask == 0xFF000000 || format->Rmask == 0x00FF0000)
		{
			flag = GL_RGB;
			FinalSurface = ResizedSurface;
		}
		else if(format->Rmask == 0x0000FF00)
		{
			flag = GL_BGR;
			FinalSurface = ResizedSurface;
		}
		else if(format->Rmask == 0x000000FF)
		{
			format->Rmask = 0xFF000000;
			format->Gmask = 0x00FF0000;
			format->Bmask = 0x0000FF00;
			FinalSurface = SDL_ConvertSurface(Surface, format, Surface->flags);
			SDL_FreeSurface(ResizedSurface);
			format = FinalSurface->format;
			flag = GL_RGB;
		}
	}
	else
	{
		SDL_FreeSurface(ResizedSurface);
		char message[1024] = "Given Surface is not truecolor.";
		throw std::exception(message);
		return false;
	}
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	if(!isTexture())
	{
		if(!exceptionError())
			return false;
		SDL_FreeSurface(FinalSurface);
		throw std::exception("Failed to generate texture name.");
		return false;
	}
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D(GL_TEXTURE_2D, 0, format->BytesPerPixel, m_powTwoW, m_powTwoH, 0, flag, GL_UNSIGNED_BYTE, FinalSurface->pixels);
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		throw std::exception(glErrorString(error).c_str());
		return false;
	}
	m_init = true;
	SDL_FreeSurface(FinalSurface);
	return true;
}
bool Texture::isInit()
{
	return m_init;
}

int	Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}

float Texture::getU()
{
	return m_u;
}

float Texture::getV()
{
	return m_v;
}

void Texture::Draw(float X, float Y, float R, float G, float B, float A, float scale, bool centered, float rotation)
{
	//m_drawInfo.push_back(DrawInfo(X,Y,m_width, m_height, R,G,B,A,centered,scale, scale, rotation));
	Draw(X, Y, R, G, B, A, scale, scale, centered, rotation);
}

void Texture::Draw(float X, float Y, float R, float G, float B, float A, float Xscale, float Yscale, bool centered, float rotation)
{
	m_drawInfo.push_back(DrawInfo(X,Y,m_width, m_height, R,G,B,A,centered, Xscale, Yscale, rotation));
	if(!m_inQueue)
	{
		m_inQueue = true;
		TextureMgr->AddToDrawQueue(this);
		addRef();
	}
}

std::list<DrawInfo> Texture::GetInstances()
{
	std::list<DrawInfo> ret(m_drawInfo);
	m_drawInfo.clear();
	return ret;
}

GLuint Texture::getTexture()
{
	return m_texture;
}

bool Texture::Release()
{
	if(--m_refCount > 0)
	{
		return true;
	}
	m_init = false;
	m_drawInfo.clear();
	m_width = m_height = m_powTwoW = m_powTwoH = 0;
	m_u = m_v = 0.0f;

	if(isTexture())
	{
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
		return true;
	}
	return true;
}
std::string Texture::GetFileName()
{
	return FileName;
}

void Texture::RemoveFromDrawQueue()
{
	m_inQueue = false;
	Release();
}
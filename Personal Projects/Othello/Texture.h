#pragma once

#include <sdl.h>
#include <sdl_opengl.h>
#include <gl/gl.h>
#include <sdl_image.h>
#include <string>
#include <list>
#include <cmath>
#include "vmmlib.hpp"
#include <SDL_gfxprimitives.h>
#include <SDL_gfxblitfunc.h>

typedef std::pair<float, float> point;

#define RATIO 30

struct DrawInfo
{
	point p1, p2, p3, p4;
	float r,g,b,a;

	DrawInfo() : r(0.0f),g(0.0f),b(0.0f),a(0.0f) {}
	DrawInfo(float X, float Y, int W, int H, float R, float G, float B, float A, bool centered, float Xscale, float Yscale, float rotate);
};



class Texture
{
	private:
		GLuint	m_texture;				// GL Texture name
		int		m_width,	m_height;	// Image width and height
		int		m_powTwoW,	m_powTwoH;	// Power-of-two width and height
		float	m_u,		m_v;		// Maximum U/V values in case the image is not a power of two.
		std::list<DrawInfo> m_drawInfo;	// List of information used for drawing instances of this texture.
		int		m_refCount;
		bool	m_init;
		bool	m_inQueue;
		std::string FileName;
	public:
		void addRef() { m_refCount++;}
		Texture() : m_texture(0), m_width(0), m_height(0), m_powTwoW(0), m_powTwoH(0),
					m_u(0.0f), m_v(0.0f), m_refCount(0), m_init(false), FileName(""), m_inQueue(false) {}
		GLboolean	isTexture();
		void	RemoveFromDrawQueue();
		bool	LoadTexture(std::string filename);
		bool	TextureFromSurface(SDL_Surface* surface);
		std::list<DrawInfo> GetInstances();
		int		getWidth();
		int		getHeight();
		float	getU();
		float	getV();
		GLuint	getTexture();
		void	Draw(float X, float Y, float R, float G, float B, float A, float scale = 1.0f, bool centered = true, float rotation = 0.0f );
		void	Draw(float X, float Y, float R, float G, float B, float A, float Xscale = 1.0f, float Yscale = 1.0f, bool centered = true, float rotation = 0.0f );
		bool	Release();
		bool	isInit();
		std::string GetFileName();
		~Texture() { Release(); }
};
#pragma once
#include <SDL.h>
#include <list>
#include "TextureManager.h"
#include "utility.h"
#include "Particle.h"
class ParticleEmitter
{
	protected:
		Texture* ParticleTexture;			// The particle texture. Loaded through the texture manager
		std::list<Particle*> Particles;		// The list of particles
		int MinParticles, MaxParticles;		// Minimum and maximum amount of particles.
		Pos2D MinSize, MaxSize;				// Minimum and maximum scale of the particles (both normally < 1, depending on texture size)
		int NumParticles;					// Number of living particles.
		int TimeLeft;						// Lifetime of the emitter.
		Pos2D Origin;
	public:
		virtual void Init() = 0;
		virtual void Update(Uint32 tickDelta) = 0;
		virtual void Destroy() = 0;
		void Draw();
		bool IsAlive();
};
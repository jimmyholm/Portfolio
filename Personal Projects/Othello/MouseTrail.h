#pragma once
#include "utility.h"
#include "InputHandler.h"
#include "ParticleEmitter.h"

class MouseTrail : public ParticleEmitter
{
	protected:
		Tint TintA, TintB;
		int MinLife, MaxLife;
	public:
		static MouseTrail* CreateEmitter(std::string TextureName, int minParticles, int maxParticles, Pos2D minSize, 
										 Pos2D maxSize, Tint tintA, Tint tintB, int minLife, int maxLife);
		virtual void Init();
		virtual void Update(Uint32 TickDelta);
		virtual void Destroy();
};
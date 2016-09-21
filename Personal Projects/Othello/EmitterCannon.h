#pragma once
#include "ParticleEmitter.h"

class EmitterCannon : public ParticleEmitter
{
	protected:
		EmitterCannon();
		Pos2D MinVelocity, MaxVelocity;
		float MinAngle, MaxAngle;
	public:
		static EmitterCannon* CreateEmitter(std::string TextureName, Pos2D origin, int minParticles, int maxParticles, 
								Pos2D minScale, Pos2D maxScale, Pos2D minVelocity, Pos2D maxVelocity,
								float minAngle, float maxAngle, int LifeTime);
		virtual void Init();
		virtual void Update(Uint32 TickDelta);
		virtual void Destroy();
};
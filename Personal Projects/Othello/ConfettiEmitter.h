#pragma once
#include "ParticleEmitter.h"

class ConfettiEmitter : public ParticleEmitter
{
	protected:
		Pos2D MinVelocity, MaxVelocity;
		Pos2D VelocityDecay;
		Pos2D Gravity;
		float MinAngularVel, MaxAngularVel;
		float AngularDampening;
	public:
		static ConfettiEmitter* CreateEmitter(std::string TextureName, Pos2D origin, int Particles, 
								Pos2D minScale, Pos2D maxScale, Pos2D minVelocity, Pos2D maxVelocity, Pos2D velDecay,
								Pos2D gravity, float minAngularVel, float maxAngularVel, 
								float angularDampening, int LifeTime);
		virtual void Init();
		virtual void Update(Uint32 TickDelta);
		virtual void Destroy();
};
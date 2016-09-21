#include "ConfettiEmitter.h"
#include "math.h"

ConfettiEmitter* ConfettiEmitter::CreateEmitter(std::string TextureName, Pos2D origin, int Particles, Pos2D minScale, 
												Pos2D maxScale, Pos2D minVelocity, Pos2D maxVelocity, 
												Pos2D velDecay, Pos2D gravity, float minAngularVel, 
												float maxAngularVel, float angularDampening, int LifeTime)
{
	ConfettiEmitter* ret = new ConfettiEmitter;
	ret->ParticleTexture = TextureMgr->getTexture(TextureName);
	if(ret->ParticleTexture == NULL)
	{
		delete ret;
		return 0;
	}
	ret->MinParticles = Particles;
	ret->MaxParticles = Particles;
	ret->MinSize	  = minScale;
	ret->MaxSize	  = maxScale;
	ret->MinVelocity  = minVelocity;
	ret->MaxVelocity  = maxVelocity;
	ret->Gravity	  = gravity;
	ret->VelocityDecay = velDecay;
	ret->MinAngularVel = minAngularVel;
	ret->MaxAngularVel = maxAngularVel;
	ret->AngularDampening = angularDampening;
	ret->TimeLeft	  = LifeTime;
	ret->Origin		  = origin;
	ret->MinAngularVel	  = minAngularVel;
	ret->MaxAngularVel	  = maxAngularVel;
	ret->NumParticles = 0;
	ret->Init();
	return ret;
}

void ConfettiEmitter::Init()
{
	while(NumParticles < MinParticles)
	{
		Pos2D Velocity = Pos2D(random(MinVelocity.x, MaxVelocity.x), random(MinVelocity.y, MaxVelocity.y));
		Velocity.x *= sin(Velocity.y);
		Velocity.y *= cos(Velocity.x);
		if(Velocity.y > 0)
			Velocity.y *= -1;
		Particles.push_back(new Particle(Pos2D(random(Origin.x-5, Origin.x+5), random(Origin.y-15, Origin.y)), Pos2D(random(MinSize.x, MaxSize.x), random(MinSize.y, MaxSize.y)),
										 Tint(random(0.5, 1.0f),random(0.5, 1.0f),random(0.5, 1.0f),random(0.75, 1.0f)),
										 Velocity,
										 VelocityDecay, Gravity, 0, random(MinAngularVel,MaxAngularVel), AngularDampening, (int)random((float)TimeLeft/2.0f,(float)TimeLeft)));
		NumParticles++;
	}
}

void ConfettiEmitter::Update(Uint32 TickDelta)
{
	std::list<Particle*>::iterator it;
	for(it = Particles.begin(); it != Particles.end();)
	{
		(*it)->Update(TickDelta);
		if((*it)->m_TimeLeft <= 0)
		{
			std::list<Particle*>::iterator dit = it;
			it++;
			Particles.erase(dit);
			NumParticles--;
		}
		else
			it++;
	}
	TimeLeft -= TickDelta;
}

void ConfettiEmitter::Destroy()
{
	//ParticleTexture->Release();
	Particles.clear();
}
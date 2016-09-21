#include "EmitterCannon.h"


EmitterCannon::EmitterCannon() : MinVelocity(Pos2D(0,0)), MaxVelocity(Pos2D(0,0)), MinAngle(0), MaxAngle(0)
{
}

EmitterCannon* EmitterCannon::CreateEmitter(std::string TextureName, Pos2D origin, 
											int minParticles, int maxParticles, Pos2D minScale, 
											Pos2D maxScale, Pos2D minVelocity, Pos2D maxVelocity, float minAngle,
											float maxAngle, int LifeTime)
{
	EmitterCannon* ret = new EmitterCannon;
	ret->ParticleTexture = TextureMgr->getTexture(TextureName);
	if(ret->ParticleTexture == NULL)
	{
		delete ret;
		return 0;
	}
	ret->MinParticles = minParticles;
	ret->MaxParticles = maxParticles;
	ret->MinSize	  = minScale;
	ret->MaxSize	  = maxScale;
	ret->MinVelocity  = minVelocity;
	ret->MaxVelocity  = maxVelocity;
	ret->TimeLeft	  = LifeTime;
	ret->Origin		  = origin;
	ret->MinAngle	  = minAngle;
	ret->MaxAngle	  = maxAngle;
	ret->NumParticles = 0;
	ret->Init();
	return ret;
}

void EmitterCannon::Init()
{
	/*while(NumParticles < MinParticles)
	{
		Particles.push_back(new Particle(Origin, Pos2D(random(MinSize.x, MaxSize.x), random(MinSize.y, MaxSize.y)),
										 Tint(random(0.5, 1.0f),random(0.5, 1.0f),random(0.5, 1.0f),random(0.75, 1.0f)),
										 Pos2D(random(MinVelocity.x, MaxVelocity.x), random(MinVelocity.y, MaxVelocity.y)),
										 Pos2D(), Pos2D(), 0, 0, 0, (int)random((float)TimeLeft/10.0f,(float)TimeLeft/5.0f)));
		NumParticles++;
	}*/
}

void EmitterCannon::Update(Uint32 TickDelta)
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
	if(NumParticles < MinParticles ||NumParticles < MaxParticles && TimeLeft > 0)
	{
		Particles.push_back(new Particle(Pos2D(random(Origin.x-4, Origin.x+4), random(Origin.y-4, Origin.y+4)), Pos2D(random(MinSize.x, MaxSize.x), random(MinSize.y, MaxSize.y)),
										 Tint(random(0.5, 1.0f),random(0.5, 1.0f),random(0.5, 1.0f),random(0.75, 1.0f)),
										 Pos2D(random(MinVelocity.x, MaxVelocity.x), random(MinVelocity.y, MaxVelocity.y)),
										 Pos2D(), Pos2D(), 0, 0, 0, (int)random((float)TimeLeft/10.0f,(float)TimeLeft/5.0f)));
		NumParticles++;
	}
	TimeLeft -= TickDelta;
}

void EmitterCannon::Destroy()
{
	ParticleTexture->Release();
	Particles.clear();
}
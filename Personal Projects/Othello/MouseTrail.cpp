#include "MouseTrail.h"


MouseTrail* MouseTrail::CreateEmitter(std::string TextureName, int minParticles, int maxParticles, Pos2D minSize, 
									  Pos2D maxSize, Tint tintA, Tint tintB, int minLife, int maxLife)
{
	MouseTrail* ret = new MouseTrail;
	ret->ParticleTexture = TextureMgr->getTexture(TextureName);
	if(ret->ParticleTexture == NULL)
	{
		delete ret;
		return 0;
	}
	ret->MinParticles = minParticles;
	ret->MaxParticles = maxParticles;
	ret->MinSize	  = minSize;
	ret->MaxSize	  = maxSize;
	ret->MinLife	  = minLife;
	ret->MaxLife	  = maxLife;
	ret->TimeLeft	  = 1;
	ret->Origin		  = InputHandler::GetInstance()->GetMousePosition();
	ret->NumParticles = 0;
	ret->TintA		  = tintA;
	ret->TintB		  = tintB;
	ret->Init();
	return ret;
}

void MouseTrail::Init()
{
}

void MouseTrail::Update(Uint32 TickDelta)
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
		Tint t = Tint(random(TintA.R, TintB.R), random(TintA.G, TintB.G), 
					  random(TintA.B, TintB.B), random(TintA.A, TintB.A));
		Particles.push_back(new Particle(Pos2D(random(Origin.x-6, Origin.x+6),random(Origin.y-6, Origin.y+6)), Pos2D(random(MinSize.x, MaxSize.x), random(MinSize.y, MaxSize.y)),
										 t, Pos2D(random(-15.0f,-25.0f), random(-5.0f, -15.0f)),
										 Pos2D(), Pos2D(), 0, 0, 0, random(MinLife, MaxLife)));
		NumParticles++;
	}
	Origin = InputHandler::GetInstance()->GetMousePosition();
}

void MouseTrail::Destroy()
{
	ParticleTexture->Release();
	Particles.clear();
}
#include "ParticleEngine.h"

ParticleEngine* ParticleEngine::Instance = 0;

ParticleEngine* ParticleEngine::GetInstance()
{
	if(Instance == 0)
		Instance = new ParticleEngine();
	return Instance;
}

void ParticleEngine::UpdateAll(Uint32 TickDelta)
{
	std::list<ParticleEmitter*>::iterator it;
	std::list<ParticleEmitter*>::iterator dit = Emitters.end();
	for(it = Emitters.begin(); it != Emitters.end(); it++)
	{
		if(dit != Emitters.end())
		{
			(*dit)->Destroy();
			Emitters.erase(dit);
			dit = Emitters.end();
		}
		(*it)->Update(TickDelta);
		if(!(*it)->IsAlive())
		{
			dit = it;
		}
	}
	if(dit != Emitters.end())
	{
		(*dit)->Destroy();
		Emitters.erase(dit);
		dit = Emitters.end();
	}
}

void ParticleEngine::Draw()
{
	std::list<ParticleEmitter*>::iterator it;
	for(it = Emitters.begin(); it != Emitters.end(); it++)
	{
		(*it)->Draw();
	}
}

void ParticleEngine::DestroyEmitters()
{
	std::list<ParticleEmitter*>::iterator it;
	for(it = Emitters.begin(); it != Emitters.end(); it++)
	{
		(*it)->Destroy();
	}
	Emitters.clear();
}

void ParticleEngine::Destroy()
{
	DestroyEmitters();
	delete Instance;
}

void ParticleEngine::AddEmitter(ParticleEmitter* emitter)
{
	Emitters.push_back(emitter);
}
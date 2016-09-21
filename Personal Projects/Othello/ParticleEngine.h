#pragma once
#include "utility.h"
#include "ParticleEmitter.h"
#include "EmitterTypes.h"
class ParticleEngine
{
	private:
		std::list<ParticleEmitter*> Emitters;
		static ParticleEngine* Instance;

	public:
		static ParticleEngine* GetInstance();

		void AddEmitter(ParticleEmitter* emitter);
		void UpdateAll(Uint32 TickDelta);
		void Draw();
		void DestroyEmitters();
		void Destroy();
};
#include "ParticleEmitter.h"

void ParticleEmitter::Draw()
{
	std::list<Particle*>::iterator it;
	for(it = Particles.begin(); it != Particles.end(); it++)
	{
		Particle* p = (*it);
		ParticleTexture->Draw(p->m_Position.x, p->m_Position.y, p->m_Tint.R, p->m_Tint.G, p->m_Tint.B, p->m_Tint.A,
							  p->m_Scale.x, p->m_Scale.y, true, p->m_Angle);
	}
}

bool ParticleEmitter::IsAlive()
{
	return TimeLeft > 0 || NumParticles > 0;
}
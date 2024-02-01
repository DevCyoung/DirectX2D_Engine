# include "pch.h"
#include <Engine/ParticleSystem.h>
class RenderComponent;
void RenderComponentUI(RenderComponent* component);


void ParticleSystemUI(ParticleSystem* component)
{
	RenderComponentUI(component);

}

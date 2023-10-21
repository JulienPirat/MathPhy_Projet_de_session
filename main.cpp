#include "TEST2/GraphicEngine.h"
#include "TEST2/ImGuiEngine.h"
#include <PhysicEngine.h>
#include <world.h>

// Main code
int main(int, char**)
{
    World w = World();

	#pragma region InitParticles
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		Particle* p = new Particle(
			Vector3D(0, 0, 0),
			Vector3D(
				((double)(rand() % 2) / (double)RAND_MAX) - 1,
				((double)(rand() % 2) / (double)RAND_MAX) - 1,
				((double)(rand() % 2) / (double)RAND_MAX) - 1
			),
			Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)),
			((double)rand() / (double)RAND_MAX),
			((double)rand() / (double)RAND_MAX),
			Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX))
		);

		std::cout << "Particle " << i << " : "
			<< p->getPosition().x << " " << p->getPosition().y << " " << p->getPosition().z << std::endl
			<< p->getVelocity().x << " " << p->getVelocity().y << " " << p->getVelocity().z << std::endl
			<< p->getAcceleration().x << " " << p->getAcceleration().y << " " << p->getAcceleration().z << std::endl;

		w.AddParticle(p);
	}
	#pragma endregion

    auto exitCode = w.Run();

    return exitCode;
}

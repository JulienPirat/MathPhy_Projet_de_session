#include "TEST2/GraphicEngine.h"
#include "TEST2/ImGuiEngine.h"
#include <PhysicEngine.h>
#include <world.h>


Particle randomGenerateParticle() {
	return Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D( //Velocité
			((double)(rand() % 2) / (double)RAND_MAX) - 1,
			((double)(rand() % 2) / (double)RAND_MAX) - 1,
			((double)(rand() % 2) / (double)RAND_MAX) - 1
		),
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Accélération
		((double)rand() / (double)RAND_MAX), //Damping
		((double)rand() / (double)RAND_MAX), //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
}

// Main code
int main(int, char**)
{
    World w = World();

	#pragma region InitParticles
	srand(time(NULL));

	/*
	for (int i = 0; i < 10; i++)
	{
		Particle p = randomGenerateParticle();

		std::cout << "Particle " << i << " : "
			<< p.getPosition().x << " " << p.getPosition().y << " " << p.getPosition().z << std::endl
			<< p.getVelocity().x << " " << p.getVelocity().y << " " << p.getVelocity().z << std::endl
			<< p.getAcceleration().x << " " << p.getAcceleration().y << " " << p.getAcceleration().z << std::endl;

		w.AddParticle(&p);
	}
	*/
	/*
	//Créer trois particules
	Particle p1 = Particle(
		Vector3D(10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p1);

	Particle p2 = Particle(
		Vector3D(-10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p2);

	Particle p3 = Particle(
		Vector3D(5, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		1, //Damping
		0.2, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p3);
	*/
	
	//Créer deux particules Collision
	/*
	Particle p1 = Particle(
		Vector3D(100, 0, 50), //Position
		Vector3D(-10, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p1);

	Particle p2 = Particle(
		Vector3D(-100, 0, 50), //Position
		Vector3D(10, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p2);
	*/

	//Ground Bloqué
	/*
	Particle p1 = Particle(
		Vector3D(0, 100, 0), //Position
		Vector3D(0, -10, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p1);

	Particle p2 = Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p2);
	*/

	/*
	Particle p1 = Particle(
		Vector3D(0, 100, 0), //Position
		Vector3D(0, -15, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p1);

	Particle p2 = Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	w.AddParticle(&p2);
	*/

	#pragma endregion

    auto exitCode = w.Run();

    return exitCode;
}


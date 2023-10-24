#pragma once
#include <GraphicEngine.h>
#include <PhysicEngine.h>
#include <ImGuiEngine.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>

class World
{
public:

	///Methodes

	//Generation de tests
	void AddParticle(Particle* particle);
	void GenBasicCollision();
	void GenBasicParticule(float x, float y, float z, float vx, float vy, float vz, float ax, float ay, float az);
	void GenContactResting();
	void GenWallCollision();

	//Ajoute des forceGenerator au partiule.
	void PutGravityForceGenerator();

	//Lancement de la simulation
	int Run();

	// M�thode statique pour obtenir l'instance unique du singleton.
	static World& GetInstance() {
		static World instance; // Cr�e une instance unique lors du premier appel.
		return instance;
	}

private :

	///Contructeur / Destructeur / Op�rateurs
	World() {}
	~World() {}

	World(const World&) = delete;
	World& operator=(const World&) = delete;

	///Attributs

	GraphicEngine graphics;
	PhysicEngine physics = PhysicEngine(particles);
	ImGuiEngine imGui;

	ParticleContactResolver contactResolver = ParticleContactResolver(10);

	std::vector<Particle*> particles = std::vector<Particle*>();

	///Methodes

	int Init();
	void Update(float deltaTime);
	void Shutdown();
};


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
	void DeleteAllParticle();
	void GenBasicCollision();
	void GenBasicParticule(float x, float y, float z, float vx, float vy, float vz, float ax, float ay, float az);
	void GenContactResting();
	void GenWallCollision();

	void AddRigidBody(RigidBody* rb);
	void DeleteAllRigidBody();

	//Ajoute des forceGenerator aux partiules.
	void PutGravityForceGenerator();


	//Ajoute des forces de frottement aux particules.
	void PutDragForceGenerator();

	//Ajoute une force de ressort ancré a l'origine aux particles
	void PutAnchoredSpringForceGenerator();

	//Ajoute une force de flottement
	void PutBuoyancyForceGenerator();

	//Ajouter un exemple de cable
	void AddCableExample();

	//Ajouter un exemple de rod
	void AddRodExample();

	//Ajouter un exemple de RigidBody
	void AddRigidBody();

	//Lancement de la simulation
	int Run();

	// Méthode statique pour obtenir l'instance unique du singleton.
	static World& GetInstance() {
		static World instance; // Crée une instance unique lors du premier appel.
		return instance;
	}

private :

	///Contructeur / Destructeur / Opérateurs
	World() {}
	~World() {}

	World(const World&) = delete;
	World& operator=(const World&) = delete;

	///Attributs

	GraphicEngine graphics;
	PhysicEngine physics = PhysicEngine(particles,rigidBodies);
	ImGuiEngine imGui;

	ParticleContactResolver contactResolver = ParticleContactResolver(10);

	std::vector<Particle*> particles = std::vector<Particle*>();

	std::vector<RigidBody*> rigidBodies = std::vector<RigidBody*>();

	///Methodes

	int Init();
	void Update(float deltaTime);
	void Shutdown();
};


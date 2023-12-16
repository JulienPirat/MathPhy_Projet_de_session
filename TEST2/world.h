#pragma once
#include <GraphicEngine.h>
#include <PhysicEngine.h>
#include <ImGuiEngine.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>
#include <Box.h>
#include <Plane.h>
#include <Sphere.h>

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

	void ContactBoxBox();

	//Ajoute des rigidbody et test les collisions Sphere a Box
	void ContactSphereBox();

	void ContactSphereSphere();

	void GenerateContactSphereBox();

	//Ajoute des forceGenerator aux partiules.
	void PutGravityForceGenerator();

	//Ajoute des forces de frottement aux particules.
	void PutDragForceGenerator();

	//Ajoute une force de ressort ancr� a l'origine aux particles
	void PutAnchoredSpringForceGenerator();

	//Ajoute une force de flottement
	void PutBuoyancyForceGenerator();

	//Ajouter un exemple de cable
	void AddCableExample();

	//Ajouter un exemple de rod
	void AddRodExample();

	void AddDemoKDTree();

	//Ajouter un exemple de RigidBody
	void AddRigidBody();

	//Ajouter un exemple de AnchordSpring a 2 RigidBody
	void AddAnchoredSpringForTwoRigidBody();

	//Ajouter un exemple de AnchordSpring a un RigidBody
	void AddAnchoredSpringForRigidBody();

	//G�n�ration de contact entre Box et Box
	void GenerateContactBoxBox();

	//G�n�ration de contact entre Box et Sphere
	void GenerateContactBoxSphere();

	//G�n�ration de contact entre Sphere et Sphere
	void GenerateContactSphereSphere();

	//Lancement de la simulation
	int Run();

	// M�thode statique pour obtenir l'instance unique du singleton.
	static World& GetInstance() {
		static World instance; // Cr�e une instance unique lors du premier appel.
		return instance;
	}

	//Sharable

	int GetNBCollisionKDTree();

private :

	///Contructeur / Destructeur / Op�rateurs
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

	std::vector<RigidBody*> rigidBodiesTEST = std::vector<RigidBody*>();

	///Methodes

	int Init();
	void Update(float deltaTime);
	void Shutdown();

};


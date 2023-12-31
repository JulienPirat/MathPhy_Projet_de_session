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


	//Generation Contact RB

	void ContactBoxBox(Vector3D rot, Vector3D rot2);

	void ContactBoxPlane();

	void ContactSpherePlane();

	void ContactSphereBox(Vector3D SPos, Vector3D SVel, Vector3D BPos, Vector3D BVel);

	void ContactSphereSphere();

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

	//Lancement de la simulation
	int Run();

	// M�thode statique pour obtenir l'instance unique du singleton.
	static World& GetInstance() {
		static World instance; // Cr�e une instance unique lors du premier appel.
		return instance;
	}

	//Sharable

	int GetNBCollisionKDTree();
	int GetNBRB();

	void ToggleRunningPhysics();
	bool GetRunningPhysics();

	void EnableCollisionControl();
	void DisableCollisionControl();
	bool GetCollisionControl();

	std::string GetContactData();

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
	void Update(double deltaTime);
	void Shutdown();

};


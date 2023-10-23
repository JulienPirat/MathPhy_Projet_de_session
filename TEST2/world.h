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
	void AddParticle(Particle* particle);
	void GenBasicCollision();
	void GenBasicParticule(float x, float y, float z, float vx, float vy, float vz, float ax, float ay, float az);
	void GenContactResting();
	void GenWallCollision();
	int Run();

	// M�thode statique pour obtenir l'instance unique du singleton.
	static World& GetInstance() {
		static World instance; // Cr�e une instance unique lors du premier appel.
		return instance;
	}

private :

	// Le constructeur est rendu priv� pour emp�cher les cr�ations d'instances en dehors de la classe.
	World() {
		// Initialisation du singleton, si n�cessaire.
	}

	// Le destructeur peut �tre ajout� pour effectuer le nettoyage si n�cessaire.
	~World() {
		// Nettoyage, si n�cessaire.
	}

	GraphicEngine graphics;
	PhysicEngine physics = PhysicEngine(particles);
	ImGuiEngine imGui;

	ParticleContactResolver contactResolver = ParticleContactResolver(10);

	std::vector<Particle*> particles = std::vector<Particle*>();

	int Init();
	void Update(float deltaTime);
	void Shutdown();

	World(const World&) = delete;
	World& operator=(const World&) = delete;
};


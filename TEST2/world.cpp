#include "world.h"
#include <GLFW/glfw3.h>

void World::AddParticle(Particle* particle)
{
	this->particles.push_back(particle);
}

void World::DeleteAllParticle() {
	physics.ClearParticles();
}

void World::AddRigidBody(RigidBody* rb)
{
	this->rigidBodies.push_back(rb);
}

void World::DeleteAllRigidBody() {
	physics.ClearRigidBodies();
}

void World::GenBasicCollision() {

	//Cr�er deux particules
	Particle* p1 = new Particle(
		Vector3D(10, 0, 0), //Position
		Vector3D(-1, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(-10, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p2);
}

void  World::GenBasicParticule(float x, float y, float z, float vx, float vy, float vz, float ax, float ay, float az) {

	Particle* p3 = new Particle(
		Vector3D(x, y, z), //Position
		Vector3D(vx, vy, vz),//Velocit�
		Vector3D(ax, ay, az), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p3);

}

void World::GenContactResting() {
	Particle* p1 = new Particle(
		Vector3D(0, 100, 0), //Position
		Vector3D(0, -10, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p2);
}

void World::GenWallCollision() {
	//Cr�er trois particules
	Particle* p1 = new Particle(
		Vector3D(10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(-10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		-1000, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p2);

	Particle* p3 = new Particle(
		Vector3D(5, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		1, //Damping
		0.2, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p3);
}

void World::PutGravityForceGenerator()
{
	physics.putGravityToParticle();
}

void World::PutDragForceGenerator()
{
	physics.putDragToParticle();
}

void World::PutAnchoredSpringForceGenerator()
{
	physics.putAnchoredSpringToParticle();
}

void World::PutBuoyancyForceGenerator()
{
	physics.putBuoyancyToParticle();
}

void World::AddCableExample()
{
	//Cr�er trois particules
	Particle* p1spring = new Particle(
		Vector3D(3, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p1spring);

	Particle* p2spring = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(-10, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p2spring);

	physics.AddCableExample(p1spring, p2spring);
}

void World::AddRodExample()
{
	//Cr�er trois particules
	Particle* p1spring = new Particle(
		Vector3D(3, 0, 0), //Position
		Vector3D(-1, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p1spring);

	Particle* p2spring = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping
		1, //Inverse Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)) //Couleur
	);
	AddParticle(p2spring);

	physics.AddRodExample(p1spring, p2spring);
}

void World::AddDemoKDTree()
{
	Box* RB_1 = new Box(
		Vector3D(10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_1);

	Box* RB_3 = new Box(
		Vector3D(12, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_3);

	Box* RB_2 = new Box(
		Vector3D(-10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 2, 1)
	);
	AddRigidBody(RB_2);

	Box* RB_4 = new Box(
		Vector3D(-12, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 2, 1)
	);
	AddRigidBody(RB_4);
}

void World::AddRigidBody()
{
	physics.putGravityToRigidBody();
}

void World::AddAnchoredSpringForTwoRigidBody()
{
	Box* RB_1 = new Box(
		Vector3D(-20, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_1);

	Box* RB_2 = new Box(
		Vector3D(20, 20, 0), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1,2,1)
	);
	AddRigidBody(RB_2);

	physics.putSpringForTwoRigidBody(RB_1, RB_2);
}

void World::AddAnchoredSpringForRigidBody()
{
	Box* RB_1 = new Box(
		Vector3D(3, 3, 3), //Position
		Vector3D(0, 0, 0),//Velocit�
		Vector3D(0, 0, 0), //Acc�l�ration
		0.999f, //Damping Lin�aire
		0.999f, //Damping Angulaire
		1, // Masse
		Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)), //Couleur
		Vector3D(1, 1, 1)
	);
	AddRigidBody(RB_1);

	Vector3D WorldAnchorPoint = Vector3D(3, 5, 4);

	physics.putSpringForRigidBody(RB_1,WorldAnchorPoint);
}

int World::Run()
{
	auto res = this->Init();

	if (res == 1) return res;

	float lastTime = glfwGetTime();
	float currentTime = 0;
	float deltaT = 0;

    while (!graphics.ShouldClose())
    {
		currentTime = glfwGetTime();
		deltaT = currentTime - lastTime;
		lastTime = currentTime;

		this->Update(deltaT);
    }

	this->Shutdown();

	return 0;
}

int World::Init()
{
	graphics = GraphicEngine();
	GLFWwindow* window = graphics.Init();

	if (window == nullptr)
		return 1;

	imGui = ImGuiEngine();
	imGui.Init(window);

	physics.Init();

	imGui.SetVisible(true);

	return 0;
}

void World::Update(float deltaTime)
{
	physics.Update(deltaTime);

	graphics.Update();

	imGui.Update();

	graphics.Render(particles, rigidBodies);

	imGui.Render();

	graphics.SwapBuffers();
}

void World::Shutdown()
{
    imGui.Shutdown();
    graphics.Shutdown();
}

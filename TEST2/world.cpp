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

void World::ContactBoxBox(Vector3D rot, Vector3D rot2)
{
	Box* RB_1 = new Box(
		Vector3D(1, 0, 0), //Position
		Vector3D(-0.5, 0, 0),//Velocité
		rot, //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		10, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 1, 1)
	);
	AddRigidBody(RB_1);

	Box* RB_2 = new Box(
		Vector3D(-1, 0, 0), //Position
		Vector3D(0.5, 0, 0),//Velocité
		rot2, //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		10, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 1, 1)
	);
	AddRigidBody(RB_2);
}

void World::ContactBoxPlane()
{
	Box* RB_1 = new Box(
		Vector3D(0, 2, 0), //Position
		Vector3D(0, -1, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 1, 1)
	);
	AddRigidBody(RB_1);

	Plane* RB_2 = new Plane(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		1,
		1
	);
	AddRigidBody(RB_2);
}

void World::ContactSpherePlane()
{
	Sphere* RB_1 = new Sphere(
		Vector3D(0, 2, 0), //Position
		Vector3D(0, -1, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		1
	);
	AddRigidBody(RB_1);

	Plane* RB_2 = new Plane(
		Vector3D(0, 0, 2), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		1,
		1
	);
	AddRigidBody(RB_2);
}

void World::ContactSphereBox(Vector3D SPos, Vector3D SVel, Vector3D BPos, Vector3D BVel)
{
	Sphere* RB_1 = new Sphere(
		SPos, //Position
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		.5f //Rayon
	);
	AddRigidBody(RB_1);
	RB_1->AddForce(SVel);

	Box* RB_2 = new Box(
		BPos, //Position
		Vector3D(0, 0, 0),
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 1, 1)
	);
	AddRigidBody(RB_2);
	RB_2->AddForce(BVel);
}

void World::ContactSphereSphere()
{
	Sphere* RB_1 = new Sphere(
		Vector3D(2, 0, 0), //Position
		Vector3D(-1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		.5f //Rayon
	);
	AddRigidBody(RB_1);

	Sphere* RB_2 = new Sphere(
		Vector3D(-2, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		2, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		.5f
	);
	AddRigidBody(RB_2);
}

void World::GenBasicCollision() {

	//Créer deux particules
	Particle* p1 = new Particle(
		Vector3D(10, 0, 0), //Position
		Vector3D(-1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(-10, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p2);
}

void  World::GenBasicParticule(float x, float y, float z, float vx, float vy, float vz, float ax, float ay, float az) {

	Particle* p3 = new Particle(
		Vector3D(x, y, z), //Position
		Vector3D(vx, vy, vz),//Velocité
		Vector3D(ax, ay, az), //Rotation
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p3);

}

void World::GenContactResting() {
	Particle* p1 = new Particle(
		Vector3D(0, 100, 0), //Position
		Vector3D(0, -10, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		-1000, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p2);
}

void World::GenWallCollision() {
	//Créer trois particules
	Particle* p1 = new Particle(
		Vector3D(10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		-1000, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p1);

	Particle* p2 = new Particle(
		Vector3D(-10, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		0.999f, //Damping
		-1000, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p2);

	Particle* p3 = new Particle(
		Vector3D(5, 0, 0), //Position
		Vector3D(1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Rotation
		1, //Damping
		0.2, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
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
	//Créer trois particules
	Particle* p1spring = new Particle(
		Vector3D(3, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p1spring);

	Particle* p2spring = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(-10, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p2spring);

	physics.AddCableExample(p1spring, p2spring);
}

void World::AddRodExample()
{
	//Créer trois particules
	Particle* p1spring = new Particle(
		Vector3D(3, 0, 0), //Position
		Vector3D(-1, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p1spring);

	Particle* p2spring = new Particle(
		Vector3D(0, 0, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping
		1, //Inverse Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)) //Couleur
	);
	AddParticle(p2spring);

	physics.AddRodExample(p1spring, p2spring);
}

void World::AddDemoKDTree()
{
	Box* RB_1 = new Box(
		Vector3D(11, 11, 11), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_1);

	Box* RB_3 = new Box(
		Vector3D(10, 10, 10), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_3);

	Box* RB_2 = new Box(
		Vector3D(-10, -10, -10), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 2, 1)
	);
	AddRigidBody(RB_2);

	Box* RB_4 = new Box(
		Vector3D(-11, -11, -11), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
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
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1, 2, 2)
	);
	AddRigidBody(RB_1);

	Box* RB_2 = new Box(
		Vector3D(20, 20, 0), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
		Vector3D(1,2,1)
	);
	AddRigidBody(RB_2);

	physics.putSpringForTwoRigidBody(RB_1, RB_2);
}

void World::AddAnchoredSpringForRigidBody()
{
	Box* RB_1 = new Box(
		Vector3D(3, 3, 3), //Position
		Vector3D(0, 0, 0),//Velocité
		Vector3D(0, 0, 0), //Accélération
		0.999f, //Damping Linéaire
		0.999f, //Damping Angulaire
		1, // Masse
		Color(((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX), ((float)rand() / (float)RAND_MAX)), //Couleur
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

	double lastTime = glfwGetTime();
	double currentTime = 0;
	double deltaT = 0;

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

void World::Update(double deltaTime)
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

int World::GetNBCollisionKDTree()
{
	return physics.NBCollision;
}

int World::GetNBRB()
{
	return physics.GetNBRB();
}

void World::ToggleRunningPhysics() {
	physics.isRunning = !physics.isRunning;
}

bool World::GetRunningPhysics()
{
	return physics.isRunning;
}

void World::EnableCollisionControl()
{
	physics.isControlledColData = true;
}

void World::DisableCollisionControl()
{
	physics.isControlledColData = false;
}

bool World::GetCollisionControl()
{
	return physics.isControlledColData;
}

std::string World::GetContactData() {

	if (physics.ControlledContact == nullptr) {
		return "NONE";
	}

	std::string title = "Contact : ";
	std::string brkline = "\n";
	std::string contactN = "Contact normal : " + physics.ControlledContact->contactNormal.ToStr();
	std::string contactP = "Contact point : " + physics.ControlledContact->contactPoint.ToStr();
	std::string contactFriction = "Friction : " + std::to_string(physics.ControlledContact->friction);
	std::string contactPenetration = "Penetration : " + std::to_string(physics.ControlledContact->penetration);
	std::string contactRestitution = "Restitution : " + std::to_string(physics.ControlledContact->restitution);
	std::string RB1P = "RB1 Position : " + physics.ControlledContact->RigidBodies[0]->position.ToStr();
	std::string RB1S = "RB1 Shape : " + std::to_string(physics.ControlledContact->RigidBodies[0]->shape);
	std::string RB2P = "RB2 Position : " + physics.ControlledContact->RigidBodies[1]->position.ToStr();
	std::string RB2S = "RB2 Shape : " + std::to_string(physics.ControlledContact->RigidBodies[1]->shape);

	return title + brkline + 
		brkline +
		contactN + brkline + 
		contactP + brkline + 
		brkline +
		contactFriction + brkline + 
		contactPenetration + brkline + 
		contactRestitution + brkline + 
		brkline +
		RB1S + brkline + 
		RB1P + brkline + 
		RB2S + brkline + 
		RB2P + brkline;
}

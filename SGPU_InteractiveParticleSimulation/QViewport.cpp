#include "QViewport.h"
#include <Mesh.h>
#include <GeometryShader.h>

const static float RAY_EXT = 20.0f;
const static float POINT_EXT = 6.0f;

QViewport::QViewport(QWidget* parent) : QGLWidget(parent) {
    this->setMouseTracking(true);
    this->grid = std::make_shared<Grid>();

    //------------------------------------------------------------------------------
    // Set the timer to call the onTimeout function at 60[fps]
    //------------------------------------------------------------------------------
    this->timer = new QTimer(this);
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    this->timer->setInterval(16);
    this->timer->start();

    this->camera = std::make_shared<MouseCameraf>();
    this->particleSystem_1 = std::make_shared<ParticleSystem>();
	this->particleSystem_2 = std::make_shared<ParticleSystem>();
	this->particleSystem_3 = std::make_shared<ParticleSystem>();

    //------------------------------------------------------------------------------
    // The simulation time-step matches the timer update specified in seconds.
    //------------------------------------------------------------------------------
    this->timeStep = 0.01667f;

    this->spawnParticles = false;
    this->particleSize = 0.5f;
}

QViewport::~QViewport() {}

void GetModelViewMatrix(std::shared_ptr<MouseCameraf>& camera, double* m) {
    float modelViewMatrix[16];
    camera->getViewMatrix().toRawMatrix(modelViewMatrix, true);
    for ( unsigned int i = 0; i < 16; i++ ) m[i] = static_cast<double>(modelViewMatrix[i]);
}

void GetProjectionMatrix(std::shared_ptr<MouseCameraf>& camera, double* m) {
    float projectionMatrix[16];
    camera->getProjectionMatrix().toRawMatrix(projectionMatrix, true);
    for ( unsigned int i = 0; i < 16; i++ ) m[i] = static_cast<double>(projectionMatrix[i]);
}

void QViewport::initializeGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glPointSize(10.0f);

    glewInit();
    
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->grid->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
    this->grid->construct(Color3f(0.4f, 0.4f, 0.4f), Color3f(0.25f, 0.25f, 0.25f), -16.0f, 16.0f, 0.4f, 8);

    this->camera->setPosition(10.0f, 0.0f, 1.570f * 0.7f);
    this->camera->setLookAt(Vector3f(0.0f, 1.0f, 0.0f));

    this->particleSystem_1->loadShader("shaders/vertexShader.vert", "shaders/geometryShader.geom", "shaders/fragmentShader.frag");
    this->particleSystem_1->getShader()->loadDiffuseTexture("textures/particle2.png");
    this->particleSystem_1->setMaxParticleCount(1000);
	this->particleSystem_2->loadShader("shaders/vertexShader.vert", "shaders/geometryShader.geom", "shaders/fragmentShader.frag");
	this->particleSystem_2->getShader()->loadDiffuseTexture("textures/particle2.png");
	this->particleSystem_2->setMaxParticleCount(1000);
	this->particleSystem_3->loadShader("shaders/vertexShader.vert", "shaders/geometryShader.geom", "shaders/fragmentShader.frag");
	this->particleSystem_3->getShader()->loadDiffuseTexture("textures/particle2.png");
	this->particleSystem_3->setMaxParticleCount(1000);

	this->mesh_car = std::make_shared<Mesh>();
	this->mesh_car->load("models/police_car.obj");
	this->mesh_car->loadShader("shaders/PhongShading.vert", "shaders/PhongShading.frag");
}

void QViewport::onTimeout() {
    //------------------------------------------------------------------------------
    // Update the particle simulation to provide the new spawnPoint and 
    // spawnDirection.
    //------------------------------------------------------------------------------
	this->particleSystem_1->update(this->spawnParticles, Vector3f(0.0f, 1.0f, 100.0f), this->timeStep, Vector3f(0.0f, 35.0f, 0.0f), Vector3f(0.0f, -70.0f, 0.0f), Vector3f(0.0f, -200.0f, 0.0f), Vector3f(0.0f, 20.0f, 0.0f));
	this->particleSystem_2->update(this->spawnParticles, Vector3f(0.0f, 1.5f, 100.0f), this->timeStep, Vector3f(0.0f, 30.0f, 0.0f), Vector3f(0.0f, -65.0f, 0.0f), Vector3f(0.0f, -175.0f, 0.0f), Vector3f(0.0f, 18.5f, 0.0f));
	this->particleSystem_3->update(this->spawnParticles, Vector3f(0.0f, 2.0f, 100.0f), this->timeStep, Vector3f(0.0f, 25.0f, 0.0f), Vector3f(0.0f, -60.0f, 0.0f), Vector3f(0.0f, -150.0f, 0.0f), Vector3f(0.0f, 17.0f, 0.0f));


    //------------------------------------------------------------------------------
    // Get the model view and projection matrices from the camera. Sine the
    // gluUnProject function requires double arrays, the cameras float arrays
    // are stored within a double array.
    //------------------------------------------------------------------------------
    double modelViewMatrix[16];
    double projectionMatrix[16];
    GetModelViewMatrix(camera, modelViewMatrix);
    GetProjectionMatrix(camera, projectionMatrix);
    double pointX, pointY, pointZ;

    //------------------------------------------------------------------------------
    // Get the size of the current OpenGL viewport. This is required for the
    // calculations within the gluUnProject function.
    //
    // viewport[0] = x
    // viewport[1] = y
    // viewport[2] = width
    // viewport[3] = height
    //------------------------------------------------------------------------------
    int viewport[4];
    std::memset(viewport, 0, sizeof(viewport));
    viewport[2] = this->width();
    viewport[3] = this->height();
    
    //------------------------------------------------------------------------------
    // Unproject the 2D mouse coordinate (flipped y) to a 3D point in the global
    // coordinate space. The 3D point is stored in pointX, pointY, pointZ.
    //------------------------------------------------------------------------------
    gluUnProject(this->mouseX, viewport[3] - this->mouseY, 0.1f, modelViewMatrix, projectionMatrix, viewport, &pointX, &pointY, &pointZ);
    
    this->updateGL();
}

void QViewport::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Matrix4f transform = Matrix4f::Identity();
    Matrix4f view = this->camera->getViewMatrix();
    Matrix4f modelViewMatrix = transform * this->camera->getViewMatrix();
    Matrix3f normalMatrix = Matrix4f::NormalMatrix(modelViewMatrix);
    Matrix4f projectionMatrix = this->camera->getProjectionMatrix();

    //------------------------------------------------------------------------------
    // Render the grid on the ground using the grid shader.
    //------------------------------------------------------------------------------

    this->grid->beginRender();
        this->grid->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);
        this->grid->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
    this->grid->endRender();
    
    //------------------------------------------------------------------------------
    // Render the particles.
    //------------------------------------------------------------------------------

	Matrix4f projectionMatrix_car = this->camera->getProjectionMatrix();
	Matrix4f modelViewMatrix_car = this->camera->getViewMatrix();
	Matrix4f normalMatrix_car = Matrix4f::Transpose(modelViewMatrix_car.toInverse());

	glEnable(GL_DEPTH_TEST);
	this->mesh_car->beginRender();
		this->mesh_car->getShader()->uniformMatrix("projectionMatrix", projectionMatrix_car);
		this->mesh_car->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix_car);
		this->mesh_car->getShader()->uniformMatrix("normalMatrix", normalMatrix_car);
		this->mesh_car->getShader()->uniformVector("lightPosition", Vector3f(0.0f, 5.0f, 5.0f));
	this->mesh_car->endRender();

	glDisable(GL_DEPTH_TEST);
    this->particleSystem_1->beginRender();
        this->particleSystem_1->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);
        this->particleSystem_1->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
        this->particleSystem_1->getShader()->uniformMatrix("normalMatrix", normalMatrix);
        this->particleSystem_1->getShader()->uniform1f("size", this->particleSize);
    this->particleSystem_1->endRender();

	this->particleSystem_2->beginRender();
        this->particleSystem_2->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);
        this->particleSystem_2->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
        this->particleSystem_2->getShader()->uniformMatrix("normalMatrix", normalMatrix);
        this->particleSystem_2->getShader()->uniform1f("size", this->particleSize);
    this->particleSystem_2->endRender();

	this->particleSystem_3->beginRender();
        this->particleSystem_3->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);
        this->particleSystem_3->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
        this->particleSystem_3->getShader()->uniformMatrix("normalMatrix", normalMatrix);
        this->particleSystem_3->getShader()->uniform1f("size", this->particleSize);
    this->particleSystem_3->endRender();

    glFlush();
}

void QViewport::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    this->camera->setPerspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float proj[16];
    this->camera->getProjectionMatrix().toRawMatrix(proj);
    glMultMatrixf(proj);
    glMatrixMode(GL_MODELVIEW);
}

void QViewport::setParticleSize(float size) {
    this->particleSize = size;
}

void QViewport::setParticleLifeMin(float min) {
	this->particleSystem_1->setMinLifetime(min);
	this->particleSystem_2->setMinLifetime(min);
	this->particleSystem_3->setMinLifetime(min);
}

void QViewport::setParticleLifeMax(float max) {
	this->particleSystem_1->setMaxLifetime(max);
	this->particleSystem_2->setMaxLifetime(max);
	this->particleSystem_3->setMaxLifetime(max);
}

void QViewport::setBounceEnergy(float energy) {
	this->particleSystem_1->setBounceEnergy(energy);
	this->particleSystem_2->setBounceEnergy(energy);
	this->particleSystem_3->setBounceEnergy(energy);
}

void QViewport::setGravity(float x, float y, float z) {
	this->particleSystem_1->setGravity(x, y, z);
	this->particleSystem_2->setGravity(x, y, z);
	this->particleSystem_3->setGravity(x, y, z);
}

void QViewport::setColor(float r, float g, float b) {
	this->particleSystem_1->setColor(r, g, b);
	this->particleSystem_2->setColor(r, g, b);
	this->particleSystem_3->setColor(r, g, b);
}

void QViewport::setInitialVelocity(float velocity) {
	this->particleSystem_1->setInitVelocity(velocity);
	this->particleSystem_2->setInitVelocity(velocity);
	this->particleSystem_3->setInitVelocity(velocity);
}

void QViewport::mouseMoveEvent(QMouseEvent* e) {
    this->camera->onMouseMove(e->x(), e->y());
    this->mouseX = e->x();
    this->mouseY = e->y();
}

void QViewport::mousePressEvent(QMouseEvent* e) {
    if ( e->button() == Qt::LeftButton ) this->camera->onMouseButton(LB_DOWN, e->x(), e->y());
    else if ( e->button() == Qt::RightButton ) {
		this->camera->onMouseButton(RB_DOWN, e->x(), e->y());
    }
}

void QViewport::startButton() {
	this->spawnParticles = true;
}

void QViewport::stopButton() {
	this->spawnParticles = false;
}

void QViewport::mouseReleaseEvent(QMouseEvent* e) {
    if ( e->button() == Qt::LeftButton ) this->camera->onMouseButton(LB_UP, e->x(), e->y());
    else if ( e->button() == Qt::RightButton ) {
		this->camera->onMouseButton(RB_UP, e->x(), e->y());
    }
}

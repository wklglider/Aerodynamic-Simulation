
#ifndef Q_VIEWPORT_H
#define Q_VIEWPORT_H

#include <gl/glew.h>
#include <QtOpenGL>
#include <memory>
#include <MouseCamera.h>
#include <ParticleSystem.h>
#include <Grid.h>
#include <Mesh.h>


class QTimer;

class QViewport : public QGLWidget {
    Q_OBJECT

public:
    QViewport(QWidget* parent);
    virtual ~QViewport();

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void setParticleSize(float size);
	void setParticleLifeMin(float min);
	void setParticleLifeMax(float max);
	void setBounceEnergy(float energy);
	void setGravity(float x, float y, float z);
	void setColor(float r, float g, float b);
	void setInitialVelocity(float velocity);

    //------------------------------------------------------------------------------
    // TODO: Implement functions for modifying the particle system
    // stored within this Viewport.
    //------------------------------------------------------------------------------

    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
	void startButton();
	void stopButton();

public slots:
    void onTimeout();

protected:
    std::shared_ptr<MouseCameraf> camera;
	std::shared_ptr<ParticleSystem> particleSystem_1;
	std::shared_ptr<ParticleSystem> particleSystem_2;
	std::shared_ptr<ParticleSystem> particleSystem_3;
    std::shared_ptr<Grid> grid;
	std::shared_ptr<Mesh> mesh_car;

    /* Size uniformed to the geometry shader for the particle system. */
    float particleSize;

    /* Timer used to update the viewport for 60[fps] */
    QTimer* timer;
    float timeStep;

    /* 
     * Variables used to control and define the spray direction of the particles.
     * The point represents the spawn position of the particles at the end of the mouse
     * in world coordinates. The direction is defined by the combination of the mouse
     * position (x, y) and the direction defined by the view frustrum of the camera.
     */
    Vector3f spawnPoint, spawnDirection;
    int mouseX, mouseY;

    /* Determines when particles are spawned at the mouse position. */
    bool spawnParticles;
};

#endif


#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include <memory>
#include <Transformation.h>
#include "Particle.h"
#include "Color3.h"

class GeometryShader;

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    /* Load the shader used for rendering the particle system. */
    bool loadShader(const std::string& vertexFilename, const std::string& geometryFilename, const std::string& fragmentFilename);

    /* Sets the size of the particle array */
    void setMaxParticleCount(std::size_t particleCount);

    /*
     * If spawnParticles is true, then particles that reside within this system will be
     * translated to the spawnPosition with an initial velocity defined in the
     * spawnDirection. The dt parameter represents the simualtion time-step.
     */
	void update(bool spawnParticles, const Vector3f& spawnPosition, float dt, const Vector3f& magneticField_1, const Vector3f& magneticField_2, const Vector3f& magneticField_3, const Vector3f& magneticField_4);

    void beginRender() const;
    void endRender() const;

    //------------------------------------------------------------------------------
    // TODO: Implement functions for modifying the particle system.
    //------------------------------------------------------------------------------
	void setGravity(float x, float y, float z);
	void setColor(float r, float g, float b);
	void setBounceEnergy(float energy);
	void setInitVelocity(float velocity);
	void setMinLifetime(float min);
	void setMaxLifetime(float max);
    void setPosition(float x, float y, float z);
    void setPosition(const Vector3f& position);

    std::shared_ptr<GeometryShader>& getShader();
    const std::shared_ptr<GeometryShader>& getShader() const;

protected:
    bool constructOnGPU();

protected:
	std::vector<Particle> particles;
    std::shared_ptr<GeometryShader> shader;

    /* 
     * The spawn position of the particles is defined by unprojecting the 2D
     * mouse coorindates to obtain a global 3D position where the particles
     * will be spawned in front of the camera. The direction is based on the
     * vector starting at the position of the camera and pointing to the
     * spawnPosition. These are set using the update function.
     */
    Vector3f spawnPosition;
    Vector3f spawnDirection;

    /* 
     * Define the minimum and maximum lifetime of a particle. The range is defined so
     * that the randomly generated lifetimes will be within this interval.
     */
    float minLifetime, maxLifetime;

    /* 
     * Magnitude of the initial velocity for the particles when they are
     * spawned. The initial velocity direction is given by spawnDirection.
     */
    float initVelocity;
    
    /* 
     * Bounce coefficient. Represents how much kinectic energy the particle
     * keeps after it has collided with a surface.
     */
    float bounceEnergy;

    Vector3f gravity;

    /* 
     * Current color of the particles. This color value is assigned to the
     * particles when they are spawned. 
     */
    Color3f color;

    /* Vertex buffer object that stores the particles. */
	unsigned int vboId;
};

#endif

#include "ParticleContact.hpp"

void ParticleContact::resolve(float deltaTime)
{
    this->resolveVelocity(deltaTime);
}

float ParticleContact::getSeparatingSpeed()
{
    Vector3 v = particles[0]->velocity;

    if(particles[1])
        v -= particles[1]->velocity;

    return Vector3::Dot(v, this->contactNormal);
}

void ParticleContact::resolveVelocity(float deltaTime)
{

    float separatingSpeed = this->getSeparatingSpeed();

    if(separatingSpeed > 0)
        return;

    float newSS = -restitution * separatingSpeed;
    float deltaSpeed = newSS - separatingSpeed;

    float totalMass = 1.f / particles[0]->mass;

    if(particles[1])
        totalMass += 1.f / particles[1]->mass;


    if(totalMass <= 0)
        return;

    float impulseMag = deltaSpeed / totalMass;
    Vector3 impulse = contactNormal * impulseMag;

    Vector3 v_a = impulse * (1.f/particles[0] -> mass);
    particles[0]->velocity += v_a;
  


    if (particles[1]) {
        Vector3 v_b = impulse * (-1.f / particles[1]->mass);
        particles[1]->velocity += v_b;
    }


}

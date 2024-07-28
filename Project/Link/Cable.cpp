#include "Cable.hpp"

ParticleContact* Cable::getContact()
{
    float currLen = currentLength();

    if (currLen == cableLength)
        return nullptr;

    ParticleContact* ret = new ParticleContact();
    ret->particles[0] = particles[0];
    ret->particles[1] = particles[1];


    Vector3 dir = particles[1]->position - particles[0]->position;
    dir.Normalize();

    particles[0]->velocity = Vector3::zero;

    if (currLen > cableLength) {
        ret->contactNormal = dir;
        ret->depth = currLen - cableLength;
        std::cout << "Magnitude: " << particles[1]->accumulatedForce.Magnitude() << std::endl;
        particles[1]->AddForce(dir * particles[1]->accumulatedForce.Magnitude());
    }

    ret->restitution = restitution;

    return ret;
}

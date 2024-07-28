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
    particles[0]->position = anchorPosition;

    if (currLen > cableLength) {
        ret->contactNormal = dir;
        ret->depth = currLen - cableLength;   
    }
    ret->restitution = restitution;

    return ret;
}

#include "ContactResolver.hpp"



void ContactResolver::Resolve(std::vector<ParticleContact*> contacts, float deltaTime)
{

    int current_iter = 0;

    while (current_iter < max_iter) {

        unsigned current_index = 0;
        float curr_min = contacts[0]->getSeparatingSpeed();
        float max_depth = contacts[0]->depth;

        for (int i = 1; i < contacts.size(); i++) {
            float ss = contacts[i]->getSeparatingSpeed();

            if (ss < curr_min && ss < 0 || 0 < contacts[i]->depth) {
                current_index = i;
                curr_min = ss;

                if(max_depth < contacts[i]->depth)
                    max_depth = contacts[i]->depth;


            }


        }

        if(curr_min >= 0 && max_depth <= 0)
            return;

        contacts[current_index]->resolve(deltaTime);
        current_iter++;
    }



}

#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include "emp/Evolve/World.hpp"

class OrgWorld; //This is a forward declaration that ensures the compiler this thing exists and we'll define it later

class Organism {
    private:
        double points;
        emp::Ptr<emp::Random> random;
        bool updated_this_step = false;
        emp::Ptr<OrgWorld> world = nullptr;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        points(_points), random(_random) {;}

    
    void SetWorld(emp::Ptr<OrgWorld> _world) {world = _world;}
    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}

    void SetUpdated(bool _in) {updated_this_step = _in;}
    bool GetUpdated() {return updated_this_step;}


    void Process(emp::WorldPosition pos) {
        std::cout << "Processing" << std::endl; //feel free to get rid of this
       
    }
};
#endif
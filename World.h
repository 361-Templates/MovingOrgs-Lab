#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {

    emp::vector<bool> sand_particles;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random) {
        
        InitializeSand(0.5);
        
    }

    ~OrgWorld() {
    }

    void InitializeSand(double density = 0.5) {
        sand_particles.resize(GetSize());
        for(size_t i = 0; i < GetSize(); i++) {
            sand_particles[i] = GetRandom().P(density);
        }
    }

    bool SandParticleAt(emp::WorldPosition pos) {
        return sand_particles[pos.GetIndex()];
    }

    void SetSandParticleAt(emp::WorldPosition pos, bool has_sand) {
        sand_particles[pos.GetIndex()] = has_sand;
    }

    void Resize(size_t new_width, size_t new_height) {
        emp::World<Organism>::Resize(new_width, new_height);
        InitializeSand(0.5);
    }

    bool MoveOrganism(emp::WorldPosition from_pos, emp::WorldPosition to_pos) {
        size_t from_id = from_pos.GetIndex();
        size_t to_id = to_pos.GetIndex();

        if (!IsOccupied(from_id)) { // Nothing was there...
            return false;
        }

        pop[to_id] = pop[from_id];
        pop[from_id] = nullptr;
        return true;
    }



  void Update() {
      emp::World<Organism>::Update();
      for (size_t i = 0; i< GetSize(); i++) {
          if (IsOccupied(i)) {
              pop[i]->SetUpdated(false);
          }
      }


      emp::vector<size_t> schedule = emp::GetPermutation(GetRandom(), GetSize());
      std::cout << "Updating!" << std::endl;
      for(int i : schedule) {
        if(!IsOccupied(i)) {continue;}
        if(pop[i]->GetUpdated()) {continue;}

        pop[i]->SetUpdated(true);
        pop[i]->Process(i);
        
        emp::WorldPosition new_pos = GetRandomNeighborPos(i);
        MoveOrganism(i, new_pos);

      }
  }

};
#endif
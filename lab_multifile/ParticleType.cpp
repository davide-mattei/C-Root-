

#include "ParticleType.hpp"

const char* ParticleType::getName () const  {
    return fName;
}
double ParticleType::getMass() const {
    return fMass;
}
int ParticleType::getCharge() const {
    return fCharge;
}
double ParticleType::getWidth() const {
    return 0;
}

void ParticleType::Print () const {
    std::cout<< "Particle's Type: " << fName << '\n'
    << "Mass: " << fMass << '\n' << "Charge: " << fCharge << '\n';
}

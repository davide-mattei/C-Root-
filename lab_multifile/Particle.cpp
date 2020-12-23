//
//  Particle.cpp
//
//
//  Created by Michele Mattei on 21/10/2020.
//

#include "Particle.hpp"
#include <cmath>   // for pi and sqrt/pow
#include <cstdlib> // for RAND_MAX

// Static Members declaration

int Particle::fNParticleType = 0;
ParticleType *Particle::fParticleType[fMaxNumParticleType];

// Getters

int Particle::getIparticle() const { return fIParticle; }
double Particle::getPx() const { return fPx; }
double Particle::getPy() const { return fPy; }
double Particle::getPz() const { return fPz; }
double Particle::getTotalMomentum() const {
  return sqrt(pow(fPx, 2) + pow(fPy, 2) + pow(fPz, 2));
}
double Particle::getParticleMass() const {
  return fParticleType[fIParticle]->getMass();
}
double Particle::getParticleEnergy() const {
  return sqrt(pow(getParticleMass(), 2) + pow(getTotalMomentum(), 2));
}
const char *Particle::getParticleName() const {
  return fParticleType[fIParticle]->getName();
}
int Particle::getParticleCharge() const {
  return fParticleType[fIParticle]->getCharge();
}

double Particle::InvMass(Particle const &p) const {
  double E = pow(p.getParticleEnergy() + getParticleEnergy(), 2);
  double P = pow(p.getPx() + getPx(), 2) + pow(p.getPy() + getPy(), 2) +
             pow(p.getPz() + getPz(), 2);
  return sqrt(E - P);
}
double Particle::InvMass(Particle *p) const {
  double E = pow(p->getParticleEnergy() + getParticleEnergy(), 2);
  double P = pow(p->getPx() + getPx(), 2) + pow(p->getPy() + getPy(), 2) +
             pow(p->getPz() + getPz(), 2);
  return sqrt(E - P);
}

// Setters

void Particle::SetParticle(int index) {
  if (index >= fNParticleType) {
    std::cout << "Out-of-range index " << '\n';
  }
  fIParticle = index;
}

void Particle::SetParticle(char *iName) {
  int index = FindParticle(iName);
  if (index == fNParticleType) {
    std::cout << "Particle is not in the array. Add it through the "
                 "AddParticleType method."
              << '\n';
  } else {
    fIParticle = index;
  }
}
void Particle::setP(double iPx, double iPy, double iPz) {
  fPx = iPx;
  fPy = iPy;
  fPz = iPz;
}

void Particle::PrintParticle() const {
  std::cout << "Particle's index: " << fIParticle << '\n'
            << "Particle's type: " << fParticleType[fIParticle]->getName()
            << '\n'
            << "Particle's momentum: " << '\n'
            << "x: " << fPx << "   y: " << fPy << "   z: " << fPz << '\n';
}

// Static Methods

void Particle::PrintArray() {
  for (int i = 0; i != fNParticleType; ++i) {
    fParticleType[i]->Print();
  }
}

void Particle::AddParticleType(const char *iName, double iMass, int iCharge,
                               double iWidth) {
  if (FindParticle(iName) != fNParticleType) {
    std::cout << "Particle already exists. " << '\n';
    return;
  } else if (fNParticleType == fMaxNumParticleType) {
    std::cout << "The array is full. Delete some particles. " << '\n';
    return;
  } else if (iWidth == 0) {
    fParticleType[fNParticleType] = new ParticleType{iName, iMass, iCharge};
    ++fNParticleType;
  } else {
    fParticleType[fNParticleType] =
        new ResonanceType{iName, iMass, iCharge, iWidth};
    ++fNParticleType;
  }
}

int Particle::FindParticle(const char *iName) {
  for (int i = 0; i != fNParticleType; ++i) {
    if (iName == fParticleType[i]->getName()) {
      return i;
    }
  }
  return fNParticleType;
}

// Decay

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
  if (getParticleMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = getParticleMass();
  double massDau1 = dau1.getParticleMass();
  double massDau2 = dau2.getParticleMass();

  if (fIParticle > -1) { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIParticle]->getWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf("Decayment cannot be preformed because mass is too low in this "
           "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.setP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.setP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz) {

  double energy = getParticleEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}

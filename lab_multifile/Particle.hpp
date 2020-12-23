//
//  Particle.hpp
//
//
//  Created by Michele Mattei on 21/10/2020.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ResonanceType.hpp"

class Particle {
public:
  Particle(const char *iName, double iPx, double iPy, double iPz)
      : fPx{iPx}, fPy{iPy}, fPz{iPz} {
    fIParticle = FindParticle(iName);
    if (fIParticle == fNParticleType)
      std::cout << "Particle " << iName
                << " is not in the list. Add it trough the \"AddParticleType\" "
                   "method. "
                << '\n';
  }

  Particle() = default; // default constructor

  //    Getters

  int getIparticle() const;
  double getPx() const;
  double getPy() const;
  double getPz() const;
  double getTotalMomentum() const;
  double getParticleMass() const;
  double getParticleEnergy() const;
  const char *getParticleName() const;
  int getParticleCharge() const;

  double InvMass(Particle const &p) const;
  double InvMass(Particle *p) const;

  //    Setters

  void SetParticle(int index);
  void SetParticle(char *name);
  void setP(double iPx, double iPy, double iPz);

  void PrintParticle() const;

  //    Static Methods

  static void PrintArray();
  static void AddParticleType(const char *iName, double iMass, int iCharge,
                              double iWidth = 0);

  //    Decay Methods

  int Decay2body(Particle &dau1, Particle &dau2) const;

private:
  //    Static Members and Methods
  static const int fMaxNumParticleType = 10; // massimo numero di particelle
  static ParticleType *fParticleType[fMaxNumParticleType];
  static int fNParticleType; // numero di particelle nell'array
  static int FindParticle(const char *iName);

  double fPx = 0;
  double fPy = 0;
  double fPz = 0;
  int fIParticle = 0; // indice Particle dell'array

  //    Decay

  void Boost(double bx, double by, double bz);
};

#endif /* Particle_hpp */

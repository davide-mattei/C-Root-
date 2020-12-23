//
//  ParticleType.hpp
//
//
//  Created by Michele Mattei on 17/10/2020.
//

#ifndef ParticleType_h
#define ParticleType_h

#include <iostream>

class ParticleType {
public:
  ParticleType(const char *iName, double iMass, int iCharge)
      : fName{iName}, fMass{iMass}, fCharge{iCharge} {}

  virtual ~ParticleType() { delete fName; };

  //    Getters
  const char *getName() const;
  double getMass() const;
  int getCharge() const;
  virtual double getWidth() const;

  virtual void Print() const;

private:
  char const *fName;
  double const fMass;
  int const fCharge;
};

#endif /* ParticleType_h */

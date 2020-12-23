//
//  ResonanceType.hpp
//
//
//  Created by Michele Mattei on 21/10/2020.
//

#ifndef ResonanceType_hpp
#define ResonanceType_hpp

#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
public:
  ResonanceType(const char *iName, double iMass, int iCharge, double iWidth)
      : ParticleType(iName, iMass, iCharge), fWidth{iWidth} {}

  //    ~ResonanceType()

  double getWidth() const override;

  void Print() const override;

private:
  double const fWidth;
};

#endif /* ResonanceType_hpp */

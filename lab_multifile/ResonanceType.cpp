//
//  ResonanceType.cpp
//
//
//  Created by Michele Mattei on 21/10/2020.
//

#include "ResonanceType.hpp"

double ResonanceType::getWidth() const { return fWidth; }

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Width: " << fWidth << '\n';
}

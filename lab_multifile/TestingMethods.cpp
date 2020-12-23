
/*
 
 #include "Particle.hpp"
 
 
void TestingMethods () {
     
     char p[]= "pion";
     char e[]= "electron";
     char m[] = "muon";
     char t[]= "tau";
     char ph[]= "photon";
     char en[] = "eneutrino";
     
     //testing AddParticleType and Particle's Constructor
     ParticleType* array[2];
     array[0] = new ParticleType(e, 9E-31, 1);
     array[1] = new ResonanceType(m, 1.9E-28, 1, 0.5);
     
     for (int i=0; i!=2; ++i) array[i]->Print();
     
     Particle::AddParticleType(e, 1E-30, -1);
     Particle::AddParticleType(m, 1E-28, -1, 0.5);
     
     Particle * particlearray[3];
     particlearray[0] = new Particle(e, 1E5, 1E5, 1E5);
     particlearray[1] = new Particle(m, 1E6, 1E4, 1E7);
     particlearray[2] = new Particle(p, 1E7, 1E7, 1E7);
     
     Particle::AddParticleType(p, 2.49E-28, 1, 0.3);
     
     // Testing all Particle's methods
     Particle::PrintArray();
     for (int i=0; i!=2; ++i) particlearray[i]->PrintParticle();
     
     particlearray[0] -> setP(1.5E6, 1.43E5, 3.33E5);
     particlearray[0] -> PrintParticle();
     
     std::cout << '\n' << '\n';
     
     Particle::AddParticleType(t, 1.92E-27, 1);
     Particle::AddParticleType(ph, 0, 0);
     Particle::AddParticleType(en, 3E-30, 1);
     
     particlearray[1] -> SetParticle(t);
     particlearray[2] -> SetParticle(5);

 //    Testing Particle's Getters
     for (int i=0; i!=3; ++i) {
         particlearray[i]->PrintParticle();
         std::cout << "Total Momentum: " << particlearray[i]->getTotalMomentum()<<
         "   Mass: " << particlearray[i]->getParticleMass() <<
         "   Energy: " << particlearray[i]->getParticleEnergy() << '\n';
     }
     
     std::cout << '\n' << "Testing Mass Invariant: " << '\n';
     for (int i=0; i!=3; ++i) {
         for (int j=0; j!=3; ++j){
             if (i!=j){ std::cout << "Particles: "<< particlearray[i]->getParticleName() << " , " << particlearray[j]->getParticleName() << '\n' << "Mass Invariant: " << particlearray[i]->InvMass(particlearray[j]) << '\n';}
         }
     }
     
 }*/


#include "Particle.hpp"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom.h"
#include <cmath>

int main() {
  auto start = std::chrono::system_clock::now();

  int constexpr events = 1E5;
  int constexpr nBins = 1E3;
  int constexpr nParticles = 120;
  gRandom->SetSeed();

  //    Generated Particles
  char p_p[] = "pion+";
  char p_m[] = "pion-";
  double constexpr pMass = 0.13957; // GeV/c^2
  char k_p[] = "kaon+";
  char k_m[] = "kaon-";
  double constexpr kMass = 0.49367; // GeV/c^2
  char pr_p[] = "proton+";
  char pr_m[] = "proton+";
  double constexpr protonMass = 0.93827; // GeV/c^2
  char Kstar[] = "K*";
  double constexpr KstarMass = 0.89166; // GeV/c^2

  //    Filling ParticleArray
  Particle::AddParticleType(p_p, pMass, +1);
  Particle::AddParticleType(p_m, pMass, -1);
  Particle::AddParticleType(k_p, kMass, +1);
  Particle::AddParticleType(k_m, kMass, -1);
  Particle::AddParticleType(pr_p, protonMass, +1);
  Particle::AddParticleType(pr_m, protonMass, -1);
  Particle::AddParticleType(Kstar, KstarMass, 0, 0.050);

  //    creating root data file
  TFile *file = new TFile("data.root", "recreate");

  //    creating Histograms
  TH1F *hProportions = new TH1F("hProportions", "Particles' type", 7, 0, 7);
  TH1F *hAzimuthal =
      new TH1F("hAzimuthal", "Azimuthal angle distribution", 500, 0, M_PI);
  TH1F *hPolar =
      new TH1F("hPolar", "Polar angle distribution", 500, 0, 2 * M_PI);
  TH1F *hMomentum = new TH1F("hMomentum", "Momentum", nBins, 0, 5.5);
  TH1F *hTransverseMomentum =
      new TH1F("hTransverseMomentum", "Transverse momentum", nBins, 0, 4);
  TH1F *hEnergy = new TH1F("hEnergy", "Particles' energy", nBins, 0, 5);
  TH1F *hInvMass = new TH1F("hInvMass", "Mass Invariant", nBins, 0, 5);
  TH1F *hInvMassConcordant =
      new TH1F("hInvMassConcordant", "Mass Invariant - Concordant Particles",
               nBins, 0, 5);
  TH1F *hInvMassDiscordant =
      new TH1F("hInvMassDiscordant", "Mass Invariant - Discordant Particles",
               nBins, 0, 5);
  TH1F *hInvMassPKdiscordant =
      new TH1F("hInvMassPKdiscordant", "Mass Invariant - discordant p and k ",
               nBins, 0, 5);
  TH1F *hInvMassPKconcordant =
      new TH1F("hInvMassPKconcordant", "Mass Invariant - concordant p and k",
               nBins, 0, 5);
  TH1F *hInvMassKstarDecay =
      new TH1F("hInvMassKstarDecay", "Mass Invariant of p and k from decays",
               nBins, 0.6, 1.3);

  hInvMass->Sumw2();
  hInvMassConcordant->Sumw2();
  hInvMassDiscordant->Sumw2();
  hInvMassPKdiscordant->Sumw2();
  hInvMassPKconcordant->Sumw2();
  hInvMassKstarDecay->Sumw2();

  for (int j = 0; j != events; ++j) {

    int array_tail = 0;

    Particle particles[nParticles];

    for (int i = 0; i != 100; ++i) {

      double theta = gRandom->Rndm() * M_PI;
      double phi = gRandom->Rndm() * 2 * M_PI;

      hAzimuthal->Fill(theta);
      hPolar->Fill(phi);

      double momentum = gRandom->Exp(1); // GeV
      double px = momentum * sin(theta) * cos(phi);
      double py = momentum * sin(theta) * sin(phi);
      double pz = momentum * cos(theta);

      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(sqrt(pow(px, 2) + pow(py, 2)));

      particles[i].setP(px, py, pz);

      //        Generating the i-particle following the given proportions and
      //        filling hProportions
      double proportions = gRandom->Rndm();
      if (proportions < 0.4) { // 80% pions
        particles[i].SetParticle(p_p);
        hProportions->Fill(0);
      } else if (proportions < 0.8) {
        particles[i].SetParticle(p_m);
        hProportions->Fill(1);
      } else if (proportions < 0.85) {
        particles[i].SetParticle(k_p);
        hProportions->Fill(2);
      } else if (proportions < 0.9) { // 10% kaons
        particles[i].SetParticle(k_m);
        hProportions->Fill(3);
      } else if (proportions < 0.945) {
        particles[i].SetParticle(pr_p);
        hProportions->Fill(4);
      } else if (proportions < 0.99) { // 9% protons
        particles[i].SetParticle(pr_m);
        hProportions->Fill(5);
      } else if (proportions < 0.995) {
        particles[i].SetParticle(Kstar);
        hProportions->Fill(6);
        particles[100 + array_tail].SetParticle(p_p);
        ++array_tail;
        particles[100 + array_tail].SetParticle(k_m);
        ++array_tail;
        particles[i].Decay2body(particles[99 + array_tail],
                                particles[98 + array_tail]);
        hInvMassKstarDecay->Fill(
            particles[99 + array_tail].InvMass(particles[98 + array_tail]));
      } else { // 1% - K* decays 50% in p+,k- and 50% in p-,k+
        particles[i].SetParticle(Kstar);
        hProportions->Fill(6);
        particles[100 + array_tail].SetParticle(p_m);
        ++array_tail;
        particles[100 + array_tail].SetParticle(k_p);
        ++array_tail;
        particles[i].Decay2body(particles[99 + array_tail],
                                particles[98 + array_tail]);
        hInvMassKstarDecay->Fill(
            particles[99 + array_tail].InvMass(particles[98 + array_tail]));
      }
      hEnergy->Fill(particles[i].getParticleEnergy());
    }

    //  Filling the Mass Invariant's histograms
    for (int k = 0; k != 100 + array_tail - 1; ++k) {
      for (int t = k + 1; t != 100 + array_tail; ++t) {

        double iMass = particles[k].getParticleMass();
        double jMass = particles[t].getParticleMass();
        double mass_invariant = particles[k].InvMass(particles[t]);
        bool p_k = (iMass == pMass && jMass == kMass) ||
                   (iMass == kMass && jMass == pMass);

        hInvMass->Fill(mass_invariant);

        if (particles[k].getParticleCharge() > 0) {
          if (particles[t].getParticleCharge() > 0) {
            hInvMassConcordant->Fill(mass_invariant);
            if (p_k) {
              hInvMassPKconcordant->Fill(mass_invariant);
            }
          } else if (particles[t].getParticleCharge() < 0) {
            hInvMassDiscordant->Fill(mass_invariant);
            if (p_k) {
              hInvMassPKdiscordant->Fill(mass_invariant);
            }
          }
        } else if (particles[k].getParticleCharge() < 0) {
          if (particles[t].getParticleCharge() < 0) {
            hInvMassConcordant->Fill(mass_invariant);
            if (p_k) {
              hInvMassPKconcordant->Fill(mass_invariant);
            }
          } else if (particles[t].getParticleCharge() > 0) {
            hInvMassDiscordant->Fill(mass_invariant);
            if (p_k) {
              hInvMassPKdiscordant->Fill(mass_invariant);
            }
          }
        }
      }
    }
  }

  file->Write();
  file->Close();

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "Time required: " << diff.count() << " s\n";

  return 0;
}

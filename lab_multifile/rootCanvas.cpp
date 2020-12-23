
void FirstTrial () {
TFile *file = new TFile ("data.root");
//file->ls();

gStyle->SetOptFit(111);
gStyle->SetOptStat(2210);
    
//creating canvas
auto c1 = new TCanvas();
auto c2 = new TCanvas();
c1->Divide(3, 2);
c2->Divide(3, 2);
    
 TH1F *h[12];
h[0] = (TH1F*)file->Get("hProportions");
h[1] = (TH1F*)file->Get("hAzimuthal");
h[2] = (TH1F*)file->Get("hPolar");
h[3] = (TH1F*)file->Get("hMomentum");
h[4] = (TH1F*)file->Get("hTransverseMomentum");
h[5] = (TH1F*)file->Get("hEnergy");
h[6] = (TH1F*)file->Get("hInvMass");
h[7] = (TH1F*)file->Get("hInvMassConcordant");
h[8] = (TH1F*)file->Get("hInvMassDiscordant");
h[9] = (TH1F*)file->Get("hInvMassPKdiscordant");
h[10] = (TH1F*)file->Get("hInvMassPKconcordant");
h[11] = (TH1F*)file->Get("hInvMassKstarDecay");

for (int i=0; i!=12; ++i){
    h[i]->SetFillColor(38);
    h[i]->SetMarkerStyle(kFullDotLarge);
    h[i]->SetMarkerColor(46);
    h[i]->SetMarkerSize(0.15);
}
    
    for (int i = 0; i!= 6; ++i) {
        c1->cd(i+1);
        h[i]-> DrawCopy();
    }
    
    for (int i = 1; i!= 7; ++i) {
        c2->cd(i);
        h[i+5]-> DrawCopy();
    }

// parte 3
   
//verifying proportions
    
double pion_p = h[0]->GetBinContent(1);
double pion_n = h[0]->GetBinContent(2);
double kaon_p = h[0]->GetBinContent(3);
double kaon_n = h[0]->GetBinContent(4);
double proton_p = h[0]->GetBinContent(5);
double proton_n = h[0]->GetBinContent(6);
double kStar = h[0]->GetBinContent(7);
double total_particles = h[0]-> GetEntries();
       std::cout << "\nGenerated particles:\n";
       std::cout << "Pions+   are " << pion_p / total_particles << "% ± " << h[0]->GetBinError(1) / total_particles << "%,           0.40% expected\n";
       std::cout << "Pions-   are " << pion_n / total_particles << "% ± " << h[0]->GetBinError(2) / total_particles << "%,           0.40% expected\n";
       std::cout << "Kaons+   are " << kaon_p / total_particles << "% ± " << h[0]->GetBinError(3) / total_particles << "%,           0.05% expected\n";
       std::cout << "Kaons-   are " << kaon_n / total_particles << "% ± " << h[0]->GetBinError(4) / total_particles << "%,           0.05% expected\n";
       std::cout << "Protons+ are " << proton_p / total_particles << "% ± " << h[0]->GetBinError(5) / total_particles << "%,           0.045% expected\n";
       std::cout << "Protons- are " << proton_n / total_particles << "% ± " << h[0]->GetBinError(6) / total_particles << "%,           0.045% expected\n";
       std::cout << "K*       are " << kStar / total_particles << "% ± " << h[0]->GetBinError(7) / total_particles << "%,           0.01% expected\n\n";
    
//    fitting angles' distributions

    auto c_anglesFit = new TCanvas();
    c_anglesFit -> Divide(2,1);
    c_anglesFit -> cd(1);
    h[1] -> Fit("pol0","Q");
    h[1] -> DrawCopy();
    c_anglesFit -> cd(2);
    h[2] -> Fit("pol0","Q");
    h[2] -> DrawCopy();
    
    TF1 *fitFunc1 = h[1]->GetFunction("pol0");
    TF1 *fitFunc2 = h[2]->GetFunction("pol0");
    
    double ChiSquare1 = fitFunc1->GetChisquare();
    double NDF1 = fitFunc1->GetNDF();
    std::cout << "Fitting angle's distributions" << '\n' << '\n';
    std::cout << "Azimuthal angle: " << '\n'
    << "Chisquare of the fit: " << ChiSquare1 << '\n'
    << "Degrees of freedom: " << NDF1 << '\n'
    << "Chisquare / NDF: " << ChiSquare1 /  NDF1 << '\n' << '\n';
    
    double ChiSquare2 = fitFunc2->GetChisquare();
    double NDF2 = fitFunc2->GetNDF();
    std::cout << "Polar angle: " << '\n'
    << "Chisquare of the fit: " << ChiSquare2 << '\n'
    << "Degrees of freedom: " << NDF2 << '\n'
    << "Chisquare / NDF: " << ChiSquare2 /  NDF2 << '\n' << '\n';
    
    
//    fitting momentum's distribution
    
    auto c_momentumFit = new TCanvas();
    h[3] -> Fit("expo","Q");
    
    TF1 *fitFunc3 = h[3]->GetFunction("expo");
    double ChiSquare3 = fitFunc3->GetChisquare();
    double NDF3 = fitFunc3->GetNDF();
    
    std::cout << "Fitting momentum's distribution" << '\n' << '\n';
    std::cout << "Distribution's mean: " << h[3]->GetMean() << " +/- " << h[3]->GetMeanError()
    << ",     expected mean: 1 " << '\n'
    << "Chisquare of the fit: " << ChiSquare3 << '\n'
    << "Degrees of freedom: " << NDF3 << '\n'
    << "Chisquare / NDF: " << ChiSquare3 /  NDF3 << '\n' << '\n';

    
//    operation on invariant masses
    
    TH1F hSubtractionPK = (*h[9])-(*h[10]);
    TF1 *fit4 = new TF1("Fit subtraction discordant-concordant Pion Kaon", "gaus", 0.6, 1.3); //relativo fit
    
    auto c_InvMassFit = new TCanvas();
    c_InvMassFit -> Divide (2,2);
    c_InvMassFit -> cd(1);
    h[9] -> DrawCopy();
    c_InvMassFit -> cd(2);
    h[10] -> DrawCopy();
    c_InvMassFit -> cd(3);
    hSubtractionPK.Fit("Fit subtraction discordant-concordant Pion Kaon","Q");
    hSubtractionPK.DrawCopy();
    c_InvMassFit -> cd(4);
    h[11] -> DrawCopy();
    
    TF1 *fitFunc4 = hSubtractionPK.GetFunction("Fit subtraction discordant-concordant Pion Kaon");
    
    double ChiSquare4 = fitFunc4->GetChisquare();
    double NDF4 = fitFunc4->GetNDF();
    double Mean4 = fitFunc4->GetParameter(1);
    double MeanError4 = fitFunc4->GetParError(1);
    double Sigma4 = fitFunc4->GetParameter(2);
    double SigmaError4 = fitFunc4->GetParError(2);
    
    std::cout << "Mass Invariant - Fitting the Subtraction between P-K with discordant and concordant charge" << '\n' << '\n';
    std::cout << "Distribution's mean: " << Mean4 << " +/- " << MeanError4 << '\n'
    << "Mean from Simulation: " << h[11] -> GetMean() << " +/- " << h[11]->GetMeanError()<< '\n'
    << " Distribution's RMS: " << Sigma4 << " +/- " << SigmaError4 << '\n'
    << " RMS from Simulation: " << h[11] -> GetRMS() << " +/- " << h[11]->GetRMSError()<< '\n'
    << "Chisquare of the fit: " << ChiSquare4 << '\n'
    << "Degrees of freedom: " << NDF4 << '\n'
    << "Chisquare / NDF: " << ChiSquare4 /  NDF4 << '\n' << '\n';
    
    c_InvMassFit->Print("c_InvMassFit.pdf", "pdf");
    c2->Print("c2.pdf", "pdf");
    
//    comparing with subtraction of all discordant-concordant particles
    
    TH1F hSubtractionAll = (*h[8])-(*h[7]);
    TF1 *fit5 = new TF1("Fit subtraction discordant-concordant particles", "gaus", 0.5, 1.5); //relativo fit
    
    auto c_InvMassFitAll = new TCanvas();
    c_InvMassFitAll -> Divide (2,2);
    c_InvMassFitAll -> cd(1);
    h[7] -> DrawCopy();
    c_InvMassFitAll -> cd(2);
    h[8] -> DrawCopy();
    c_InvMassFitAll -> cd(3);
    hSubtractionAll.Fit("Fit subtraction discordant-concordant particles", "Q");
    hSubtractionAll.DrawCopy();
    c_InvMassFitAll -> cd(4);
    h[11] -> DrawCopy();
    
    TF1 *fitFunc5 = hSubtractionAll.GetFunction("Fit subtraction discordant-concordant particles");
    
    double ChiSquare5 = fitFunc5->GetChisquare();
    double NDF5 = fitFunc5->GetNDF();
    double Mean5 = fitFunc5->GetParameter(1);
    double MeanError5 = fitFunc5->GetParError(1);
    double Sigma5 = fitFunc5->GetParameter(2);
    double SigmaError5 = fitFunc5->GetParError(2);
    
    std::cout << "Mass Invariant - Fitting the Subtraction between P-K with discordant and concordant charge" << '\n' << '\n';
    std::cout << "Distribution's mean: " << Mean5 << " +/- " << MeanError5 << '\n'
    << "Mean from Simulation: " << h[11] -> GetMean() << " +/- " << h[11]->GetMeanError()<< '\n'
    << " Distribution's RMS: " << Sigma5 << " +/- " << SigmaError5 << '\n'
    << " RMS from Simulation: " << h[11] -> GetRMS() << " +/- " << h[11]->GetRMSError()<< '\n'
    << "Chisquare of the fit: " << ChiSquare5 << '\n'
    << "Degrees of freedom: " << NDF5 << '\n'
    << "Chisquare / NDF: " << ChiSquare5 /  NDF5 << '\n' << '\n';
    
    c_InvMassFitAll->Print("c_InvMassFitAll.pdf", "pdf");
    
}


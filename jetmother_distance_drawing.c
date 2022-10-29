const char* inputpath="/Users/yoonha/Desktop/NPL/rootfiles/jetparticlegg2qq_2.root";

void jetmother_distance_drawing()
{
    TFile *f  = new TFile(inputpath, "open");
    TH1F * dr = (TH1F *)gROOT->FindObject("dr");

   // eta->Rebin2D(2,2);
    
    TCanvas* c=new TCanvas("canvas","canvas",500,500);
    c->cd();

    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.04, 1, 1);
    pad1->BuildLegend();
    pad1->Draw();
    pad1->cd();
    
    dr->SetTitle("dR between jet axis & leading mom");
    dr->SetStats(0);
    dr->GetXaxis()->SetTitle("dR=#sqrt{(#eta_{jet}-#eta_{mom})^{2}+(#phi_{jet}-#phi_{mom})^{2}}");
    dr->GetXaxis()->SetTitleOffset(1.3);
    dr->Draw();
     
    TPaveText *script = new TPaveText(0.2,9000,0.5,14000);
    script->SetFillColorAlpha(0,0);
    script->SetBorderSize(0);
    script->SetTextFont(42);
    script->AddText("PYTHIA8 pp 13TeV");
    script->AddText("PartonLevel:MPI,ISR,FSR = off");
    script->AddText("g g #rightarrow q qbar");
    script->AddText("PhaseSpace:pTHatMin=20.");
    script->Draw();

    TPaveText *script2 = new TPaveText(0.2,2e3,0.5,7e3);
    script2->SetFillColorAlpha(0,0);
    script2->SetBorderSize(0);
    script2->SetTextFont(42);
    script2->AddText("particle range: |#eta |<4");
    script2->AddText("jet Recontruction: full jet");
    script2->AddText("anti #it{k}_{T} R=0.7");
    script2->AddText("10<p_{T,jet}<140 GeV/c, |#eta_{jet}|<3.");
    script2->Draw();
    
    




    return;
}

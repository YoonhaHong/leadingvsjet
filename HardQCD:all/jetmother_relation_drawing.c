void jetmother_relation_drawing (int Rmode =2 ){
    TString inputpath="./jetparticle2_all_MIF_";
    
    TString Rsize; Rsize.Form("R%02d",Rmode);
    inputpath.Append(Rsize); 
    inputpath.Append(".root");
    
    TFile *f  = new TFile(inputpath, "open");
    TH2F * pt = (TH2F *)gROOT->FindObject("quarkjet_particle_pt");
    TH2F * eta = (TH2F *)gROOT->FindObject("quarkjet_particle_eta");
    TH2F * phi = (TH2F *)gROOT->FindObject("quarkjet_particle_phi");
    TH2F * dR = (TH2F *)gROOT->FindObject("dr");

    TCanvas* c=new TCanvas("canvas","canvas",2000,500);
    c->Divide(3,1);
    
    c->cd(1);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1);
    pad1->BuildLegend();

    TPad *pad2 = (TPad*)pad1->Clone();
    TPad *pad3 = (TPad*)pad1->Clone();
    pad1->Draw();
    pad1->cd();
   
    pt->SetTitle("");
    pt->SetStats(0);
    pt->GetXaxis()->SetTitle("jet p_{T} (GeV/c)");
    pt->GetYaxis()->SetTitle("leading particle p_{T} (GeV/c)");
    TH2F * zoomed = (TH2F *)pt->Clone();

   // pt->RebinX(2); pt->RebinY(2);
    pt->Draw("colz");


    c->cd(2);
    pad2->Draw(); pad2->cd();
    eta->SetTitle("leading particle vs jet (p_{T}, #eta, #phi)");
    eta->GetXaxis()->SetTitle("#eta_{jet}");
    eta->GetYaxis()->SetTitle("#eta_{lp}");
    eta->SetStats(0);
    eta->Draw("colz");

    TPaveText *script = new TPaveText(0.11,0.61,0.56,0.90,"NDC");
    script->SetFillColorAlpha(0,0);
    script->SetBorderSize(0);
    script->SetTextFont(42);
    script->AddText("PYTHIA8 pp 13TeV");
    script->AddText("HardQCD:all");
    script->AddText("PartonLevel:MPI,ISR,FSR = on");
    script->AddText("PhaseSpace:pTHatMin=20");
    script->Draw();

    TPaveText *script2 = new TPaveText(0.48,0.15,0.89,0.44,"NDC");
    script2->SetFillColorAlpha(0,0);
    script2->SetBorderSize(0);
    script2->SetTextFont(42);
    script2->AddText("particle range: |#eta |<4");
    script2->AddText("jet Recontruction: full jet");
    if (Rmode==2) script2->AddText("anti #it{k}_{T} R=0.2");
    else if (Rmode==7) script2->AddText("anti #it{k}_{T} R=0.7");
    script2->AddText("10<p_{T,jet}<140 GeV/c, |#eta_{jet}|<3");
    script2->Draw();
    
    
    c->cd(3);
    pad3->Draw(); pad3->cd();
    phi->SetTitle("");
    phi->GetXaxis()->SetTitle("#phi_{jet}");
    phi->GetYaxis()->SetTitle("#phi_{lp}");
    phi->SetStats(0);
    phi->Draw("colz");



    TCanvas* c2 = new TCanvas("zoomed","zoomed",500,500); 
    TPad* c2pad = new TPad("c2pad","c2pad",0,0,1,1);
   // zoomed->RebinX(2); zoomed->RebinY(2);

    TString title = "HardQCD:all with bkg, ";

    
    if(Rmode==2) title.Append("R=0.2");
    else if(Rmode==7) title.Append("R=0.7");
    zoomed->SetTitle(title);

    zoomed->GetXaxis()->SetRangeUser(10,40);
    zoomed->GetYaxis()->SetRangeUser(10,40);
    c2->cd(); c2pad->Draw();
    c2pad->cd(); 
    zoomed->Draw("colz");
    
    TPaveText *zoomedscpt = new TPaveText(0.57,0.27,0.85,0.39,"NDC");
    zoomedscpt->AddText("MPI,ISR,FSR = on");

    zoomedscpt->SetFillColorAlpha(0,0);
    zoomedscpt->SetBorderSize(0);
    zoomedscpt->SetTextFont(42);
    zoomedscpt->Draw();



    TCanvas* c3 = new TCanvas("dR","dR",500,500); 
    TPad* c3pad = new TPad("c3pad","c3pad",0,0.10,1,1); 
    c3pad->SetLogy();

    c3->cd(); c3pad->Draw();
    c3pad->cd(); 

    
    TH1* frame3=gPad->DrawFrame(0,0.5,0.7,7e3);
    frame3->GetXaxis()->SetTitle("dR=#sqrt{(#eta_{jet}-#eta_{lp})^{2}+(#phi_{jet}-#phi_{lp})^{2}}");
    frame3->GetXaxis()->SetTitleOffset(1.17);
    frame3->Draw();

    frame3->SetTitle(title);
    dR->SetStats(0);
    dR->Draw("same");
    TPaveText *dRscpt = new TPaveText(0.57,0.70,0.82,0.75,"NDC");
    dRscpt->SetFillColorAlpha(0,0);
    dRscpt->SetBorderSize(0);
    dRscpt->SetTextFont(42);
    dRscpt->AddText("MPI,ISR,FSR = on");

    dRscpt->Draw();

    TString cname(title); TString c2name(title); TString c3name(title);
    cname.Append(".pdf"); c2name.Append("_lowpt.pdf"); c3name.Append("_dR.pdf");
    c->Print(cname);
    c2->Print(c2name);
    c3->Print(c3name);
    return;
}

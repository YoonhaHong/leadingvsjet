void typesofjet_drawing (int Rmode =7, TString event= "gg2qqbar" ){
    
    int eventmode = event.Contains("qqbar");
    TString inputpath;
    if(eventmode == 1) inputpath="./typesofjet_fromgg2qqbar";
    else inputpath="./typesofjet_fromall";

    TString Rsize; Rsize.Form("R%02d",Rmode);
    inputpath.Append(Rsize); 
    inputpath.Append(".root");
    
    TFile *f  = new TFile(inputpath, "open");
    TH2F * qpt = (TH2F *)gROOT->FindObject("quarkjet_particle_pt");
    TH2F * gpt = (TH2F *)gROOT->FindObject("quarkjet_particle_pt");
    TH2F * ept = (TH2F *)gROOT->FindObject("quarkjet_particle_pt");
  //  TH2F * eta = (TH2F *)gROOT->FindObject("quarkjet_particle_eta");
  //  TH2F * phi = (TH2F *)gROOT->FindObject("quarkjet_particle_phi");
  //  TH2F * dR = (TH2F *)gROOT->FindObject("quarkdr");


    TCanvas* c2 = new TCanvas("qpt","qpt",500,500); 
    TPad* c2pad = new TPad("c2pad","c2pad",0,0,1,1);
   // qpt->RebinX(2); qpt->RebinY(2);

    TString title;
    if(eventmode ==1) title = "gg2qqbar with bkg, ";
    else title = "HardQCD:all with bkg, ";
    
    if(Rmode==2) title.Append("R=0.2");
    else if(Rmode==7) title.Append("R=0.7");
    qpt->SetTitle(title);

    qpt->GetXaxis()->SetRangeUser(10,40);
    qpt->GetYaxis()->SetRangeUser(10,40);
    c2->cd(); c2pad->Draw();
    c2pad->cd(); 
    qpt->Draw("colz");
    
    TPaveText *qptscpt = new TPaveText(0.57,0.27,0.85,0.39,"NDC");
    qptscpt->AddText("MPI,ISR,FSR = on");

    qptscpt->SetFillColorAlpha(0,0);
    qptscpt->SetBorderSize(0);
    qptscpt->SetTextFont(42);
    qptscpt->Draw();



    return; 

    TString cname(title); TString c2name(title); TString c3name(title);
    cname.Append(".pdf"); c2name.Append("_lowpt.pdf"); c3name.Append("_dR.pdf");
    c2->Print(c2name);
    return;
}

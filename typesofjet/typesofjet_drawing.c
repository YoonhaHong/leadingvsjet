void typesofjet_drawing (int Rmode =7, TString event= "gg2qqbar" ){
   //"gg2qqbar" or "all" 
    int eventmode = event.Contains("qqbar");
    TString inputpath;
    if(eventmode == 1) inputpath="./typesofjet_fromgg2qqbar";
    else inputpath="./typesofjet_fromall";

    TString Rsize; Rsize.Form("R%02d",Rmode);
    inputpath.Append(Rsize); 
    inputpath.Append(".root");
    
    TFile *f  = new TFile(inputpath, "open");
    TH2F * qpt = (TH2F *)gROOT->FindObject("quarkjet_particle_pt");
    TH2F * gpt = (TH2F *)gROOT->FindObject("gluonjet_particle_pt");
    TH2F * ept = (TH2F *)gROOT->FindObject("elsejet_particle_pt");
  //  TH2F * eta = (TH2F *)gROOT->FindObject("quarkjet_particle_eta");
  //  TH2F * phi = (TH2F *)gROOT->FindObject("quarkjet_particle_phi");
  //  TH2F * dR = (TH2F *)gROOT->FindObject("quarkdr");

    gStyle->SetOptStat(11); //only hist name, entries

    TString title;
    if(eventmode ==1) title = "gg2qqbar with bkg, ";
    else title = "HardQCD:all with bkg, ";
    
    if(Rmode==2) title.Append("R=0.2");
    else if(Rmode==7) title.Append("R=0.7");
    TString qtitle(title); TString gtitle(title); TString etitle(title);

    TPaveText *script = new TPaveText(0.57,0.27,0.85,0.39,"NDC");
    script->AddText("MPI,ISR,FSR = on");
    script->SetFillColorAlpha(0,0);
    script->SetBorderSize(0);
    script->SetTextFont(42);

    //quark tagged 
    TCanvas* c1 = new TCanvas("qpt","qpt",500,500); 
    TPad* c1pad = new TPad("c1pad","c1pad",0,0,1,1);
    qtitle.Append(", quark tagged"); qpt->SetTitle(qtitle);
    
    qpt->GetXaxis()->SetRangeUser(10,40);
    qpt->GetYaxis()->SetRangeUser(10,40);
    c1->cd(); c1pad->Draw();
    c1pad->cd(); 
    qpt->Draw("colz");
    
    //gluon tagged
    TCanvas* c2 = new TCanvas("gpt","gpt",500,500); 
    TPad* c2pad = new TPad("c2pad","c2pad",0,0,1,1);
    gtitle.Append(", gluon tagged"); gpt->SetTitle(gtitle);

    gpt->GetXaxis()->SetRangeUser(10,40);
    gpt->GetYaxis()->SetRangeUser(10,40);
    c2->cd(); c2pad->Draw();
    c2pad->cd(); 
    gpt->Draw("colz");

    //else
    TCanvas* c3 = new TCanvas("ept","ept",500,500); 
    TPad* c3pad = new TPad("c3pad","c3pad",0,0,1,1);
    etitle.Append(", else"); ept->SetTitle(etitle);

    ept->GetXaxis()->SetRangeUser(10,40);
    ept->GetYaxis()->SetRangeUser(10,40);
    c3->cd(); c3pad->Draw();
    c3pad->cd(); 
    ept->Draw("colz");

   // return;
    //print to pdf
    qtitle.Append(".pdf"); gtitle.Append(".pdf"); etitle.Append(".pdf");
    c1->Print(qtitle); c2->Print(gtitle); c3->Print(etitle);
    return;
}

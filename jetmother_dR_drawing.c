void jetmother_dR_drawing(TString inputpath="./jetparticlegg2ggR02.root")
{
    int mode;
    if(inputpath.Contains("qq")) mode=1;
    else mode=0;

    int Rmode;
    if(inputpath.Contains("R02")) Rmode=2;
    else if(inputpath.Contains("R07")) Rmode=7;
    
    int MIF=0;
    if(inputpath.Contains("MIF")) MIF=1;

    TFile *f  = new TFile(inputpath, "open");
    TH2F * dR = (TH2F *)gROOT->FindObject("dr");

    TString title;
    if(MIF==1) title="with bkg, ";
    if(mode==0)  title.Append("gluon jets, ");
    else         title.Append("quark jets, ");
    
    if(Rmode==2) title.Append("R=0.2");
    else if(Rmode==7) title.Append("R=0.7");


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
    if(MIF==1) dRscpt->AddText("MPI,ISR,FSR = on");
    else dRscpt->AddText("MPI,ISR,FSR = off");
    dRscpt->Draw();

    TString cname(title); TString c2name(title); TString c3name(title);
    c3name.Append("_dR.pdf");
    c3->Print(c3name);
    return;
}

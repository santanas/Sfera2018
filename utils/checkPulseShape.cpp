#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"




int main() {

  TFile* file = TFile::Open("prova.root");
  TTree* tree = (TTree*)file->Get("tree");

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  c1->cd();

  float pshape[128][1024];

  tree->SetBranchAddress( "pshape", &pshape );

  tree->GetEntry(0);

  TH1D* h1 = new TH1D("h1", "", 1024, 0., 1024. );


  for( unsigned i=0; i<1024; ++i ) {

    h1->SetBinContent( i+1, pshape[0][i] );

  }


  h1->Draw();

  c1->SaveAs("pshape.eps");
  c1->SaveAs("pshape.pdf");

  return 0;

}

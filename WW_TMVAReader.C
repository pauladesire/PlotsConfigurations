#include "LatinoAnalysis/MultiDraw/interface/TTreeFunction.h"
#include "LatinoAnalysis/MultiDraw/interface/FunctionLibrary.h"
#include <iostream>

#include <TMVA/Reader.h>

using namespace std;

class ww_top_bdt_2j : public multidraw::TTreeFunction {
public:
  ww_top_bdt_2j();

  char const* getName() const override { return "ww_top_bdt_2j"; }
  TTreeFunction* clone() const override { return new ww_top_bdt_2j(); }

  unsigned getNdata() override { return 1; }
  double evaluate(unsigned) override;

protected:
  void bindTree_(multidraw::FunctionLibrary&) override;

  FloatArrayReader* Lepton_pt{};
  FloatValueReader* mll{};
  FloatValueReader* mth{}; 
  FloatValueReader* drll{};
  FloatValueReader* dphillmet{};
  FloatValueReader* mtw1{};
  FloatValueReader* mtw2{};
  FloatValueReader* pTWW{};
  FloatValueReader* pTHjj{};
  FloatValueReader* mjj{};
  FloatValueReader* detajj{};
  FloatValueReader* dphijj{};
  FloatValueReader* dphijet2met{};
  FloatValueReader* dphijjmet{};
  FloatValueReader* dphilep1jet1{};
  FloatValueReader* dphilep1jet2{};
  FloatValueReader* mindetajl{};
  UIntValueReader* nCleanJet{};
  FloatArrayReader* CleanJet_pt{};
  FloatArrayReader* CleanJet_eta{};
  FloatArrayReader* Jet_btagDeepB{};
  IntArrayReader* CleanJet_jetIdx{};

  // Variables fed into the BDT
  float mll_;
  float mjj_; 
  float mth_;
  float pt0_;
  float pt1_;
  float detajj_; 
  float Jet_btagDeepB_CleanJet_jetIdx_0_;                                                                                                   
  float Jet_btagDeepB_CleanJet_jetIdx_1_; 
  float mindetajl_;                                                                                                                         

  TMVA::Reader *reader = new TMVA::Reader();
};

ww_top_bdt_2j::ww_top_bdt_2j() : TTreeFunction() 
{
  reader->AddVariable("mll", &mll_);
  reader->AddVariable("mjj", &mjj_);     
  reader->AddVariable("mth", &mth_);                 
  reader->AddVariable("Lepton_pt[0]", &pt0_);  
  reader->AddVariable("Lepton_pt[1]", &pt1_); 
  reader->AddVariable("detajj", &detajj_); 
  reader->AddVariable("Alt$(Jet_btagDeepB[CleanJet_jetIdx[0]],-2)", &Jet_btagDeepB_CleanJet_jetIdx_0_);                                     
  reader->AddVariable("Alt$(Jet_btagDeepB[CleanJet_jetIdx[1]],-2)", &Jet_btagDeepB_CleanJet_jetIdx_1_);  
  reader->AddVariable("mindetajl", &mindetajl_);     

  reader->BookMVA("BDT","/afs/cern.ch/work/p/pdesirev/private/CMSSW_10_6_4/src/PlotsConfigurations/Configurations/WW/Full2016_v7/dataset/weights/WW_TMVAClassification_BDT.weights.xml");

}

double  ww_top_bdt_2j::evaluate(unsigned)
{
  mll_ = *mll->Get();
  mjj_ = *mjj->Get();      
  mth_ = *mth->Get();      
  pt0_ = Lepton_pt->At(0); 
  pt1_ = Lepton_pt->At(1);        
  detajj_ = *detajj->Get();
  mindetajl_ = *mindetajl->Get();

  unsigned njet = *nCleanJet->Get();   
  int jetIdx0 = CleanJet_jetIdx->At(0);
  int jetIdx1 = CleanJet_jetIdx->At(1);
  
  Jet_btagDeepB_CleanJet_jetIdx_0_ = jetIdx0 >= 0 ? Jet_btagDeepB->At(jetIdx0) : -2;
  Jet_btagDeepB_CleanJet_jetIdx_1_ = jetIdx1 >= 0 ? Jet_btagDeepB->At(jetIdx1) : -2;
  


double classifier = reader->EvaluateMVA("BDT");
  //double classifier = pt1_ + mll_ + drll_ + dphillmet_ + mtw1_ + mtw2_ + pTWW_ + pTHjj_ + mjj_ + detajj_ + dphijj_ + dphijet2met_ + dphijjmet_ + dphilep1jet1_ + dphilep1jet2_ + mindetajl_ + CleanJet_pt_0_ + CleanJet_pt_1_ + CleanJet_eta_0_ + CleanJet_eta_1_ + Jet_btagDeepB_CleanJet_jetIdx_0_ +Jet_btagDeepB_CleanJet_jetIdx_1_;

  return classifier;
}

void
ww_top_bdt_2j::bindTree_(multidraw::FunctionLibrary& _library)
{
  _library.bindBranch(Lepton_pt,"Lepton_pt");
  _library.bindBranch(mll,"mll");
  _library.bindBranch(mth,"mth");     
  _library.bindBranch(drll,"drll");
  _library.bindBranch(dphillmet,"dphillmet");
  _library.bindBranch(mtw1,"mtw1");
  _library.bindBranch(mtw2,"mtw2");
  _library.bindBranch(pTWW,"pTWW");
  _library.bindBranch(pTHjj,"pTHjj");
  _library.bindBranch(mjj,"mjj");
  _library.bindBranch(detajj,"detajj");
  _library.bindBranch(dphijj,"dphijj");
  _library.bindBranch(dphijet2met,"dphijet2met");
  _library.bindBranch(dphijjmet,"dphijjmet");
  _library.bindBranch(dphilep1jet1,"dphilep1jet1");
  _library.bindBranch(dphilep1jet2,"dphilep1jet2");
  _library.bindBranch(mindetajl,"mindetajl");
  _library.bindBranch(nCleanJet,"nCleanJet");
  _library.bindBranch(CleanJet_pt,"CleanJet_pt");
  _library.bindBranch(CleanJet_eta,"CleanJet_eta");
  _library.bindBranch(Jet_btagDeepB,"Jet_btagDeepB");
  _library.bindBranch(CleanJet_jetIdx,"CleanJet_jetIdx");
  
}

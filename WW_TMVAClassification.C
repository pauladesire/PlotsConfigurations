//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  root -l VH2j_TMVAClassification.C\(\"BDT\"\)
//  root -l VH2j_TMVAClassification.C\(\"BDT,BDT4,BDT6,BDT12\"\)
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TObjString.h"
#include "TPluginManager.h"
#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"

#include "TMVA/DataLoader.h"
#include "TMVA/Factory.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/Tools.h"


// User defined function

//#include "/afs/cern.ch/user/p/piedra/work/CMSSW_projects/CMSSW_10_2_15_patch2/src/PlotsConfigurations/Configurations/VH2j/Full2016_nanoAODv4/detaljmin.C"



void WW_TMVAClassification(TString myMethodList = "") 
{
  // Load the library
  TMVA::Tools::Instance();

  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;

  Use["BDT"]   = 1;  // Uses Adaptive Boost
  Use["BDT4"]  = 0;  // Uses Adaptive Boost
  Use["BDT6"]  = 0;  // Uses Adaptive Boost
  Use["BDT12"] = 0;  // Uses Adaptive Boost

  if (myMethodList != "") {

    for (std::map<std::string,int>::iterator it=Use.begin(); it!=Use.end(); it++) it->second = 0;

    std::vector<TString> mlist = TMVA::gTools().SplitString(myMethodList, ',');

    for (UInt_t i=0; i<mlist.size(); i++) {

      std::string regMethod(mlist[i]);

      if (Use.find(regMethod) == Use.end()) {

	std::cout << " Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;

	for (std::map<std::string,int>::iterator it=Use.begin(); it!=Use.end(); it++) std::cout << it->first << " ";

	std::cout << std::endl;

	return;
      }

      Use[regMethod] = 1;
    }
  }


  // Input and output files
  //----------------------------------------------------------------------------
  TString workdir = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Summer16_102X_nAODv7_Full2016v7/MCl1loose2016v7__MCCorr2016v7__l2loose__l2tightOR2016v7/";

  TString outfileName("WW_TMVAClassification.root");

  TFile* outputFile = TFile::Open(outfileName, "recreate");


  // Create the factory object. The first argument is the base of the name of all the weight files
  //----------------------------------------------------------------------------
  TString factoryName("WW_TMVAClassification");

  TMVA::Factory* factory = new TMVA::Factory(factoryName, outputFile,
					     "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification");

  TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

  dataloader->AddVariable("mll",          'F');
  dataloader->AddVariable("mjj",          'F');
  dataloader->AddVariable("mth",          'F');
  dataloader->AddVariable("Lepton_pt[0]", 'F');
  dataloader->AddVariable("Lepton_pt[1]", 'F');
  dataloader->AddVariable("detajj",       'F');
  //dataloader->AddVariable("detaljmin:=detaljmin(Lepton_eta[0],Lepton_eta[1],CleanJet_eta[0],CleanJet_eta[1])", 'F');
  dataloader->AddVariable("Alt$(Jet_btagDeepB[CleanJet_jetIdx[0]],-2)", 'F'); 
  dataloader->AddVariable("Alt$(Jet_btagDeepB[CleanJet_jetIdx[1]],-2)", 'F');
  dataloader->AddVariable("mindetajl", 'F');

  // Input files
  //----------------------------------------------------------------------------
  std::vector<TFile*> InputFiles_signal;
  std::vector<TFile*> InputFiles_background;

  InputFiles_signal.clear();
  InputFiles_background.clear();

  for (UInt_t k=0; k<4; k++) {

    if (k < 1) InputFiles_signal.push_back(TFile::Open(Form("%s/nanoLatino_WWTo2L2Nu__part%d.root",      workdir.Data(), k)));  
    if (k < 1) InputFiles_signal.push_back(TFile::Open(Form("%s/nanoLatino_GluGluWWTo2L2Nu_MCFM__part%d.root",      workdir.Data(), k)));  

    if (k < 4) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_TTTo2L2Nu__part%d.root", workdir.Data(), k)));
    if (k < 2) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_ST_s-channel__part%d.root", workdir.Data(), k)));
    if (k < 4) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_ST_t-channel_antitop__part%d.root", workdir.Data(), k)));
    if (k < 4) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_ST_t-channel_top__part%d.root", workdir.Data(), k)));
    if (k < 4) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_ST_tW_antitop__part%d.root", workdir.Data(), k)));
    if (k < 4) InputFiles_background.push_back(TFile::Open(Form("%s/nanoLatino_ST_tW_top__part%d.root", workdir.Data(), k))); 
 }


  // Apply cuts on the signal and background samples (can be different)
  //----------------------------------------------------------------------------
  TCut mycuts;
  TCut mycutb;

  mycuts = "Lepton_pdgId[0]*Lepton_pdgId[1] == -11*13 && Lepton_pt[0] > 25. && Lepton_pt[1] > 25.   && mll > 20  && Sum$(CleanJet_pt > 30) >= 2";

  //  mycuts = "PuppiMET_pt > 20			 \
  //          && Lepton_pdgId[0]*Lepton_pdgId[1] == -11*13	\
		//          && Lepton_pt[0] > 25. \
  //&& Lepton_pt[1] > 25.   \
      //          && nLepton >= 2		\
		    //     && Alt$(Lepton_pt[2],0) < 10. \
  // && mll > 20					\
	      //&& Sum$(CleanJet_pt > 30) >= 2";

  mycutb = mycuts;

  
  // Create factory for signal and background samples
  double tmpWeight = 1.;

  for (UInt_t i=0; i<InputFiles_signal.size(); ++i) {
    TTree* tmpsTree = (TTree*)InputFiles_signal.at(i)->Get("Events");
    dataloader->AddSignalTree(tmpsTree, tmpWeight);
  }

  for (UInt_t k=0; k<InputFiles_background.size(); ++k) {
    TTree* tmpbTree = (TTree*)InputFiles_background.at(k)->Get("Events");
    dataloader->AddBackgroundTree(tmpbTree, tmpWeight);
  }

//dataloader->SetSignalWeightExpression    ("XSWeight*GenLepMatch2l*SFweight2l*bPogSF_CMVAL*LepCut2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*LepSF2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*METFilter_MC");
//dataloader->SetBackgroundWeightExpression("XSWeight*GenLepMatch2l*SFweight2l*bPogSF_CMVAL*LepCut2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*LepSF2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*METFilter_MC");
  //dataloader->SetSignalWeightExpression    ("XSWeight");
  //dataloader->SetBackgroundWeightExpression("XSWeight");

//dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random::SplitSeed=10:NormMode=None:!V");
//dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "nTrain_Signal=2404:nTrain_Background=11671:SplitMode=Block::SplitSeed=10:NormMode=EqualNumEvents");
//dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "SplitMode=Alternate::SplitSeed=10:NormMode=EqualNumEvents");
//dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "SplitMode=Random:NormMode=NumEvents:!V");
 dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "SplitMode=Random::SplitSeed=10:NormMode=EqualNumEvents");


  // Book MVA methods
  //----------------------------------------------------------------------------
  if (Use["BDT"]) factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
				      "!H:!V:NTrees=250:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=20");

  if (Use["BDT4"]) factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT4",
				       "!H:!V:NTrees=800:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=20");

  if (Use["BDT6"]) factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT6",
				       "!H:!V:NTrees=500:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500");

  if (Use["BDT12"]) factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT12",
					"!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.2:SeparationType=GiniIndex:nCuts=20");


  // Now you can tell the factory to train, test, and evaluate the MVAs
  //----------------------------------------------------------------------------
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();    


  // Save the output
  //----------------------------------------------------------------------------
  outputFile->Close();

  delete factory;
  delete dataloader;

  
  // Launch the GUI for the root macros
  //----------------------------------------------------------------------------
  if (!gROOT->IsBatch()) TMVA::TMVAGui(outfileName);
}

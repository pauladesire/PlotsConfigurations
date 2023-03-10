# Latinos code
### Initiate virtual machine
<p> ssh -Y pdesirev@lxplus7.cern.ch </p>

### Submit failed jobs
<p> condor_submit ggWW.14/mkShapes__WW__ALL__ggWW.14.jds </p>
<p> for i in */*.jid; do condor_submit ${i/jid/jds}; done </p>

### Enter git
<p> eval "$(ssh-agent -s)" </p>
<p> ssh-add ~/.ssh/gitkey </p>
<p> ssh-add -l </p>

### Madgraph
<i> Run Madgraph </i>
<p> python2 ./bin/mg5_amc </p>
<p> import model ALP </p>
<p> define multiparticle l- = e- mu- ta- </p>
<p> define multiparticle l+ = e+ mu+ ta+ </p>
<p> generate p p > w+ w-, w+ > l+ vl, w- > l- vl~ </p>
<p> output XXX </p>
<p> launch </p>
<i> Latino Trees compile step </i>
<p> c++ -o ntupleMaker.exe `root-config --cflags` ntupleMaker.cpp `root-config --libs`</p>
<i> Latino Trees execute: Produces a root file from events <i>
<p> ./ntupleMaker.exe ../../madgraph/MG5/MG5_aMC_v2_0_1/ma_0p001_CW_0p25Events/run_01/unweighted_events.lhe   ma0p001_CW_0p25.root </p>
 
### Analysis Steps:
<i> Run the files </i>
<p> mkShapesMulti.py --pycfg=configuration.py --doBatch=1 --batchSplit=Samples,Files --batchQueue=workday </p>
<i> Merge the files </i>
<p> mkShapesMulti.py --pycfg=configuration.py --doHadd=1 --batchSplit=Samples,Files --doNotCleanup --nThreads=10  </p>
<i> Do the plots </i>
<p> mkPlot.py --inputFile=rootFile/plots_WW.root --minLogC=0.01 --minLogCratio=0.01 --maxLogC=1000 --maxLogCratio=1000 --showIntegralLegend=1  </p>

### Datacards
<i> Create datacards </i>
<p> mkDatacards.py --pycfg=configuration.py --inputFile=rootFile/plots_WW.root </p>
<i> Create a proper combine enviroment </i>
<p> cd ../../../../../../../CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/ </p>
<p> cmsenv </p>
<p> cd - </p>
<i> Combine the datacards. The CR should always be defined based on the events datacard, but the signal one can change </i>
<p> combineCards.py ww_em_0j/events/datacard.txt ww_em_0j_dytt/events/datacard.txt ww_em_0j_top/events/datacard.txt > datacard_combined.txt </p>
<p> text2workspace.py datacard_combined.txt -m 125 </p>

### Fix signal stregth (r=1) systematic uncertainties
<i> Obtain value </i>
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 --expectSignal=1 -t -1 datacard_combined.txt -m 125 -n mytest > resultR1.txt </p>
<i> Obtain impacts and plot them </i>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacards/datacard_combined.root -m 125 -t -1 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Signal strength (r)
<i> Obtain value </i>
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 datacard_combined.txt -m 125 -n mytest > resultR.txt </p>
<i> Obtain impacts and plot them </i>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Upper limits (for non SM)
<p> combine -M AsymptoticLimits datacard.txt </p>
 <p> If you want to do it blinded, include options --noFitAsimov and --run blind </p>

### Likelihood scan
<i> Obtain the likelihood to the case that has been forced to have r=1 (for example) </i>
<p> combine -M MultiDimFit datacard_combined.txt -m 125 --expectSignal=1 -t -1 --algo=grid --points 100 --setParameterRanges r=-7,7 -n "_MyScan" </p>
<p> wget https://raw.githubusercontent.com/latinos/PlotsConfigurations/master/Configurations/ggH/scripts/drawNLL.C </p>
<p> root -l higgsCombine_MyScan.MultiDimFit.mH125.root drawNLL.C </p>

## Enter the rootfile
<p> root -l rootFile/plots_WW.root </p>
<p> ww_em->cd() </p>
<p> events->cd() </p>
<p> histo_WW>GetBinContent(1) </p>

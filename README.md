# WW-Full2016_v7

### Analysis Steps: 
<p> mkShapesMulti.py --pycfg=configuration.py --doBatch=1 --batchSplit=Samples,Files --batchQueue=workday </p>
<p> mkShapesMulti.py --pycfg=configuration.py --doHadd=1 --batchSplit=Samples,Files --doNotCleanup --nThreads=10  </p>
<p> mkPlot.py --inputFile=rootFile/plots_WW.root --minLogC=0.01 --minLogCratio=0.01 --maxLogC=1000 --maxLogCratio=1000 --showIntegralLegend=1  </p>

### Datacards
<p> mkDatacards.py --pycfg=configuration.py --inputFile=rootFile/plots_WW.root </p>
<p> cd ../../../../../../../CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/ </p>
<p> cmsenv </p>
<p> cd - </p>
<p> combineCards.py ww_em_0j/events/datacard.txt ww_em_0j_dytt/events/datacard.txt ww_em_0j_top/events/datacard.txt > datacard_combined.txt </p>
<p> text2workspace.py datacard_combined.txt -m 125 </p>

### Fix signal stregth (r=1)
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 --expectSignal=1 -t -1 datacard_combined.txt -m 125 -n mytest > resultR1.txt </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacards/datacard_combined.root -m 125 -t -1 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Fix mu experimental (r)
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 datacard_combined.txt -m 125 -n mytest > resultR.txt </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Likelihood scan
<p> combine -M MultiDimFit datacard_combined.txt -m 125 --expectSignal=1 -t -1 --algo=grid --points 100 --setParameterRanges r=-7,7 -n "_MyScan" </p>
<p> wget https://raw.githubusercontent.com/latinos/PlotsConfigurations/master/Configurations/ggH/scripts/drawNLL.C </p>
<p> root -l higgsCombine_MyScan.MultiDimFit.mH125.root drawNLL.C </p>

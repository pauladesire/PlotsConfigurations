# Latinos code

### Analysis Steps:
<i> Run the files </i>
<p> mkShapesMulti.py --pycfg=configuration.py --doBatch=1 --batchSplit=Samples,Files --batchQueue=workday </p>
2. Merge the files
<p> mkShapesMulti.py --pycfg=configuration.py --doHadd=1 --batchSplit=Samples,Files --doNotCleanup --nThreads=10  </p>
3. Do the plots
<p> mkPlot.py --inputFile=rootFile/plots_WW.root --minLogC=0.01 --minLogCratio=0.01 --maxLogC=1000 --maxLogCratio=1000 --showIntegralLegend=1  </p>

### Datacards
1. Create datacards
<p> mkDatacards.py --pycfg=configuration.py --inputFile=rootFile/plots_WW.root </p>
2. Create a proper combine enviroment
<p> cd ../../../../../../../CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/ </p>
<p> cmsenv </p>
<p> cd - </p>
3. Combine the datacards. The CR should always be defined based on the events datacard, but the signal one can change
<p> combineCards.py ww_em_0j/events/datacard.txt ww_em_0j_dytt/events/datacard.txt ww_em_0j_top/events/datacard.txt > datacard_combined.txt </p>
<p> text2workspace.py datacard_combined.txt -m 125 </p>

### Fix signal stregth (r=1) systematic uncertainties
1. Obtain value
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 --expectSignal=1 -t -1 datacard_combined.txt -m 125 -n mytest > resultR1.txt </p>
2. Obtain impacts and plot them
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacard_combined.root -m 125 -t -1 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts --expectSignal=1 -d datacards/datacard_combined.root -m 125 -t -1 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Signal strength (r)
1. Obtain value
<p> combine -M FitDiagnostics --rMin=-4 --rMax=7 datacard_combined.txt -m 125 -n mytest > resultR.txt </p>
2. Obtain impacts and plot them
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doInitialFit --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 --doFits --robustFit 1 </p>
<p> combineTool.py -M Impacts -d datacard_combined.root -m 125 -o impacts.json </p>
<p> plotImpacts.py -i impacts.json -o impacts </p>

### Likelihood scan
1. Obtain the likelihood to the case that has been forced to have r=1 (for example)
<p> combine -M MultiDimFit datacard_combined.txt -m 125 --expectSignal=1 -t -1 --algo=grid --points 100 --setParameterRanges r=-7,7 -n "_MyScan" </p>
<p> wget https://raw.githubusercontent.com/latinos/PlotsConfigurations/master/Configurations/ggH/scripts/drawNLL.C </p>
<p> root -l higgsCombine_MyScan.MultiDimFit.mH125.root drawNLL.C </p>

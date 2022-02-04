# WW-Full2016_v7

### Analysis Steps: 
<p> mkShapesMulti.py --pycfg=configuration.py --doBatch=1 --batchSplit=Samples,Files --batchQueue=longlunch </p>
<p> mkShapesMulti.py --pycfg=configuration.py --doHadd=1 --batchSplit=Samples,Files --doNotCleanup --nThreads=10  </p>
<p> mkPlot.py --inputFile=rootFile/plots_WW.root --minLogC=0.01 --minLogCratio=0.01 --maxLogC=1000 --maxLogCratio=1000 --showIntegralLegend=1  </p>

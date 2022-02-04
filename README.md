# W+W- analysis 

# Produce a valid VOMS proxy

    voms-proxy-init -voms cms -rfc --valid 168:0
    cmsenv


# Test running locally in one file 

    mkShapesMulti.py --inputDir=/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/ --treeName=Events -S samples_onefile.py


# Produce histograms

    mkShapesMulti.py --inputDir=/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/ --doBatch=True --batchQueue=workday --batchSplit=Samples,Files --treeName=


# Check job status

    condor_q

And wait until all jobs have finished.

# Resubmit failed jobs

cd $HOME/scripts/jobs/mkShapes__ggH_SF_2016_v7/

for i in *jid; do condor_submit ${i/jid/jds}; done

cd -

# Group (hadd) histograms

   mkShapesMulti.py --pycfg=configuration.py --doHadd=1 --batchSplit=Samples,Files --doNotCleanup --nThreads=8


# Draw distributions

mkPlot.py --inputFile=rootFile/plots_WW.root --minLogC=0.01 --minLogCratio=0.01 --maxLogC=1000 --maxLogCratio=1000 --showIntegralLegend=1


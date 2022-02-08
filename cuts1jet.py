# cuts

#cuts = {}

supercut = 'Lepton_pdgId[0]*Lepton_pdgId[1] == -11*13 \
            && Lepton_pt[0] > 25. \
            && Lepton_pt[1] > 25. \
            && (nLepton >= 2 && Alt$(Lepton_pt[2],0) < 10.) \
'

cuts['ww_em'] = 'mll > 20 \
                 && PuppiMET_pt > 20. \
                 && Alt$(CleanJet_pt[0], 0) > 30. \
                 && Alt$(CleanJet_pt[1], 0) < 30. \
                 && ptll > 30 \
                 && mpmet > 20 \
                 && bVeto \
'      

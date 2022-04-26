# cuts

#cuts = {}

supercut = 'Lepton_pdgId[0]*Lepton_pdgId[1] == -11*13 \
            && Lepton_pt[0] > 25. \
            && Lepton_pt[1] > 25. \
            && (nLepton >= 2 && Alt$(Lepton_pt[2],0) < 10.) \
'
cuts['top_1j'] = 'mll > 20 \
                 && PuppiMET_pt > 20. \
                 && Alt$(CleanJet_pt[0], 0) > 30. \
                 && Alt$(CleanJet_pt[1], 0) < 30. \
                 && ptll > 30 \
                 && mpmet > 20 \
                 && bReq \
'

cuts['top_0j'] = 'mll > 20 \
                 && PuppiMET_pt > 20. \
                 && Alt$(CleanJet_pt[0], 0) < 30. \
                 && ptll > 30 \
                 && mpmet > 20 \
                 && Sum$(CleanJet_pt > 20. && Jet_btagDeepB[CleanJet_jetIdx] > 0.2217) >= 1 \
'

cuts['top_2j'] = 'mll > 20 \
                 && PuppiMET_pt > 20. \
                 && Alt$(CleanJet_pt[0], 0) > 30. \
                 && Alt$(CleanJet_pt[1], 0) > 30. \
                 && Alt$(CleanJet_pt[2], 0) < 30. \
                 && bReq \
'


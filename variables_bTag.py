# variables

#variables = {}
    
#'fold' : # 0 = not fold (default), 1 = fold underflowbin, 2 = fold overflow bin, 3 = fold underflow and overflow
   
# Tuning for shape analysis

variables['events']  = {   'name': '1',      
                        'range' : (1,0,2),  
                        'xaxis' : 'events', 
                         'fold' : 3
                        }

variables['bTag1'] = {     'name': 'Alt$(Jet_btagDeepB[CleanJet_jetIdx[0]],-2)',
                           'range':(30,-2,1),
                           'xaxis': 'bTag1',
                           'fold': 3
                       }

variables['bTag2'] = {     'name': 'Alt$(Jet_btagDeepB[CleanJet_jetIdx[1]],-2)',
       	       	       	   'range':(30,-2,1),
       	       	       	   'xaxis': 'bTag2',
       	       	       	   'fold': 3
       	       	       }

#variables['mT2'] = {     'name'  : 'mT2',
#                          'range' : (25,0,250),
#                          'xaxis' : 'm_{T}^{2}',
#                          'fold'  : 3
#                          }

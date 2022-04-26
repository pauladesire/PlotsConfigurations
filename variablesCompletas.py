# variables

#variables = {}
    
#'fold' : # 0 = not fold (default), 1 = fold underflowbin, 2 = fold overflow bin, 3 = fold underflow and overflow
   
# Tuning for shape analysis

variables['events']  = {   'name': '1',      
                        'range' : (1,0,2),  
                        'xaxis' : 'events', 
                         'fold' : 3
                        }


variables['mth_control']  = {   'name': 'mth',            #   variable name    
                        'range' : (50,0,1000),     #   variable range
                        'xaxis' : 'm_{T}^{\ell\ell} [GeV]',  #   x axis name
                        'fold' : 3
                        }

variables['dphijj'] = {   'name': 'dphijj',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{jj} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['detajj'] = {   'name': 'detajj',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta_{ETAjj}} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilljet'] = {   'name': 'dphilljet',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell\ell JET} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilljetjet'] = {   'name': 'dphilljetjet ',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell\ell JETJET} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilep1jet1'] = {   'name': 'dphilep1jet1',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell 1JET1} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilep1jet2'] = {   'name': 'dphilep1jet2',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell 1JET2} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilep2jet1'] = {   'name': 'dphilep2jet1',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell 2JET1} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphilep2jet2'] = {   'name': 'dphilep2jet2',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell 2JET2} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphijet1met'] = {   'name': 'dphijet1met',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{JET1MET} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['dphijet2met'] = {   'name': 'dphijet2met',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{JET2MET} [rad]',  #   x axis name
                          'fold' : 0
                          }
variables['pTHjj']  = {   'name': 'pTHjj',            #   variable name
                        'range' : (40,0,400),    #   variable range
                        'xaxis' : 'p_{THjj} [GeV]',  #   x axis name
                        'fold' : 3
                        }

variables['mll']  = {   'name': 'mll',
                        'range' : (40,0,400),
                        'xaxis' : 'm_{\ell\ell} [GeV]',
                        'fold' : 3
                        }

variables['mjj'] = {     'name'  : 'mjj',            #   variable name    
                          'range' : (50,0,1000),    #   variable range
                          'xaxis' : 'm_{jj}',  #   x axis name
                          'fold'  : 3
                          }

variables['drll_control'] = {     'name': 'drll',    
                          'range' : (50,0,5.0),
                          'xaxis' : '\Delta R_{\ell\ell}',
                          'fold'  : 0
                          }

variables['dphill'] = {   'name': 'dphill',            #   variable name    
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{\ell\ell} [rad]',  #   x axis name
                          'fold' : 0
                          }


variables['mtw2'] = {     'name'  : 'mtw2',    
                          'range' : (25,0,500),
                          'xaxis' : 'm_{T}^{W2}', 
                          'fold'  : 3
                          }

variables['mt2'] = {     'name'  : 'mt2',
                          'range' : (25,0,500),
                          'xaxis' : 'm_{T}^{2}',
                          'fold'  : 3
                          }

variables['njet']  = {   'name': 'njet',      
                         'range' : (10,0,10),  
                         'xaxis' : 'njet', 
                         'fold' : 0
                         }
                        
variables['ptll']  = {   'name': 'ptll',            #   variable name    
                         'range' : (40,0,200),    #   variable range
                         'xaxis' : 'p_{T}^{\ell\ell} [GeV]',  #   x axis name
                         'fold' : 3
                         }

variables['met']  = {   'name': 'PuppiMET_pt',            #   variable name    
                        'range' : (40,0,200),    #   variable range
                        'xaxis' : 'E_{T}^{miss} [GeV]',  #   x axis name
                        'fold' : 3
                        }

variables['mll']  = {   'name': 'mll',            
                        'range' : (40,0,400),     
                        'xaxis' : 'm_{\ell\ell} [GeV]',
                        'fold' : 3
                        }

variables['projpfmet']  = {   'name': 'projpfmet',
                        'range' : (40,0,400),
                        'xaxis' : 'E_{Tpro}^{miss} [GeV]',
                        'fold' : 0
                        }

variables['mpmet']  = {   'name': 'mpmet',
                        'range' : (40,0,200),
                        'xaxis' : 'min(E_{Tpro}^{miss}, TrackE_{Tpro}^{miss}) [GeV]',
                        'fold' : 3
                        }

variables['dphilmet'] = {   'name': 'dphilmet',            #   variable name
                          'range' : (20,0,3.2),    #   variable range
                          'xaxis' : '\Delta\Phi_{metl} [rad]',  #   x axis name
                          'fold' : 0
                          }

variables['pt1']  = {   'name': 'Lepton_pt[0]',            #   variable name    
                        'range' : (40,0,400),    #   variable range
                        'xaxis' : 'p_{T}^{1st lep} [GeV]',  #   x axis name
                        'fold' : 3
                        }

variables['pt2']  = {   'name': 'Lepton_pt[1]',            #   variable name    
                        'range' : (30,0,300),    #   variable range
                        'xaxis' : 'p_{T}^{2nd lep} [GeV]',  #   x axis name
                        'fold' : 3
                        }

variables['nvtx']  = {   'name': 'PV_npvsGood',      
                         'range' : (40,0,40),  
                         'xaxis' : 'nvtx', 
                         'fold' : 3
                         }
                        

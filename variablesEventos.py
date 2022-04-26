# variables

#variables = {}
    
#'fold' : # 0 = not fold (default), 1 = fold underflowbin, 2 = fold overflow bin, 3 = fold underflow and overflow
   
# Tuning for shape analysis

variables['events']  = {   'name': '1',      
                        'range' : (1,0,2),  
                        'xaxis' : 'events', 
                         'fold' : 3
                        }
#variables['dphill'] = {   'name': 'dphill',            #   variable name
#                          'range' : (20,0,3.2),    #   variable range
#                          'xaxis' : '\Delta\Phi_{\ell\ell} [rad]',  #   x axis name
#                          'fold' : 0
#                          }

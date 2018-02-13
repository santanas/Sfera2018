import numpy as np
from array import array
from ROOT import *


with open('Run_3_Data_1_29_2018_Ascii.dat') as f:
#with open('Run_00005_Data_1_26_2018_Ascii.dat') as f:


    outfile = TFile( 'prova.root', 'recreate' )
    tree = TTree('t', '')


    maxch = 128
    nch       = array( 'i', [ 0 ] )
    base      = array( 'f', maxch*[ 0. ] )
    vamp      = array( 'f', maxch*[ 0. ] )
    vcharge   = array( 'f', maxch*[ 0. ] )
    letime    = array( 'f', maxch*[ 0. ] )
    tetime    = array( 'f', maxch*[ 0. ] )
    ratecount = array( 'f', maxch*[ 0. ] )

    tree.Branch( 'nch'      , nch      , 'nch/I'           )
    tree.Branch( 'base'     , base     , 'base[nch]/F'     )
    tree.Branch( 'vamp'     , vamp     , 'vamp[nch]/F'     )
    tree.Branch( 'vcharge'  , vcharge  , 'vcharge[nch]/F'  )
    tree.Branch( 'letime'   , letime   , 'letime[nch]/F'   )
    tree.Branch( 'tetime'   , tetime   , 'tetime[nch]/F'   )
    tree.Branch( 'ratecount', ratecount, 'ratecount[nch]/F')

    nsamp = 1024
    pshape = np.zeros(nsamp*maxch).reshape(nsamp,maxch)

    tree.Branch( 'pshape', pshape, 'pshape[nch][nsamp]/F')


    lines=f.readlines()

    wasReadingEvent = False
    readyForPulseShape = False
    ch = -1

    for line in lines:

        if len(line.split('=== EVENT'))>1 and wasReadingEvent:

          print('in first if')
          tree.Fill()
          nch[0] = 0
          ch = -1
          #nch       = array( 'i', [ 0 ] )
          #base      = array( 'f', maxch*[ 0. ] )
          #vamp      = array( 'f', maxch*[ 0. ] )
          #vcharge   = array( 'f', maxch*[ 0. ] )
          #letime    = array( 'f', maxch*[ 0. ] )
          #tetime    = array( 'f', maxch*[ 0. ] )
          #ratecount = array( 'f', maxch*[ 0. ] )
          wasReadingEvent = False


        elif len(line.split('=== CH: '))>1:

          wasReadingEvent = True
          readyForPulseShape = True

          nch[0] += 1

          words = line.split(' ')


          ch         = int(words[2])
          ev         = words[4]
          fcr        = words[6]
          base     [ch] = float(words[8])
          vamp     [ch] = float(words[11])
          vcharge  [ch] = float(words[14])
          letime   [ch] = float(words[17])
          tetime   [ch] = float(words[20])
          ratecount[ch] = float(words[23])

        elif readyForPulseShape and ch>=0:
  
          myarray = np.fromstring(line, dtype=float, sep=' ')
          print(myarray)
          readyForPulseShape = False
   

    if wasReadingEvent:
      tree.Fill()

    outfile.Write()
    outfile.Close()

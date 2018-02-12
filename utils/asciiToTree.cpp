#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <fstream>
#include <string>




int main( int argc, char* argv[] ) {

  if( argc != 2 ) {

    std::cout << "USAGE: ./asciiToTree [filename]" << std::endl;
    exit(1);

  }

  std::string fileName(argv[1]);

  std::ifstream fs;
  fs.open(fileName.c_str());

  TFile* outfile = TFile::Open( "prova.root", "recreate" );
  TTree* tree = new TTree( "t", "" );

  int maxch = 128;
  int nch;
  float base     [128];
  float vamp     [128];
  float vcharge  [128];
  float letime   [128];
  float tetime   [128];
  float ratecount[128];

  tree->Branch( "nch"      , &nch     , "nch/I"           );
  tree->Branch( "base"     , base     , "base[nch]/F"     );
  tree->Branch( "vamp"     , vamp     , "vamp[nch]/F"     );
  tree->Branch( "vcharge"  , vcharge  , "vcharge[nch]/F"  );
  tree->Branch( "letime"   , letime   , "letime[nch]/F"   );
  tree->Branch( "tetime"   , tetime   , "tetime[nch]/F"   );
  tree->Branch( "ratecount", ratecount, "ratecount[nch]/F");


  std::string line;

  if( fs.good() ) {

    while( getline(fs,line) ) {

      //std::string delimiter = " ";
      //
      //size_t pos = 0;
      //std::vector<std::string> words;
      //std::string word;
      //while ((pos = line.find(delimiter)) != std::string::npos) {
      //    word = line.substr(0, pos);
      //    line.erase(0, pos + delimiter.length());
      //    words.push_back(word);
      //}
      //std::cout << "----" << std::endl;
      //std::cout << "w[0]: " << words[0] << std::endl;
      //std::cout << "w[1]: " << words[1] << std::endl;

    }

  }

  return 0;

}


/*

    OUTFILE = tfILE( 'PROVA.ROOT', 'RECREATE' )
    tree = TTree('t', '')



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

*/

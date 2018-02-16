#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>




int main( int argc, char* argv[] ) {

  if( argc != 2 ) {

    std::cout << "USAGE: ./asciiToTree [filename]" << std::endl;
    exit(1);

  }

  std::string fileName(argv[1]);

  std::ifstream fs(Form("../data/%s", fileName.c_str()));
  if( !fs.good() ) {
    std::cout << "-> No file called '" << fileName << "' found in '../data/'. Exiting." << std::endl;
    exit(1);
  }

  std::cout << "-> Opened ascii data file: " << fileName << std::endl;

  size_t pos = 0;
  std::string outfileName;
  if((pos = fileName.find(".")) != std::string::npos) {
    std::string prefix = fileName.substr(0, pos);
    outfileName = prefix + ".root";
  }

  TFile* outfile = TFile::Open( outfileName.c_str(), "recreate" );
  TTree* tree = new TTree( "tree", "" );


  int ev;
  int fcr;
  int nch;
  float base     [128];
  float vamp     [128];
  float vcharge  [128];
  float letime   [128];
  float tetime   [128];
  float ratecount[128];
  float pshape   [128][1024];

  tree->Branch( "ev"       , &ev      , "ev/I"            );
  tree->Branch( "fcr"      , &fcr     , "fcr/I"           );
  tree->Branch( "nch"      , &nch     , "nch/I"           );
  tree->Branch( "base"     , base     , "base[nch]/F"     );
  tree->Branch( "vamp"     , vamp     , "vamp[nch]/F"     );
  tree->Branch( "vcharge"  , vcharge  , "vcharge[nch]/F"  );
  tree->Branch( "letime"   , letime   , "letime[nch]/F"   );
  tree->Branch( "tetime"   , tetime   , "tetime[nch]/F"   );
  tree->Branch( "ratecount", ratecount, "ratecount[nch]/F");
  tree->Branch( "pshape"   , pshape   , "pshape[nch][1024]/F");


  std::string line;
  bool firstEvent = true;
  bool wasReadingEvent = false;
  bool readyForPulseShape = false;
  int ch = -1;


  if( fs.good() ) {

    std::cout << "-> Starting parsing file." << std::endl;

    while( getline(fs,line) ) {

      std::string delimiter = " ";
      size_t pos = 0;
      std::vector<std::string> words;
      std::string word;
      while ((pos = line.find(delimiter)) != std::string::npos) {
        word = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        words.push_back(word);
      }


      if( words[0]=="===" && words[1]=="EVENT" && wasReadingEvent ) {

        if( ev % 50 == 0 ) std::cout << "   event: " << ev << std::endl;

        if( !firstEvent )
          tree->Fill();
 
        nch = 0;
        ch = -1;
        wasReadingEvent = false;
        firstEvent = false;

      } else if( words[0]=="===" && words[1]=="CH:" ) {

        wasReadingEvent = true;
        readyForPulseShape = true;

        nch += 1;

        ch            = atoi(words[2] .c_str());
        ev            = atoi(words[4] .c_str());
        fcr           = atoi(words[6] .c_str());
        base     [ch] = atof(words[8] .c_str());
        vamp     [ch] = atof(words[11].c_str());
        vcharge  [ch] = atof(words[14].c_str());
        letime   [ch] = atof(words[17].c_str());
        tetime   [ch] = atof(words[20].c_str());
        ratecount[ch] = atof(words[23].c_str());


      } else if( readyForPulseShape && ch>=0 ) {
  
        for( unsigned i=0; i<words.size(); ++i ) 
          pshape[ch][i] = atof(words[i].c_str());

        readyForPulseShape = false;
   
      }

    } // while get lines

  } // if file is good

  if( wasReadingEvent )
    tree->Fill();


  fs.close();

  tree->Write();
  outfile->Close();

  std::cout << "-> Tree saved in: " << outfile->GetName() << std::endl;

  return 0;

}


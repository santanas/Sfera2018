# Welcome to the repository of Sfera2018

Change directory to `analysis` and there you will find two programs:
`asciToTree.cpp` is the program that reads an ascii measurements file and converts it to a ROOT TTree;
`checkPulseShape.cpp` will plot a single pulse shape, to check that everything is OK.

Compile `asciToTree.cpp` with the command `make asciToTree` and then execute it through `./asciToTree [fileName]`, where `fileName` needs to be a valid file in the `../data` directory, and needs to be formatted correctly. This is automatically the case if you are using an ascii file that was produced by the digitizer, with full pulse shape readout. An example of such file can be found in `../data/test_data_64ch.dat`, which is a file with one event and 64 channels read out from the digitizer; only the first channel is filled with a square wave, whereas the others are all noise.

The program will produce an output rootfile with name consistent with the input datafile.

You can check a single pulse shape by compiling the `checkPulseShape` program (`make checkPulseShape`) and then running `./checkPulseShape [rootFileName] [event] [channel]`.

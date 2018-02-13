# Welcome to the repository of Sfera2018

Change directory to `utils` and there you will find two programs:
`asciToTree.cpp` is the program that reads an ascii measurements file and converts it to a ROOT TTree;
`checkPulseShape.cpp` will plot a single pulse shape, to check that everything is OK.

Compile `asciToTree.cpp` with the command `make asciToTree` and then execute it through `./asciToTree [fileName]`, where `fileName` needs to be a valid file in the `../data` directory, and needs to be formatted correctly (this is automatically the case if you are using an ascii file that was produced by the digitizer, with full pulse shape readout).

The program will produce an output rootfile with name consistent with the input datafile.

You can check a single pulse shape by compiling the `checkPulseShape` program (`make checkPulseShape`) and then running `./checkPulseShape [rootFileName] [event] [channel]`.

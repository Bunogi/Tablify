#ifndef ARGUMENTS
#define ARGUMENTS
#include <tclap/CmdLine.h>

extern TCLAP::CmdLine cmd;

extern TCLAP::ValueArg<int> returnArg;

extern TCLAP::ValueArg<std::string> formatArg;

extern TCLAP::ValueArg<int> minWidthArg;
extern TCLAP::ValueArg<int> minHeightArg;

extern TCLAP::UnlabeledMultiArg<std::string> colArg;

#endif // ARGUMENTS


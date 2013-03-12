#include "Prefixspan.h"

/* Globals */
void Usage();
void Version();
void ParseParameters (int argc, char **argv);

vector<string> filenames;
bool           toggle_verbose       = false;
int            min_sup              = 1;    // minimum support for LCM
int            max_pat              = 0;    // maximum_itemset_size : default infinity;

int main(int argc, char **argv)
{
  Version();
  ParseParameters(argc, argv);
  
  Prefixspan prefixspan(min_sup, max_pat);
  prefixspan.run(filenames[0]);
  return 0;
}

/*****************************************************************************
 * Version
 ****************************************************************************/
void Version(){
  cerr << "PrefixSpan version 1.00 - Sequential Pattern Miner" << endl
       << "Written by Yasuo Tabei" << endl << endl;
}

/***************************************************************************
 * Usage
 ***************************************************************************/
void Usage(){
  cerr << endl
       << "Usage: prefixspan [OPTION]... INFILE" << endl << endl
       << "       where [OPTION]...  is a list of zero or more optional arguments" << endl
       << "             INFILE(s)    is the name of the input transaction database" << endl << endl
       << "Additional arguments (at most one input file may be specified):" << endl
       << "       -min_sup [minimum support]" << endl
       << "       -max_pat [maximum pattern]" << endl
       << endl;
  exit(0);
}

/*****************************************************************************
 * ParseParameters
 *****************************************************************************/
void ParseParameters (int argc, char **argv){
  if (argc == 1) Usage();
  filenames.clear();

  for (int argno = 1; argno < argc; argno++){
    if (argv[argno][0] == '-'){
      if      (!strcmp (argv[argno], "-version")){
	Version();
      }
      else if (!strcmp (argv[argno], "-verbose")) {
	toggle_verbose = true;
      }
      else if (!strcmp (argv[argno], "-min_sup")) {
	if (argno == argc - 1) cerr << "Must specify minimum support after -min_sup" << endl;
	min_sup = atoi(argv[++argno]);
      }
      else if (!strcmp (argv[argno], "-max_pat")) {
	if (argno == argc - 1) cerr << "Must specify miximum itemset size after -max_size" << endl;
	max_pat = atoi(argv[++argno]);
      }
    }
    else {
      filenames.push_back(argv[argno]);
    }
  }
}

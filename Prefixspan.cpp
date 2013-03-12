#include "Prefixspan.h"

/********************************************************************
 * Read file
 ********************************************************************/
void Prefixspan::read(const string &_filename, Pairdata &pairdata) {
  string       line;
  int          item;
  unsigned int id = 0;

  ifstream is(_filename.c_str());
  Transaction transaction;
  while (getline (is, line)) {
    transaction.second.clear();
    vector<unsigned int> &itemsets = transaction.second;
    istrstream istrs ((char *)line.c_str());

    while (istrs >> item) 
      itemsets.push_back(item);
    
    transaction.first = id++;
    
    pairdata.database.push_back(transaction);
    pairdata.indeces.push_back(0);
  }
}

/********************************************************************
 * Run prefixspan
 ********************************************************************/
void Prefixspan::run(const string &_filename)
{
  Pairdata pairdata;
  read(_filename, pairdata);
  project(pairdata);
}

/********************************************************************
 * Print frequent sequential patterns
 ********************************************************************/
void Prefixspan::print_pattern(Pairdata &projected) {
  for (vector<unsigned int>::iterator it = pattern.begin(); it != pattern.end(); it++) {
    cout << *it << " ";
  }

  cout << endl << "( ";
  for (vector<Transaction>::iterator it = projected.database.begin(); it != projected.database.end(); it++) {
    cout << it->first << " ";
  }
  cout << ") : " << projected.database.size() << endl;
}

/********************************************************************
 * Project database
 ********************************************************************/
void Prefixspan::project(Pairdata &projected) {
  if (projected.database.size() < min_sup)
    return;
  
  print_pattern(projected);

  if (max_pat != 0 && pattern.size() == max_pat)
    return;
  
  map<unsigned int, unsigned int> map_item;
  const vector<Transaction> &database = projected.database;
  for (unsigned int i = 0; i < database.size(); i++) {
    const vector<unsigned int> &itemset = database[i].second;
    for (unsigned int iter = projected.indeces[i]; iter < itemset.size(); iter++) 
      ++map_item[itemset[iter]];
  }

  Pairdata pairdata;
  vector<Transaction> &new_database = pairdata.database;
  vector<unsigned int> &new_indeces = pairdata.indeces;
  for (map<unsigned int, unsigned int>::iterator it_1 = map_item.begin(); it_1 != map_item.end(); it_1++) {
    for (unsigned int i = 0; i < database.size(); i++) {
      const Transaction &transaction = database[i];
      const vector<unsigned int> &itemset = transaction.second;
      for (unsigned int iter = projected.indeces[i]; iter < itemset.size(); iter++) {
	if (itemset[iter] == it_1->first) {
	  new_database.push_back(transaction);
	  new_indeces.push_back(iter + 1);
	  break;
	}
      }
    }

    pattern.push_back(it_1->first);
    project(pairdata);
    pattern.pop_back();
    pairdata.clear();
  }
}

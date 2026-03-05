#ifndef INDEXER_H
#define INDEXER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Indexer {
public:
    unordered_map<string, unordered_map<string, vector<int>>> invertedIndex;
    unordered_map<string, int> docLength;
    int totalDocs;

    void buildIndex(unordered_map<string, string>& documents);
};

#endif
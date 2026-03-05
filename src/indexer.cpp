#include "indexer.h"
#include <sstream>
#include <cctype>
#include <unordered_set>
using namespace std;

// Stopword list
unordered_set<string> stopwords = {"the", "is", "in", "at", "of", "on", "and", "a", "an", "to", "for", "with"};

void Indexer::buildIndex(unordered_map<string, string>& documents) {

    totalDocs=documents.size();

    for (auto& pair : documents) {

        string docID = pair.first;
        string content = pair.second;

        stringstream ss(content);
        string word;

        int wordCount=0;

        int position = 0;

        while (ss >> word) {

            for (char &c : word) {
                c = tolower(c);
            }

            // skip stopwords
            if (stopwords.find(word) != stopwords.end()) {
                continue;
            }

            invertedIndex[word][docID].push_back(position);

            wordCount++;
            position++;
        }

        docLength[docID] = wordCount;
    }
}
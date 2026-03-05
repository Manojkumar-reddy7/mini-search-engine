#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "indexer.h"
#include <cmath>
#include <iomanip>


using namespace std;

int main() {

    // STEP 1: Read Documents
    
    unordered_map<string, string> documents;

    vector<string> fileNames = {
        "data/doc1.txt",
        "data/doc2.txt",
        "data/doc3.txt",
        "data/doc4.txt",
        "data/doc5.txt"
    };

    for (string filePath : fileNames) {

        ifstream file(filePath);

        if (!file) {
            cout << "Cannot open file: " << filePath << endl;
            continue;
        }

        string content, line;

        while (getline(file, line)) {
            content += line + " ";
        }

        documents[filePath] = content;
    }

    
    // STEP 2: Build Inverted Index
    
    Indexer indexer; 
    indexer.buildIndex(documents);

   
    // STEP 3: Multi-word Search

    string query;

    cout << "\nEnter search query: ";
    getline(cin >> ws, query);

    // Detect phrase search
    bool phraseSearch = false;

    if (!query.empty() && query.front() == '"' && query.back() == '"') {
        phraseSearch = true;
        query = query.substr(1, query.size() - 2);
    }

    stringstream ss(query);
    string word;
    vector<string> queryWords;

    while (ss >> word) {

        // convert to lowercase
        for (char &c : word) {
            c = tolower(c);
        }

        queryWords.push_back(word);
    }



    if (phraseSearch && queryWords.size() >= 2) {

        cout << "\nPhrase Search Results:\n";

        string firstWord = queryWords[0];

        if (indexer.invertedIndex.find(firstWord) == indexer.invertedIndex.end()) {
            cout << "No matching documents found.\n";
            return 0;
        }

        for (auto &docPair : indexer.invertedIndex[firstWord]) {

            string docID = docPair.first;
            vector<int> positions = docPair.second;

            bool phraseFound = false;

            for (int pos : positions) {

                bool match = true;

                for (int i = 1; i < queryWords.size(); i++) {

                    string nextWord = queryWords[i];

                    auto wordIt = indexer.invertedIndex.find(nextWord);
                    if (wordIt == indexer.invertedIndex.end()) {
                        match = false;
                        break;
                    }

                    auto docIt = wordIt->second.find(docID);
                    if (docIt == wordIt->second.end()) {
                        match = false;
                        break;
                    }

                    vector<int>& nextPositions = docIt->second;

                    if (find(nextPositions.begin(), nextPositions.end(), pos + i) == nextPositions.end()) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    phraseFound = true;
                    break;
                }
            }

            if (phraseFound)
                cout << docID << endl;
        }

        return 0;
    }


    // STEP 4: Score Documents

    unordered_map<string, double> scores;

    for (string qWord : queryWords) {

        if (indexer.invertedIndex.find(qWord) != indexer.invertedIndex.end()) {

            int docsContainingWord = indexer.invertedIndex[qWord].size();

            double idf = log((double)indexer.totalDocs / docsContainingWord) + 1;

            for (auto &pair : indexer.invertedIndex[qWord]) {

                string docID = pair.first;
                int frequency = pair.second.size();

                double tf = (double)frequency / indexer.docLength[docID];

                scores[docID] += tf * idf;
            }
        }
    }

   
    // STEP 5: Display Results

    if (scores.empty()) {
        cout << "No matching documents found.\n";
        return 0;
    }

    vector<pair<string,double>> results(scores.begin(), scores.end());

    sort(results.begin(), results.end(),
         [](auto &a, auto &b) {
             return a.second > b.second;
         });

    cout << "\nSearch Results:\n";

    for (auto &pair : results) {
        cout << pair.first << " (score: " << fixed << setprecision(4) << pair.second << ")" << endl;
    }

    return 0;
}
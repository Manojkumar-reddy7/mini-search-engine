# Mini Search Engine (C++)

This project implements a mini search engine using C++.

Features
- Inverted Index
- TF-IDF Ranking
- Multi-word search
- Phrase search
- Stopword removal
- Case-insensitive search

Project Structure

mini-search-engine
│
├── data
│   ├── doc1.txt
│   ├── doc2.txt
│   ├── doc3.txt
│   ├── doc4.txt
│   └── doc5.txt
│
├── src
│   ├── main.cpp
│   ├── indexer.cpp
│   └── indexer.h

Compile

g++ -std=c++17 src/main.cpp src/indexer.cpp -o search.exe

Run

search.exe
# Mini Search Engine (C++)

This project implements a simple search engine in C++ using an inverted index and TF-IDF ranking to retrieve relevant documents.

## Features
- Inverted index construction
- TF-IDF based document ranking
- Multi-word query support
- Phrase search
- Stopword removal
- Case insensitive search

## Dataset
The project uses multiple text documents stored in the **data** folder.  
Each document contains text related to computer science topics such as machine learning, algorithms, and information retrieval.

## Source Code
The source files are located in the **src** folder.

- `main.cpp` – Handles reading documents, building the index, and running the search engine.
- `indexer.cpp` – Builds the inverted index and stores document statistics.
- `indexer.h` – Header file for the indexer class.

## How to Compile

Use g++ to compile the project:

g++ -std=c++17 src/main.cpp src/indexer.cpp -o search.exe

## How to Run

After compiling, run the executable:

.\search.exe

## Example Queries

machine learning  
"machine learning"  
search engines  
information retrieval
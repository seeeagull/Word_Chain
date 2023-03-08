//
// Created by seeeagull on 23-3-6.
//

#ifndef WORD_CHAIN_GRAPH_H
#define WORD_CHAIN_GRAPH_H

#include <string>
#include <memory>
#include <vector>
#include <deque>
#include <map>
#include "file_io.h"

class Graph {
    typedef std::shared_ptr<std::string> StringPointer;
public:
    Graph();
    ~Graph() = default;
    void AddWord(const StringPointer& word);
    void SetHead(char h);
    void setTail(char t);
    void SetBannedHead(char bh);
    void SetFileIO(FileIo* file_io);
    bool DetectLoop();
    void FindAllWordChains();
    void FindMostWordsChain();
    void FindMostLettersChain();
    void OutputAllWords();

private:
    bool DfsFindLoop(char now, std::vector<int>& visited);
    void DfsGetChains(char now, std::deque<StringPointer>& records);
    void FindMostWordsChainWithLoops();
    void FindMostWordsChainWithoutLoops();
    void FindMostLettersChainWithLoops();
    void FindMostLettersChainWithoutLoops();
    void Tarjan();

    struct Edge {
        StringPointer word;
        int length;
        char tar;
        bool used;
        explicit Edge(const StringPointer& word) : word(word) {
            used = false;
            length = word->length();
            tar = word->at(length - 1) - 'a';
        }
        bool operator < (const Edge &e) const {
            return length < e.length;
        }
        bool operator > (const Edge &e) const {
            return length > e.length;
        }
    };

    typedef std::shared_ptr<Edge> EdgePointer;

    std::vector<std::vector<EdgePointer>*> edges_{};
    std::vector<EdgePointer> self_loop_{};
    char head_ = 30;
    char tail_ = 30;
    char banned_head_ = 30;
    bool has_loop_ = false;
    FileIo* file_io_ = nullptr;
};

#endif //WORD_CHAIN_GRAPH_H

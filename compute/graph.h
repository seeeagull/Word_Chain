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
#include <stack>
#include <bitset>
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
    int FindAllWordChains();
    int FindLongestChain(bool weighted);
    void OutputAllWords();

private:
    bool DfsFindLoop(char now, std::vector<int>& visited);
    void DfsGetChains(char now, std::deque<StringPointer>& records);
    int FindLongestChainWithLoops(bool weighted);
    int FindLongestChainWithoutLoops(bool weighted);
    void Tarjan(char u, int& dfn_num, int& fa_num,
                std::vector<int>& dfn,
                std::vector<int>& low,
                std::stack<int>& stack,
                std::vector<bool>& instack,
                std::vector<int>& fa);

    struct State {
        std::bitset<100> passed_edges;
        char last_pos;
        explicit State(char pos) : last_pos(pos) {}
        bool operator < (const State &s) const {
            if (last_pos != s.last_pos) {
                return last_pos < s.last_pos;
            }
            for (int i = 0; i <= 99; ++i) {
                if (passed_edges[i] != s.passed_edges[i]) {
                    return passed_edges[i] < s.passed_edges[i];
                }
            }
            return false;
        }
        bool operator > (const State &s) const {
            if (last_pos != s.last_pos) {
                return last_pos > s.last_pos;
            }
            for (int i = 0; i <= 99; ++i) {
                if (passed_edges[i] != s.passed_edges[i]) {
                    return passed_edges[i] > s.passed_edges[i];
                }
            }
            return false;
        }
    };
    void DfsLongestChain(char u, State& cur,
                         std::map<State, std::pair<int, char>>& longest,
                         std::map<std::pair<char, char>, int>& pos,
                         std::vector<int>& fa);

    struct Edge {
        int id;
        StringPointer word;
        int length;
        char src;
        char tar;
        bool used;
        explicit Edge(int id, const StringPointer& word) : id(id), word(word) {
            used = false;
            length = word->length();
            src = word->at(0) - 'a';
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
    std::map<int, EdgePointer> edges_map_{};
    std::map<std::pair<char, char>, std::vector<std::pair<int, int>>> edges2_{};
    std::vector<EdgePointer> self_loop_{};
    int edges_num_ = 0;
    char head_ = 30;
    char tail_ = 30;
    char banned_head_ = 30;
    bool has_loop_ = false;
    FileIo* file_io_ = nullptr;
};

#endif //WORD_CHAIN_GRAPH_H

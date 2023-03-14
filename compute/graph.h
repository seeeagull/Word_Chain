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
    void SetTail(char t);
    void SetBannedHead(char bh);
    void SetFileIO(FileIo* file_io);
    bool DetectLoop();
    int FindAllWordChains(std::vector<StringPointer>& wordlist);
    int FindLongestChain(bool weighted, std::vector<StringPointer>& wordlist);

private:
    bool DfsFindLoop(char now, std::vector<int>& visited);
    void DfsGetChains(char now, std::deque<StringPointer>& records,
                      std::vector<StringPointer>& wordlist);
    int FindLongestChainWithLoops(bool weighted, std::vector<StringPointer>& wordlist);
    int FindLongestChainWithoutLoops(bool weighted, std::vector<StringPointer>& wordlist);
    void Tarjan(char u, int& dfn_num, int& fa_num,
                std::vector<int>& dfn,
                std::vector<int>& low,
                std::stack<int>& stack,
                std::vector<bool>& instack,
                std::vector<int>& fa);

    struct State {
        long long passed_edges_high = 0;
        long long passed_edges_low = 0;
        char last_pos;
        explicit State(char pos) : last_pos(pos) {}
        bool operator < (const State &s) const {
            if (last_pos != s.last_pos) {
                return last_pos < s.last_pos;
            }
            if (passed_edges_high != s.passed_edges_high) {
                return passed_edges_high < s.passed_edges_high;
            }
            if (passed_edges_low != s.passed_edges_low) {
                return passed_edges_low < s.passed_edges_low;
            }
            return false;
        }
        bool operator > (const State &s) const {
            if (last_pos != s.last_pos) {
                return last_pos > s.last_pos;
            }
            if (passed_edges_high != s.passed_edges_high) {
                return passed_edges_high > s.passed_edges_high;
            }
            if (passed_edges_low != s.passed_edges_low) {
                return passed_edges_low > s.passed_edges_low;
            }
            return true;
        }
        void set(int pos) {
            if (pos < 64) {
                passed_edges_low ^= (1ll << pos);
            } else {
                passed_edges_high ^= (1ll << (pos - 64));
            }
        }
        void reset(int pos) {
            if (pos < 64) {
                passed_edges_low ^= (1ll << pos);
            } else {
                passed_edges_high ^= (1ll << (pos - 64));
            }
        }
        void reset() {
            passed_edges_low = passed_edges_high = 0;
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

//
// Created by seeeagull on 23-3-6.
//

#include <queue>
#include <algorithm>
#include "./graph.h"

Graph::Graph() {
    edges_.resize(26);
    for (char i = 0; i < 26; ++i) {
        edges_[i] = new std::vector<EdgePointer>();
    }
}

void Graph::AddWord(const StringPointer& word) {
    Edge edge(edges_num_, word);
    edges_[edge.src]->push_back(std::make_shared<Edge>(edge));
    edges_map_[edges_num_] = std::make_shared<Edge>(edge);
    ++edges_num_;
}

void Graph::SetHead(char h) {
    this->head_ = h;
}

void Graph::SetTail(char t) {
    this->tail_ = t;
}

void Graph::SetBannedHead(char bh) {
    this->banned_head_ = bh;
}

void Graph::SetFileIO(FileIo *file_io) {
    this->file_io_ = file_io;
}

bool Graph::DetectLoop() {
    std::vector<int> visited(26);
    for (char i = 0; i < 26; ++i) {
        self_loop_.push_back(nullptr);
    }
    for (char i = 0; i < 26; ++i) {
        for (const auto& it : *edges_[i]) {
            if (i == it->tar) {
                if (self_loop_[i]) {
                    has_loop_ = true;
                }
                self_loop_[i] = it;
            }
        }
    }
    if (has_loop_) {
        if (banned_head_ != 30) {
            for (auto& it : edges_map_) {
                if (it.second->src == banned_head_) {
                    it.second = nullptr;
                }
            }
            edges_[banned_head_]->clear();
        }
        return true;
    }
    for (char i = 0; i < 26; ++i) {
        if (visited[i] == 0) {
            if (DfsFindLoop(i, visited)) {
                has_loop_ = true;
                break;
            }
        }
    }
    if (banned_head_ != 30) {
        for (auto& it : edges_map_) {
            if (it.second->src == banned_head_) {
                it.second = nullptr;
            }
        }
        edges_[banned_head_]->clear();
    }
    return has_loop_;
}

bool Graph::DfsFindLoop(char now, std::vector<int>& visited) {
    visited[now] = 1;
    for (const auto& it : *(edges_[now])) {
        auto next = it->tar;
        if (now == next || visited[next] == 2) {
            continue;
        } else if (visited[next] == 1) {
            return true;
        } else if (DfsFindLoop(next, visited)) {
            return true;
        }
    }
    visited[now] = 2;
    return false;
}

void Graph::DfsGetChains(char now, std::deque<StringPointer>& records,
                         std::vector<StringPointer>& wordlist) {
    if (tail_ == 30 || tail_ == now) {
        if (records.size() > 1) {
            if (file_io_) {
                file_io_->PrintLine(&records);
            }
            int size = records.size();
            std::string word_chain = *records[0];
            for (int i = 1; i < size; ++i) {
                word_chain += " ";
                word_chain += *records[i];
            }
            wordlist.push_back(std::make_shared<std::string>(word_chain));
        }
    }
    for (const auto& it : *edges_[now]) {
        if (it->used) {
            continue;
        }
        it->used = true;
        records.push_back(it->word);
        DfsGetChains(it->tar, records, wordlist);
        records.pop_back();
        it->used = false;
    }
}

int Graph::FindAllWordChains(std::vector<StringPointer>& wordlist) {
    int total_chains = 0;
    std::queue<char> q{};
    std::vector<int> in_degree(26);
    std::vector<int> single_word(26);
    std::vector<int> chains(26, 1);
    for (char i = 0; i < 26; ++i) {
        for (const auto& it : *edges_[i]) {
            if (i != it->tar) {
                ++in_degree[it->tar];
            }
            ++single_word[it->tar];
        }
    }
    for (char i = 0; i < 26; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        char now = q.front();
        q.pop();
        if (self_loop_[now]) {
            chains[now] <<= 1;
        }
        if (tail_ == 30 || tail_ == now) {
            total_chains += chains[now] - single_word[now] - 1;
        }
        for (const auto& it : *edges_[now]) {
            auto tar = it->tar;
            if (tar == now) {
                continue;
            }
            chains[tar] += chains[now];
            --in_degree[tar];
            if (in_degree[tar] == 0) {
                q.push(tar);
            }
        }
    }
    if (file_io_) {
        file_io_->PrintNumber(total_chains);
    }

    std::deque<StringPointer> records{};
    for (char i = 0; i < 26; ++i) {
        if (head_ == 30 || head_ == i) {
            DfsGetChains(i, records, wordlist);
        }
    }
    return total_chains;
}

void Graph::Tarjan(char u, int& dfn_num, int& fa_num,
                   std::vector<int>& dfn,
                   std::vector<int>& low,
                   std::stack<int>& stack,
                   std::vector<bool>& instack,
                   std::vector<int>& fa) {
    low[u] = dfn[u] = ++dfn_num;
    stack.push(u);
    instack[u] = true;
    for (const auto& it : *edges_[u]) {
        auto v = it->tar;
        if (dfn[v] == 0) {
            Tarjan(v, dfn_num, fa_num, dfn, low, stack, instack, fa);
            low[u] = low[v] < low[u] ? low[v] : low[u];
        } else if (instack[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }
    if (dfn[u] == low[u]) {
        ++fa_num;
        while(dfn[stack.top()] != low[stack.top()]) {
            fa[stack.top()] = fa_num;
            instack[stack.top()] = false;
            stack.pop();
        }
        fa[u] = fa_num;
        instack[u] = false;
        stack.pop();
    }
}

int Graph::FindLongestChain(bool weighted, std::vector<StringPointer>& wordlist) {
    if (has_loop_) {
        return FindLongestChainWithLoops(weighted, wordlist);
    } else {
        return FindLongestChainWithoutLoops(weighted, wordlist);
    }
}

void Graph::DfsLongestChain(char u, State& cur,
                            std::map<State, std::pair<int, char>>& longest,
                            std::map<std::pair<char, char>, int>& pos,
                            std::vector<int>& fa) {
    if (longest.count(cur)) {
        return;
    }
    char to = -1;
    int length = 0;
    if (tail_ != 30 && tail_ != u) {
        length = -1e9;
    }
    if (pos[std::make_pair(u, u)] < edges2_[std::make_pair(u, u)].size()) {
        auto edge = std::make_pair(u, u);
        cur.set(edges2_[edge][pos[edge]].second);
        pos[edge] += 1;
        DfsLongestChain(u, cur, longest, pos, fa);
        pos[edge] -= 1;
        to = u;
        length = longest[cur].first + edges2_[edge][pos[edge]].first;
        cur.reset(edges2_[edge][pos[edge]].second);
    } else {
        for (char v = 0; v < 26; ++v) {
            auto edge = std::make_pair(u, v);
            if (pos[edge] < edges2_[edge].size()) {
                if (fa[u] == fa[v]) {
                    cur.set(edges2_[edge][pos[edge]].second);
                    cur.last_pos = v;
                    pos[edge] += 1;
                    DfsLongestChain(v, cur, longest, pos, fa);
                    pos[edge] -= 1;
                    if (length < longest[cur].first + edges2_[edge][pos[edge]].first) {
                        to = v;
                        length = longest[cur].first + edges2_[edge][pos[edge]].first;
                    }
                    cur.last_pos = u;
                    cur.reset(edges2_[edge][pos[edge]].second);
                } else {
                    State new_scc(v);
                    pos[edge] += 1;
                    DfsLongestChain(v, new_scc, longest, pos, fa);
                    pos[edge] -= 1;
                    if (length < longest[new_scc].first + edges2_[edge][pos[edge]].first) {
                        to = v;
                        length = longest[new_scc].first + edges2_[edge][pos[edge]].first;
                    }
                }
            }
        }
    }
    longest[cur] = {length, to};
}

int Graph::FindLongestChainWithLoops(bool weighted, std::vector<StringPointer>& wordlist) {
    int dfn_cnt = 0, fa_num = 0;
    std::vector<int> dfn(26);
    std::vector<int> low(26);
    std::stack<int> stack{};
    std::vector<bool> instack(26);
    std::vector<int> fa(26);
    for (char i = 0; i < 26; ++i) {
        if (dfn[i] == 0) {
            Tarjan(i, dfn_cnt, fa_num, dfn, low, stack, instack, fa);
        }
    }

    std::map<std::pair<char, char>, int> pos{};
    for (char i = 0; i < 26; ++i) {
        for (char j = 0; j < 26; ++j) {
            auto edge = std::make_pair(i, j);
            edges2_[edge] = std::vector<std::pair<int, int>>();
            pos[edge] = 0;
        }
    }
    for (char i = 0; i < 26; ++i) {
        for (const auto& j : *edges_[i]) {
            auto edge = std::make_pair(i, j->tar);
            edges2_[edge].emplace_back(weighted ? j->length : 1, j->id);
        }
    }
    for (char i = 0; i < 26; ++i) {
        for (char j = 0; j < 26; ++j) {
            auto edge = std::make_pair(i, j);
            std::sort(edges2_[edge].rbegin(), edges2_[edge].rend());
        }
    }

    std::map<State, std::pair<int, char>> longest{};
    for (char i = 0; i < 26; ++i) {
        if (head_ == 30 || head_ == i) {
            State cur(i);
            DfsLongestChain(i, cur, longest, pos, fa);
        }
    }
    int max_length = 0, max_id = -1;
    char last_pos = -1;
    for (char i = 0; i < 26; ++i) {
        if (head_ == 30 || head_ == i) {
            for (const auto& it : *edges_[i]) {
                char j = it->tar;
                State first(j);
                if (fa[i] == fa[j]) {
                    first.set(it->id);
                }
                // A chain should contain at least two words.
                if (longest.count(first) == 0 || longest[first].first <= 0) {
                    continue;
                }
                int length = longest[first].first + (weighted ? it->length : 1);
                if (length > max_length) {
                    max_length = length;
                    max_id = it->id;
                    last_pos = j;
                }
            }
        }
    }

    State cur(last_pos);
    if (max_id != -1) {
        if (file_io_) {
            file_io_->PrintWord(edges_map_[max_id]->word);
        }
        wordlist.push_back(edges_map_[max_id]->word);
        last_pos = edges_map_[max_id]->tar;
        if (fa[edges_map_[max_id]->src] == fa[edges_map_[max_id]->tar]) {
            cur.set(max_id);
            cur.last_pos = last_pos;
            auto edge = std::make_pair(edges_map_[max_id]->src, edges_map_[max_id]->tar);
            pos[edge] += 1;
        }
        char to;
        while ((to = longest[cur].second) != -1) {
            auto edge = std::make_pair(last_pos, to);
            auto id = edges2_[edge][pos[edge]].second;
            if (file_io_) {
                file_io_->PrintWord(edges_map_[id]->word);
            }
            wordlist.push_back(edges_map_[id]->word);
            if (fa[last_pos] == fa[to]) {
                cur.set(id);
            } else {
                cur.reset();
            }
            pos[edge] += 1;
            last_pos = to;
            cur.last_pos = to;
        }
    }
    return max_length;
}

int Graph::FindLongestChainWithoutLoops(bool weighted, std::vector<StringPointer>& wordlist) {
    int dfn_cnt = 0, fa_num = 0;
    std::vector<int> dfn(26);
    std::vector<int> low(26);
    std::stack<int> stack{};
    std::vector<bool> instack(26);
    std::vector<int> fa(26);
    for (char i = 0; i < 26; ++i) {
        if (dfn[i] == 0) {
            Tarjan(i, dfn_cnt, fa_num, dfn, low, stack, instack, fa);
        }
    }
    std::vector<char> id(26);
    for (char i = 0; i < 26; ++i) {
        id[fa[i] - 1] = i;
    }

    char optimal = -1;
    int max_length = -1;
    std::vector<StringPointer> prev(26, nullptr);
    std::deque<StringPointer> answer{};
    std::vector<int> length(26, -1e9);
    for(char x = 0; x < 26; ++x){
        char i = id[x];
        if (tail_ == 30 || tail_ == i) {
            length[i] = 0;
        }
        for(const auto& it : *edges_[i]){
            int j = it->tar;
            if(i == j) {
                continue;
            }
            int len = length[j] + (weighted ? it->length : 1);
            if(length[j] >= 0 && len > length[i]) {
                length[i] = len;
                prev[i] = it->word;
            }
        }
        if (self_loop_[i] && length[i] >= 0) {
            length[i] += weighted ? self_loop_[i]->length : 1;
        }
    }

    for(int i = 0; i < edges_num_; i++) {
        auto edge = edges_map_[i];
        if (edge == nullptr) {
            continue;
        }
        char u = edge->src, v = edge->tar;
        if(head_ == 30 || head_ == u) {
            if(u == v){
                if(length[u] == (weighted ? edge->length : 1)) {
                    continue;
                }
                if(max_length < length[u]) {
                    max_length = length[u];
                    optimal = u;
                }
            } else {
                if(length[v] <= 0) {
                    continue;
                }
                int len = length[v] + (weighted ? edge->length : 1);
                if(max_length < len) {
                    max_length = len;
                    optimal = u;
                    prev[u] = edge->word;
                }
            }
        }
    }

    if (optimal != -1) {
        while (prev[optimal] != nullptr) {
            if (self_loop_[optimal] != nullptr) {
                answer.push_back(self_loop_[optimal]->word);
            }
            answer.push_back(prev[optimal]);
            int len = prev[optimal]->length();
            optimal = (prev[optimal])->at(len - 1) - 'a';
        }
        if (self_loop_[optimal] != nullptr) {
            answer.push_back(self_loop_[optimal]->word);
        }
        for (const auto &it: answer) {
            if (file_io_) {
                file_io_->PrintWord(it);
            }
            wordlist.push_back(it);
        }
    }
    return max_length;
}

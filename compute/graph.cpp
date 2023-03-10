//
// Created by seeeagull on 23-3-6.
//

#include <queue>
#include "./graph.h"

Graph::Graph() {
    edges_.resize(26);
    for (char i = 0; i < 26; ++i) {
        edges_[i] = new std::vector<EdgePointer>();
    }
}

void Graph::OutputAllWords() {
    for (char i = 0; i < 26; ++i) {
        std::cout << "now letter " << (char)(i + 'a') << std::endl;
        for (const auto& it : *edges_[i]) {
            std::cout << *(it->word) << " " << it->tar << std::endl;
        }
    }
}

void Graph::AddWord(const StringPointer& word) {
    auto edge = new Edge(word);
    char src = word->at(0) - 'a';
    edges_[src]->push_back(static_cast<const EdgePointer>(edge));
}

void Graph::SetHead(char h) {
    this->head_ = h;
}

void Graph::setTail(char t) {
    this->tail_ = t;
}

void Graph::SetBannedHead(char bh) {
    this->banned_head_ = bh;
}

void Graph::SetFileIO(FileIo *file_io) {
    this->file_io_ = file_io;
}

bool Graph::DetectLoop() {
    bool self_loops = false;
    std::vector<int> visited{};
    for (char i = 0; i < 26; ++i) {
        visited.push_back(0);
        self_loop_.push_back(nullptr);
    }
    for (char i = 0; i < 26; ++i) {
        for (const auto& it : *edges_[i]) {
            if (i == it->tar) {
                if (self_loop_[i]) {
                    self_loops = true;
                }
                self_loop_[i] = it;
            }
        }
    }
    if (self_loops) {
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

void Graph::DfsGetChains(char now, std::deque<StringPointer>& records) {
    if (tail_ == 30 || tail_ == now) {
        if (records.size() > 1) {
            file_io_->PrintLine(&records);
        }
    }
    if (banned_head_ == now) {
        return;
    }
    for (const auto& it : *edges_[now]) {
        if (it->used) {
            continue;
        }
        it->used = true;
        records.push_back(it->word);
        DfsGetChains(it->tar, records);
        records.pop_back();
        it->used = false;
    }
}

int Graph::FindAllWordChains() {
    int total_chains = 0;
    std::queue<char> q{};
    std::vector<int> in_degree{};
    std::vector<int> single_word{};
    std::vector<int> chains{};
    for (char i = 0; i < 26; ++i) {
        in_degree.push_back(0);
        single_word.push_back(0);
        chains.push_back(1);
    }
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
            if (now != banned_head_) {
                chains[tar] += chains[now];
            }
            --in_degree[tar];
            if (in_degree[tar] == 0) {
                q.push(tar);
            }
        }
    }
    file_io_->PrintNumber(total_chains);

    std::deque<StringPointer> records{};
    for (char i = 0; i < 26; ++i) {
        if ((head_ == 30 || head_ == i) && i != banned_head_) {
            DfsGetChains(i, records);
        }
    }
    return total_chains;
}

int Graph::FindMostWordsChain() {
    if (has_loop_) {
         return FindMostWordsChainWithLoops();
    } else {
        return FindMostWordsChainWithoutLoops();
    }
}

int Graph::FindMostLettersChain() {
    if (has_loop_) {
        return FindMostLettersChainWithLoops();
    } else {
        return FindMostLettersChainWithoutLoops();
    }
}

int Graph::FindMostWordsChainWithLoops() {
    // TODO
    return 0;
}

int Graph::FindMostWordsChainWithoutLoops() {
    char optimal = 0;
    std::vector<StringPointer> prev{};
    std::deque<StringPointer> answer{};
    std::queue<char> q{};
    std::vector<int> in_degree{};
    std::vector<int> words_cnt{};
    for (char i = 0; i < 26; ++i) {
        in_degree.push_back(0);
        words_cnt.push_back(0);
        prev.push_back(nullptr);
    }
    for (char i = 0; i < 26; ++i) {
        for (const auto& it : *edges_[i]) {
            if (i != it->tar) {
                ++in_degree[it->tar];
            }
        }
    }
    for (char i = 0; i < 26; ++i) {
        if (in_degree[i] == 0 && (head_ == 30 || head_ == i)) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        char now = q.front();
        q.pop();
        if (self_loop_[now]) {
            words_cnt[now] += 1;
        }
        for (const auto& it : *edges_[now]) {
            auto tar = it->tar;
            if (tar == now) {
                continue;
            }
            if (now != banned_head_) {
                if (words_cnt[now] + 1 > words_cnt[tar]) {
                    words_cnt[tar] = words_cnt[now] + 1;
                    prev[tar] = it->word;
                }
            }
            --in_degree[tar];
            if (in_degree[tar] == 0) {
                q.push(tar);
            }
        }
    }
    for (char i = 0; i < 26; ++i) {
        if (tail_ == 30 || tail_ == i) {
            if (words_cnt[i] > words_cnt[optimal]) {
                optimal = i;
            }
        }
    }
    int ret = words_cnt[optimal];
    while (prev[optimal] != nullptr) {
        if (self_loop_[optimal] != nullptr) {
            answer.push_front(self_loop_[optimal]->word);
        }
        answer.push_front(prev[optimal]);
        optimal = (prev[optimal])->at(0) - 'a';
    }
    if (self_loop_[optimal] != nullptr) {
        answer.push_front(self_loop_[optimal]->word);
    }
    for (const auto& it : answer) {
        file_io_->PrintWord(it);
    }
    return ret;
}

int Graph::FindMostLettersChainWithLoops() {
    // TODO
    return 0;
}

int Graph::FindMostLettersChainWithoutLoops() {
    char optimal = 0;
    std::vector<StringPointer> prev{};
    std::deque<StringPointer> answer{};
    std::queue<char> q{};
    std::vector<int> in_degree{};
    std::vector<int> letters_cnt{};
    for (char i = 0; i < 26; ++i) {
        in_degree.push_back(0);
        letters_cnt.push_back(0);
        prev.push_back(nullptr);
    }
    for (char i = 0; i < 26; ++i) {
        for (const auto& it : *edges_[i]) {
            if (i != it->tar) {
                ++in_degree[it->tar];
            }
        }
    }
    for (char i = 0; i < 26; ++i) {
        if (in_degree[i] == 0 && (head_ == 30 || head_ == i)) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        char now = q.front();
        q.pop();
        if (self_loop_[now]) {
            letters_cnt[now] += self_loop_[now]->length;
        }
        for (const auto& it : *edges_[now]) {
            auto tar = it->tar;
            if (tar == now) {
                continue;
            }
            if (now != banned_head_) {
                if (letters_cnt[now] + it->length > letters_cnt[tar]) {
                    letters_cnt[tar] = letters_cnt[now] + it->length;
                    prev[tar] = it->word;
                }
            }
            --in_degree[tar];
            if (in_degree[tar] == 0) {
                q.push(tar);
            }
        }
    }
    for (char i = 0; i < 26; ++i) {
        if (tail_ == 30 || tail_ == i) {
            if (letters_cnt[i] > letters_cnt[optimal]) {
                optimal = i;
            }
        }
    }
    int ret = letters_cnt[optimal];
    while (prev[optimal] != nullptr) {
        if (self_loop_[optimal] != nullptr) {
            answer.push_front(self_loop_[optimal]->word);
        }
        answer.push_front(prev[optimal]);
        optimal = (prev[optimal])->at(0) - 'a';
    }
    if (self_loop_[optimal] != nullptr) {
        answer.push_front(self_loop_[optimal]->word);
    }
    for (const auto& it : answer) {
        file_io_->PrintWord(it);
    }
    return ret;
}

//
// Created by seeeagull on 23-3-7.
//

#include "core.h"

void Core::AddWords(char **words, int len) {
    std::set<std::string> unique_words{};
    for (int i = 0; i < len; ++i) {
        if (unique_words.count(words[i]) == 0) {
            unique_words.insert(words[i]);
        }
    }
    for (const auto& it : unique_words) {
        graph.AddWord(std::make_shared<std::string>(it));
    }
}

void Core::HandleAdditionalParams(char head, char tail, char reject) {
    if (head == 0) {
    } else if (head >= 'a' && head <= 'z') {
        graph.SetHead(head - 'a');
    } else if (head >= 'A' && head <='Z') {
        graph.SetHead(head - 'A');
    } else {
        throw IllegalCharException();
    }
    if (tail == 0) {
    } else if (tail >= 'a' && tail <= 'z') {
        graph.SetHead(tail - 'a');
    } else if (tail >= 'A' && tail <='Z') {
        graph.SetHead(tail - 'A');
    } else {
        throw IllegalCharException();
    }
    if (reject == 0) {
    } else if (reject >= 'a' && reject <= 'z') {
        graph.SetHead(reject - 'a');
    } else if (reject >= 'A' && reject <='Z') {
        graph.SetHead(reject - 'A');
    } else {
        throw IllegalCharException();
    }
}

void Core::HandleEnableLoop(bool enable_loop) {
    if (graph.DetectLoop() && !enable_loop) {
        throw UnexpectedLoopException();
    }
}

int Core::gen_chains_all(char* words[], int len, char* result[]) {
    AddWords(words, len);
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph.FindAllWordChains(wordlist);
    Vector2Result(wordlist, result);
    return ret;
}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    try {
        HandleAdditionalParams(head, tail, reject);
    } catch (IllegalCharException& e) {
        throw e;
    }
    AddWords(words, len);
    try {
        HandleEnableLoop(enable_loop);
    } catch (UnexpectedLoopException& e) {
        throw e;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph.FindLongestChain(false, wordlist);
    Vector2Result(wordlist, result);
    return ret;
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    try {
        HandleAdditionalParams(head, tail, reject);
    } catch (IllegalCharException& e) {
        throw e;
    }
    AddWords(words, len);
    try {
        HandleEnableLoop(enable_loop);
    } catch (UnexpectedLoopException& e) {
        throw e;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret =  graph.FindLongestChain(true, wordlist);
    Vector2Result(wordlist, result);
    return ret;
}
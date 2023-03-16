//
// Created by seeeagull on 23-3-7.
//
#define CORE
#include "core.h"

int gen_chains_all(char* words[], int len, char* result[]) {
    Graph graph{};
    auto graph_pointer = std::make_shared<Graph>(graph);
    AddWords(graph_pointer, words, len);
    try {
        HandleEnableLoop(graph_pointer, false);
    } catch (UnexpectedLoopException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -11;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph_pointer->FindAllWordChains(wordlist);
    if (wordlist.size() > 20000) {
        return -12;
    }
    Vector2Result(wordlist, result);
    return ret;
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    Graph graph{};
    auto graph_pointer = std::make_shared<Graph>(graph);
    try {
        HandleAdditionalParams(graph_pointer, head, tail, reject);
    } catch (IllegalCharException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    AddWords(graph_pointer, words, len);
    try {
        HandleEnableLoop(graph_pointer, enable_loop);
    } catch (UnexpectedLoopException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -11;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph_pointer->FindLongestChain(false, wordlist);
    if (wordlist.size() > 20000) {
        return -12;
    }
    Vector2Result(wordlist, result);
    return ret;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    Graph graph{};
    auto graph_pointer = std::make_shared<Graph>(graph);
    try {
        HandleAdditionalParams(graph_pointer, head, tail, reject);
    } catch (IllegalCharException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    AddWords(graph_pointer, words, len);
    try {
        HandleEnableLoop(graph_pointer, enable_loop);
    } catch (UnexpectedLoopException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -11;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph_pointer->FindLongestChain(true, wordlist);
    if (wordlist.size() > 20000) {
        return -12;
    }
    Vector2Result(wordlist, result);
    return ret;
}
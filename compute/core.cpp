//
// Created by seeeagull on 23-3-7.
//
#define CORE
#include "core.h"

int gen_chains_all(char* words[], int len, char* result[]) {
    Graph graph{};
    AddWords(std::make_shared<Graph>(graph), words, len);
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph.FindAllWordChains(wordlist);
    Vector2Result(wordlist, result);
    return ret;
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    Graph graph{};
    try {
        HandleAdditionalParams(std::make_shared<Graph>(graph), head, tail, reject);
    } catch (IllegalCharException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    AddWords(std::make_shared<Graph>(graph), words, len);
    try {
        HandleEnableLoop(std::make_shared<Graph>(graph), enable_loop);
    } catch (UnexpectedLoopException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret = graph.FindLongestChain(false, wordlist);
    Vector2Result(wordlist, result);
    return ret;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop) {
    Graph graph{};
    try {
        HandleAdditionalParams(std::make_shared<Graph>(graph), head, tail, reject);
    } catch (IllegalCharException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    AddWords(std::make_shared<Graph>(graph), words, len);
    try {
        HandleEnableLoop(std::make_shared<Graph>(graph), enable_loop);
    } catch (UnexpectedLoopException& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    int ret =  graph.FindLongestChain(true, wordlist);
    Vector2Result(wordlist, result);
    return ret;
}
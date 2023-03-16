//
// Created by seeeagull on 23-3-14.
//

#ifndef WORDLIST_EXE_CORE_H
#define WORDLIST_EXE_CORE_H

#ifdef CORE
#define EXPOSED_FUNCTION extern "C" __declspec(dllexport)
#else
#define EXPOSED_FUNCTION extern "C" __declspec(dllimport)
#endif

#include "./types.h"
#include "../compute/graph.h"

EXPOSED_FUNCTION int gen_chains_all(char* words[], int len, char* result[]);
EXPOSED_FUNCTION int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
EXPOSED_FUNCTION int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
//int gen_chains_all(char* words[], int len, char* result[]);
//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);

static void AddWords(const std::shared_ptr<Graph>& graph, char *words[], int len) {
    std::set<std::string> unique_words{};
    for (int i = 0; i < len; ++i) {
        if (unique_words.count(words[i]) == 0) {
            unique_words.insert(words[i]);
        }
    }
    for (const auto& it : unique_words) {
        graph->AddWord(std::make_shared<std::string>(it));
    }
}

static void HandleAdditionalParams(const std::shared_ptr<Graph>& graph,
                                   char head, char tail, char reject) {
    if (head == 0) {
    } else if (head >= 'a' && head <= 'z') {
        graph->SetHead(head - 'a');
    } else if (head >= 'A' && head <='Z') {
        graph->SetHead(head - 'A');
    } else {
        throw IllegalCharException();
    }
    if (tail == 0) {
    } else if (tail >= 'a' && tail <= 'z') {
        graph->SetHead(tail - 'a');
    } else if (tail >= 'A' && tail <='Z') {
        graph->SetHead(tail - 'A');
    } else {
        throw IllegalCharException();
    }
    if (reject == 0) {
    } else if (reject >= 'a' && reject <= 'z') {
        graph->SetHead(reject - 'a');
    } else if (reject >= 'A' && reject <='Z') {
        graph->SetHead(reject - 'A');
    } else {
        throw IllegalCharException();
    }
}

static void HandleEnableLoop(const std::shared_ptr<Graph>& graph, bool enable_loop) {
    if (graph->DetectLoop() && !enable_loop) {
        throw UnexpectedLoopException();
    }
}

static void Vector2Result(std::vector<std::shared_ptr<std::string>> vec, char* result[]){
    int pos = 0, size = vec.size();
    for(const auto &i : vec) {
        pos += (int)i->length() + 1;
    }
    char* p = (char*) malloc((size_t) pos + 1);
    for(int i = 0; i < size; i++){
        result[i] = p;
        for(auto j : *vec[i]){
            if (p != nullptr) *p = j;
            p++;
        }
        if (p != nullptr) *p = 0;
        p++;
    }
}

#endif //WORDLIST_EXE_CORE_H

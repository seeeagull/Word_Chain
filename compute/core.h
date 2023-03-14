//
// Created by seeeagull on 23-3-14.
//

#ifndef WORDLIST_EXE_CORE_H
#define WORDLIST_EXE_CORE_H

#include "./types.h"
#include "./graph.h"

class Core {
public:
    int gen_chains_all(char* words[], int len, char* result[]);
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
private:
    void AddWords(char* words[], int len);
    void HandleAdditionalParams(char head, char tail, char reject);
    void HandleEnableLoop(bool enable_loop);
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
    Graph graph{};
};

#endif //WORDLIST_EXE_CORE_H

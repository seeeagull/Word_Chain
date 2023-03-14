//
// Created by Jiang on 2023/3/14.
//
#include <iostream>

#ifdef CORE
#define EXPOSED_FUNCTION extern "C" __declspec(dllexport)
#else
#define EXPOSED_FUNCTION extern "C" __declspec(dllimport)
#endif

EXPOSED_FUNCTION int gen_chains_all(char* words[], int len, char* result[]);
EXPOSED_FUNCTION int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
EXPOSED_FUNCTION int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);

int dll_test() {
    char* words[] = {"abc", "cc", "ced", "dopwa", "dz", "zy"};
    int len = 6;
    char* result[100000];
    int ret = gen_chains_all(words, len, result);
    std::cout << ret << std::endl;
    for (int i = 0; i < ret; ++i) {
        std::cout << words[i] << std::endl;
    }
    return 0;
}

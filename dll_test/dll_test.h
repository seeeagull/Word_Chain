//
// Created by Jiang on 2023/3/14.
//

#ifndef WORDLIST_DLL_TEST_H
#define WORDLIST_DLL_TEST_H

#include <iostream>
#include <cstring>
#include "./dll_test.h"

#ifdef CORE
#define EXPOSED_FUNCTION extern "C" __declspec(dllexport)
#else
#define EXPOSED_FUNCTION extern "C" __declspec(dllimport)
#endif

EXPOSED_FUNCTION int gen_chains_all(char* words[], int len, char* result[]);
EXPOSED_FUNCTION int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
EXPOSED_FUNCTION int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);

void dll_test() {
    FILE *file = nullptr;
    fopen_s(&file, "D:/courses/sixth/software/Word_Chain/simple.txt", "r");
    int len;
    char* words[100];
    std::string s;
    char c;
    int wordCount = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c >= 'A' && c <= 'Z')
            s += char(c - 'A' + 'a');
        else if (c >= 'a' && c <= 'z')
            s += c;
        else {
            if ((int)s.size() > 1) {
                char* tmp = (char*)malloc(s.length() + 1);
                if (tmp != nullptr) {
                    char* str = tmp;
                    for (char i : s) {
                        (*str++) = i;
                    }
                    (*str) = '\0';
                    words[wordCount] = tmp;
                    ++wordCount;
                }
            }
            s = "";
        }
    }
    if ((int)s.size() > 1) {
        char* tmp = (char*)malloc(s.length() + 1);
        if (tmp != nullptr) {
            char* str = tmp;
            for (char i : s) {
                (*str++) = i;
            }
            (*str) = '\0';
            words[wordCount] = tmp;
            ++wordCount;
        }
    }
    len = wordCount;
    char *result[10000];
    int ret = gen_chains_all(words, len, result);
    std::cout << ret << std::endl;
    int i = 0;
    while (strlen(result[i]) > 0) {
        std::cout << result[i] << std::endl;
        ++i;
    }
}

#endif //WORDLIST_DLL_TEST_H

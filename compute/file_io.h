//
// Created by seeeagull on 23-3-6.
//

#ifndef WORD_CHAIN_FILE_IO_H
#define WORD_CHAIN_FILE_IO_H

#include <vector>
#include <string>
#include <deque>
#include <set>
#include <memory>
#include <iostream>
#include <fstream>
#include "../core/types.h"

class FileIo {
    typedef std::shared_ptr<std::string> StringPointer;
public:
    FileIo();
    ~FileIo();
    void SetInputFile(StringPointer file);
    void SetOutputFile(StringPointer file);
    void ReadFile(std::vector<StringPointer>& words);
    void PrintNumber(int number);
    void PrintLine(std::deque<StringPointer>* words);
    void PrintWord(const StringPointer& word);

private:
    StringPointer input_file_;
    std::string output_file_ = "./solution.txt";
    std::ofstream target;
};

#endif //WORD_CHAIN_FILE_IO_H

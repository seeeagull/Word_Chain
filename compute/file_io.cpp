//
// Created by seeeagull on 23-3-6.
//

#include <utility>

#include "./file_io.h"

FileIo::FileIo() {
    target.open(output_file_);
}

FileIo::~FileIo() {
    // TODO: others?
    target.close();
}

void FileIo::SetInputFile(StringPointer file) {
    input_file_ = std::move(file);
}

void FileIo::ReadFile(std::vector<StringPointer>& words) {
    std::ifstream source(*input_file_);
    if (!source.is_open()) {
        throw CannotFindInputFile();
    } else {
        std::string cur_line;
        while (getline(source, cur_line)) {
            int length = cur_line.length();
            int start = 0;
            for (int i = 0; i < length; ++i) {
                if (!(cur_line[i] >= 'a' && cur_line[i] <= 'z' || cur_line[i] >= 'A' && cur_line[i] <= 'Z')) {
                    if (start < i) {
                        auto new_word = cur_line.substr(start, i - start);
                        words.push_back(std::make_shared<std::string>(new_word));
                    }
                    start = i + 1;
                } else if (cur_line[i] >= 'A' && cur_line[i] <= 'Z') {
                    cur_line[i] = cur_line[i] - 'A' + 'a';
                }
            }
            if (start < length) {
                auto new_word = cur_line.substr(start, length - start);
                words.push_back(std::make_shared<std::string>(new_word));
            }
        }
    }
}

void FileIo::PrintNumber(int number) {
    target << number << std::endl;
}

void FileIo::PrintLine(std::deque<StringPointer>* words) {
    int length = words->size();
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            target << " ";
        }
        target << *(*words)[i];
    }
    target << std::endl;
}

void FileIo::PrintWord(const StringPointer& word) {
    target << *word << std::endl;
}

//
// Created by seeeagull on 23-3-7.
//


#include "controller.h"

void Controller::ParseCmd(int argc, char *argv[]) {
    int i = 1;
    while (i < argc) {
        if (argv[i][0] != '-') {
            // TODO: throw error
        }
        switch (argv[i][1]) {
            case 'n':
                if (function_type_ != kNone) {
                    throw ConflictFunctionalParamsException();
                }
                function_type_ = kFindAllWordChains;
                input_file_ = argv[i + 1];
                i += 2;
                break;
            case 'w':
                if (function_type_ != kNone) {
                    throw ConflictFunctionalParamsException();
                }
                function_type_ = kFindWordChainWithMostWords;
                input_file_ = argv[i + 1];
                i += 2;
                break;
            case 'c':
                if (function_type_ != kNone) {
                    throw ConflictFunctionalParamsException();
                }
                function_type_ = kFindWordChainWithMostLetters;
                input_file_ = argv[i + 1];
                i += 2;
                break;
            case 'h':
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    head = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    head = argv[i + 1][0] - 'a';
                } else  {
                    // TODO: throw error
                }
                i += 2;
                break;
            case 't':
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    tail = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    tail = argv[i + 1][0] - 'a';
                } else  {
                    // TODO: throw error
                }
                i += 2;
                break;
            case 'j':
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    banned_head_ = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    banned_head_ = argv[i + 1][0] - 'a';
                } else  {
                    // TODO: throw error
                }
                i += 2;
                break;
            case 'r':
                allow_loop_ = true;
                ++i;
                break;
        }
    }
    if (function_type_ == kNone) {
        throw NoFunctionalParamException();
    } else if (function_type_ == kFindAllWordChains &&
               (head != 30 || tail != 30 || banned_head_ != 30 || allow_loop_)) {
        throw ConflictAdditionalParamsException();
    }

    if (input_file_.length() == 0) {
        throw NoInputFileException();
    }
}

int Controller::Cmd(int argc, char **argv, int *res, const char* file_name) {
    try {
        ParseCmd(argc, argv);
    } catch (NoInputFileException e) {
        return kNoFilePath;
    }
    graph.SetHead(head);
    graph.setTail(tail);
    graph.SetBannedHead(banned_head_);
    graph.SetFileIO(&file_io_);
    file_io_.SetInputFile(std::make_shared<std::string>(input_file_));
    std::string output_file(file_name);
    file_io_.SetOutputFile(std::make_shared<std::string>(output_file));
    std::vector<std::shared_ptr<std::string>> words{};
    file_io_.ReadFile(words);

    for(const auto& it : words) {
        graph.AddWord(it);
    }
    bool has_loop = graph.DetectLoop();
    if (has_loop && !allow_loop_) {
        return kUnexpectedLoop;
    }
    switch (function_type_) {
        case kFindAllWordChains:
            *res = graph.FindAllWordChains();
            break;
        case kFindWordChainWithMostWords:
            *res = graph.FindMostWordsChain();
            break;
        case kFindWordChainWithMostLetters:
            *res = graph.FindMostLettersChain();
            break;
        default:
            break;
    }
    return kNoError;
}


//
// Created by seeeagull on 23-3-6.
//

#ifndef WORD_CHAIN_TYPES_H
#define WORD_CHAIN_TYPES_H

#include <exception>

enum FUNCTION_TYPE {
    kNone,
    kFindAllWordChains,
    kFindWordChainWithMostWords,
    kFindWordChainWithMostLetters
};

struct ConflictFunctionalParamsException
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot specify more than one functional parameters!";
    }
};

struct ConflictAdditionalParamsException
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot add any additional parameters with functional parameter '-n'!";
    }
};

struct NoFunctionalParamException
        : public std::exception {
    const char * what () const noexcept override {
        return "Must specify one functional parameter!";
    }
};

struct NoInputFileException
        : public std::exception {
    const char * what () const noexcept override {
        return "Must input a text file!";
    }
};

struct CannotFindInputFile
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot find text file!";
    }
};

struct ShouldNotContainLoops
        : public std::exception {
    const char * what () const noexcept override {
        return "The input file should not contain word loops without parameter '-r'!";
    }
};

#endif //WORD_CHAIN_TYPES_H

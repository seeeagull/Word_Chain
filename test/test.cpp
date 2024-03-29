#include <iostream>
#include <cctype>
#include <unordered_set>
#include <vector>
#include "gtest/gtest.h"
#include "../core/types.h"
#include "../compute/controller.h"

#ifndef WORD_CHAIN_H
#define WORD_CHAIN_H

class WordChain {
private:
    std::string file_name_;
    std::vector<std::string> pts_;     // unique pts_
    std::vector<std::vector<int> > edges_;
    std::vector<std::vector<int> > dist_;

public:
    explicit WordChain(const std::string &file_name) : file_name_(file_name), chain_cnt_(), char_cnt_(),
                                                       max_char_cnt_(), banned_(), head_(), tail_() {}

    void BuildGraph() {
        std::ifstream file(file_name_);
        if (!file.is_open()) {
            std::cerr << "Error: " << file_name_ << " does not exist." << std::endl;
            std::exit(1);
        }
        std::unordered_set<std::string> word_set;
        std::string s;
        char c;
        while (file.get(c)) {
            if (isupper(c)) s += (char) tolower(c);
            else if (islower(c)) s += c;
            else {
                if (s.length() > 0) {
                    if (word_set.find(s) == word_set.end()) {
                        pts_.push_back(s);
                        word_set.insert(s);
                    }
                    s = "";
                }
            }
        }
        if (s.length() > 0 and word_set.find(s) == word_set.end()) {
            pts_.push_back(s);
            word_set.insert(s);
        }
        int n = (int) pts_.size();
        edges_.resize(n, std::vector<int>(0));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {   // do not contain self-circle
                if (pts_[i][pts_[i].length() - 1] == pts_[j][0]) {
                    edges_[i].push_back(j);
                }
                if (pts_[j][pts_[j].length() - 1] == pts_[i][0]) {
                    edges_[j].push_back(i);
                }
            }
        }
//        for (int i = 0; i < n; ++i) {
//            std::cout << pts_[i] << ": ";
//            for (int j = 0; j < edges_[i].size(); ++j) {
//                std::cout << pts_[edges_[i][j]] << ' ';
//            }
//            std::cout << std::endl;
//        }
    }

private :
    std::unordered_set<int> vis_;
    std::vector<int> chain_;
    std::vector<int> res_;
    std::vector<std::string> output_;
    int chain_cnt_;
    int char_cnt_;
    int max_char_cnt_;
    char banned_;
    char head_;
    char tail_;

    void DFSChainCnt(int p) {
        vis_.insert(p);
        chain_.push_back(p);
        if (chain_.size() >= 2) chain_cnt_++;
        for (int next: edges_[p]) {
            if (vis_.find(next) == vis_.end()) DFSChainCnt(next);
        }
        vis_.erase(p);
        chain_.pop_back();
    }

    void DFSWord(int p) {
        vis_.insert(p);
        chain_.push_back(p);
        if ((tail_ == 0 || tail_ == pts_[p][pts_[p].length() - 1]) &&
            res_.size() < chain_.size() && chain_.size() >= 2)
            res_ = chain_;
        for (int next: edges_[p]) {
            if (vis_.find(next) == vis_.end() && pts_[next][0] != banned_)
                DFSWord(next);
        }
        vis_.erase(p);
        chain_.pop_back();
    }

    void DFSChar(int p) {
        vis_.insert(p);
        chain_.push_back(p);
        char_cnt_ += pts_[p].length();
        if ((tail_ == 0 || tail_ == pts_[p][pts_[p].length() - 1]) &&
            max_char_cnt_ < char_cnt_ && chain_.size() >= 2) {
            res_ = chain_;
            max_char_cnt_ = char_cnt_;
        }
        for (int next: edges_[p]) {
            if (vis_.find(next) == vis_.end() && pts_[next][0] != banned_)
                DFSChar(next);
        }
        vis_.erase(p);
        chain_.pop_back();
        char_cnt_ -= pts_[p].length();
    }

public:

    void OutputFile(const char *file_name) {
        std::ofstream output_file(file_name);
        for (int i = 0; i < output_.size(); ++i) {
            output_file << output_[i] << '\n';
        }
        output_file.close();
    }

    int GetChainCnt() {
        vis_.clear();
        chain_.clear();
        chain_cnt_ = 0;
        for (int i = 0; i < pts_.size(); ++i) {
            DFSChainCnt(i);
        }
        output_.clear();
        output_.push_back(std::to_string(chain_cnt_));
        return chain_cnt_;
    }

    int GetMostWordChain(char head, char tail, char banned) {
        head_ = head;
        tail_ = tail;
        banned_ = banned;
        vis_.clear();
        chain_.clear();
        res_.clear();
        for (int i = 0; i < pts_.size(); ++i) {
            if ((head_ == 0 || head_ == pts_[i][0]) && pts_[i][0] != banned_)
                DFSWord(i);
        }
        output_.clear();
        for (int i = 0; i < res_.size(); ++i) {
            output_.push_back(pts_[res_[i]]);
        }
        return res_.size();
    }

    int GetMostCharChain(char head, char tail, char banned) {
        head_ = head;
        tail_ = tail;
        banned_ = banned;
        char_cnt_ = 0;
        max_char_cnt_ = 0;
        vis_.clear();
        chain_.clear();
        res_.clear();
        for (int i = 0; i < pts_.size(); ++i) {
            if ((head_ == 0 || head_ == pts_[i][0]) && pts_[i][0] != banned_)
                DFSChar(i);
        }
        output_.clear();
        for (int i = 0; i < res_.size(); ++i) {
            output_.push_back(pts_[res_[i]]);
        }
        return max_char_cnt_;
    }
};

#endif //WORD_CHAIN_H

TEST(correctness_test, testcase1) {
    const char *file_name = "./testcase/testcase1.txt";
    const char *argv[] = {"Wordlist.exe", "-n", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetChainCnt();
    word_chain.OutputFile("./output/output1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase2_1) {
    const char *file_name = "./testcase/testcase2.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-h", "C", "-j", "V", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain('c', 0, 'v');
    word_chain.OutputFile("./output/output2_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output2_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase2_2) {
    const char *file_name = "./testcase/testcase2.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-j", "h", "-t", "J", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain(0, 'j', 'h');
    word_chain.OutputFile("./output/output2_2_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output2_2.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase3) {
    const char *file_name = "./testcase/testcase3.txt";
    const char *argv[] = {"Wordlist.exe", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 0, 0);
    word_chain.OutputFile("./output/output3_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output3.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase4_1) {
    const char *file_name = "./testcase/testcase4.txt";
    const char *argv[] = {"Wordlist.exe", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain(0, 0, 0);
    word_chain.OutputFile("./output/output4_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output4_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase4_2) {
    const char *file_name = "./testcase/testcase4.txt";
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-t", "a", "-j", "b", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain('a', 'a', 'b');
    word_chain.OutputFile("./output/output4_2_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output4_2.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase4_3) {
    const char *file_name = "./testcase/testcase4.txt";
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-j", "b", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain('a', 0, 'b');
    word_chain.OutputFile("./output/output4_3_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output4_3.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase4_4) {
    const char *file_name = "./testcase/testcase4.txt";
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain('a', 0, 0);
    word_chain.OutputFile("./output/output4_4_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output4_4.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase4_5) {
    const char *file_name = "./testcase/testcase4.txt";
    const char *argv[] = {"Wordlist.exe", "-t", "a", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain(0, 'a', 0);
    word_chain.OutputFile("./output/output4_5_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output4_5.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase5_1) {
    const char *file_name = "./testcase/testcase5.txt";
    const char *argv[] = {"Wordlist.exe", "-j", "h", "-r", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain(0, 0, 'h');
    word_chain.OutputFile("./output/output5_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output5_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase5_2) {
    const char *file_name = "./testcase/testcase5.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-h", "a", "-t", "a", "-j", "b", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain('a', 'a', 'b');
    word_chain.OutputFile("./output/output5_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output5_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase5_3) {
    const char *file_name = "./testcase/testcase5.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-h", "a", "-t", "a", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain('a', 'a', 0);
    word_chain.OutputFile("./output/output5_3_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output5_3.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase5_4) {
    const char *file_name = "./testcase/testcase5.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-t", "a", "-j", "b", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 'a', 'b');
    word_chain.OutputFile("./output/output5_4_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output5_4.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase6_1) {
    const char *file_name = "./testcase/testcase6.txt";
    const char *argv[] = {"Wordlist.exe", "-t", "t", "-r", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 't', 0);
    word_chain.OutputFile("./output/output6_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output6_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase6_2) {
    const char *file_name = "./testcase/testcase6.txt";
    const char *argv[] = {"Wordlist.exe", "-h", "n", "-r", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain('n', 0, 0);
    word_chain.OutputFile("./output/output6_2_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output6_2.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase7_1) {
    const char *file_name = "./testcase/testcase7.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 0, 0);
    word_chain.OutputFile("./output/output7_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output7_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase7_2) {
    const char *file_name = "./testcase/testcase7.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-t", "b", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 'b', 0);
    word_chain.OutputFile("./output/output7_2_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "./output/output7_2.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase8) {
    const char *file_name = "./testcase/testcase8.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain(0, 0, 0);
    word_chain.OutputFile("./output/output8_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output8.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase9) {
    const char *file_name = "./testcase/testcase9.txt";
    const char *argv[] = {"Wordlist.exe", "-h", "j", "-t", "z", "-r", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain('j', 'z', 0);
    word_chain.OutputFile("./output/output9_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output9.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase10) {
    const char *file_name = "./testcase/testcase10.txt";
    const char *argv[] = {"Wordlist.exe", "-j", "b", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain(0, 0, 'b');
    word_chain.OutputFile("./output/output10_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output10.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase12) {
    const char *file_name = "./testcase/testcase12.txt";
    const char *argv[] = {"Wordlist.exe", "-n", file_name};
    WordChain word_chain((std::string(file_name)));
    Controller controller{};
    word_chain.BuildGraph();
    int std_res = word_chain.GetChainCnt();
    word_chain.OutputFile("./output/output12_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "./output/output12.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(robustness_test, testcase1) {
    const char *argv[] = {"Wordlist.exe", "-n"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp1.txt");
    EXPECT_EQ(ret, kNoFilePath);
}

TEST(robustness_test, testcase2_1) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase2.txt", "./testcase/testcase2.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp2_1.txt");
    EXPECT_EQ(ret, kMultiFilePath);
}

TEST(robustness_test, testcase2_2) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase2.txt", "./testcase/testcase2.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp2_2.txt");
    EXPECT_EQ(ret, kMultiFilePath);
}

TEST(robustness_test, testcase2_3) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase2.txt", "./testcase/testcase2.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp2_3.txt");
    EXPECT_EQ(ret, kMultiFilePath);
}

TEST(robustness_test, testcase3_1) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase0.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp3_1.txt");
    EXPECT_EQ(ret, kFileNotExists);
}

TEST(robustness_test, testcase3_2) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase0.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp3_2.txt");
    EXPECT_EQ(ret, kFileNotExists);
}

TEST(robustness_test, testcase3_3) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase0.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp3_3.txt");
    EXPECT_EQ(ret, kFileNotExists);
}

TEST(robustness_test, testcase4_1) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase11.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_1.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase4_2) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase11.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_2.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase4_3) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase11.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_3.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase4_4) {
    const char *argv[] = {"Wordlist.exe", "-n", "t.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_4.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase4_5) {
    const char *argv[] = {"Wordlist.exe", "-n", "t.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_5.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase4_6) {
    const char *argv[] = {"Wordlist.exe", "-n", "t.c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4_6.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase5_1) {
    const char *argv[] = {"Wordlist.exe", "-q", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp5_1.txt");
    EXPECT_EQ(ret, kIllegalParam);
}

TEST(robustness_test, testcase5_2) {
    const char *argv[] = {"Wordlist.exe", "-r", "a", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp5_2.txt");
    EXPECT_EQ(ret, kIllegalParam);
}

TEST(robustness_test, testcase5_3) {
    const char *argv[] = {"Wordlist.exe",  "a", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp5_3.txt");
    EXPECT_EQ(ret, kIllegalParam);
}

TEST(robustness_test, testcase6_1) {
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-t", "s", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp6_1.txt");
    EXPECT_EQ(ret, kNoFunctionalParam);
}

TEST(robustness_test, testcase6_2) {
    const char *argv[] = {"Wordlist.exe", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp6_2.txt");
    EXPECT_EQ(ret, kNoFunctionalParam);
}

TEST(robustness_test, testcase6_3) {
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-j", "s", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp6_3.txt");
    EXPECT_EQ(ret, kNoFunctionalParam);
}

TEST(robustness_test, testcase7_1) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase1.txt", "-n"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_1.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_2) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase1.txt", "-n"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_2.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_3) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-w"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_3.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_4) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase1.txt", "-w"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_4.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_5) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_5.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_6) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase1.txt", "-c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_6.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_7) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-h", "h"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_7.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_8) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-t", "h"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_8.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase7_9) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-j", "h"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7_9.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase8_1) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase1.txt", "-n"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp8_1.txt");
    EXPECT_EQ(ret, kDuplicateParam);
}

TEST(robustness_test, testcase8_2) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase1.txt", "-w"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp8_2.txt");
    EXPECT_EQ(ret, kDuplicateParam);
}

TEST(robustness_test, testcase8_3) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase1.txt", "-c"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp8_3.txt");
    EXPECT_EQ(ret, kDuplicateParam);
}

TEST(robustness_test, testcase9_1) {
    const char *argv[] = {"Wordlist.exe", "-h", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp9_1.txt");
    EXPECT_EQ(ret, kCharNotAssign);
}

TEST(robustness_test, testcase9_2) {
    const char *argv[] = {"Wordlist.exe", "-t", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp9_2.txt");
    EXPECT_EQ(ret, kCharNotAssign);
}

TEST(robustness_test, testcase9_3) {
    const char *argv[] = {"Wordlist.exe", "-j", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp9_3.txt");
    EXPECT_EQ(ret, kCharNotAssign);
}

TEST(robustness_test, testcase10_1) {
    const char *argv[] = {"Wordlist.exe", "-h", "AB", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_1.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_2) {
    const char *argv[] = {"Wordlist.exe", "-t", "AB", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_2.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_3) {
    const char *argv[] = {"Wordlist.exe", "-j", "AB", "-n", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_3.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_4) {
    const char *argv[] = {"Wordlist.exe", "-h", "1", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_4.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_5) {
    const char *argv[] = {"Wordlist.exe", "-t", "1", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_5.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_6) {
    const char *argv[] = {"Wordlist.exe", "-j", "1", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_6.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_7) {
    const char *argv[] = {"Wordlist.exe", "-h", "a", "a", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_7.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_8) {
    const char *argv[] = {"Wordlist.exe", "-t", "a", "a", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_8.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase10_9) {
    const char *argv[] = {"Wordlist.exe", "-j", "a", "a", "./testcase/testcase1.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10_9.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase11_1) {
    const char *argv[] = {"Wordlist.exe", "-n", "./testcase/testcase5.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp11_1.txt");
    EXPECT_EQ(ret, kUnexpectedLoop);
}

TEST(robustness_test, testcase11_2) {
    const char *argv[] = {"Wordlist.exe", "-w", "./testcase/testcase5.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp11_2.txt");
    EXPECT_EQ(ret, kUnexpectedLoop);
}

TEST(robustness_test, testcase11_3) {
    const char *argv[] = {"Wordlist.exe", "-c", "./testcase/testcase5.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp11_3.txt");
    EXPECT_EQ(ret, kUnexpectedLoop);
}


TEST(robustness_test, testcase12_1) {
    const char *argv[] = {"Wordlist.exe", "-r", "-w", "./testcase/testcase13.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp12_1.txt");
    EXPECT_EQ(ret, kLengthOverflow);
}

TEST(robustness_test, testcase12_2) {
    const char *argv[] = {"Wordlist.exe", "-r", "-c", "./testcase/testcase13.txt"};
    Controller controller{};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp12_2.txt");
    EXPECT_EQ(ret, kLengthOverflow);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
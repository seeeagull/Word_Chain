#include <QtWidgets>
#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../core/types.h"

#include "gui_qt5.h"

#ifdef CORE
#define EXPOSED_FUNCTION extern "C" __declspec(dllexport)
#else
#define EXPOSED_FUNCTION extern "C" __declspec(dllimport)
#endif

EXPOSED_FUNCTION int gen_chains_all(char* words[], int len, char* result[]);
EXPOSED_FUNCTION int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);
EXPOSED_FUNCTION int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char reject, bool enable_loop);

WordChainUIQt5::WordChainUIQt5() {
    createMenu();
    createControlBox();
    createDisplayBox();

    auto *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(controlGroupBox);
    mainLayout->addWidget(displayGroupBox);

    auto *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(mainLayout);

    auto *scrollArea = new QScrollArea;
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 20px;}");

    scrollArea->setWidget(scrollAreaContent);

    auto *scrollLayout = new QVBoxLayout;
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->addWidget(scrollArea);

    setLayout(scrollLayout);
    setWindowTitle("最长单词链");
}

void WordChainUIQt5::createMenu() {
    menuBar = new QMenuBar;
    fileMenu = new QMenu("&File", this);
    exitAction = fileMenu->addAction("E&xit");
    menuBar->addMenu(fileMenu);
    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void WordChainUIQt5::createControlBox() {
    controlGroupBox = new QGroupBox;
    auto *layout = new QGridLayout;
    functionalParamsGroup = new QButtonGroup;
    for (int i = 0; i < NumFunctions; ++i) {
        functionalParamsRadio[i] = new QRadioButton(functions[i]);
        functionalParamsGroup->addButton(functionalParamsRadio[i]);
        layout->addWidget(functionalParamsRadio[i], 0, 4 * i, 1, 4);
    }
    connect(functionalParamsRadio[0], SIGNAL(toggled(bool)), this, SLOT(onFunctionalParamNButtonClicked(bool)));
    functionalParamsRadio[1]->setChecked(true);
    for (int i = 0; i < NumLimits; ++i) {
        if (i < 3) {
            limitLabels[i] = new QLabel(limits[i]);
            limitChar[i] = new QLineEdit;
            limitChar[i]->setPlaceholderText("允许所有");
            QRegularExpression regex("[a-zA-Z]{1}");
            QValidator *validator = new QRegularExpressionValidator(regex);
            limitChar[i]->setValidator(validator);
            layout->addWidget(limitLabels[i], i / 2 + 1, 6 * (i % 2), 1, 2);
            layout->addWidget(limitChar[i], i / 2 + 1, 6 * (i % 2) + 2, 1, 4);
        } else {
            allowRingsRadio = new QRadioButton(limits[i]);
            layout->addWidget(allowRingsRadio, 2, 6, 1, 2);
        }
    }
    usedTimeLabel = new QLabel("");
    layout->addWidget(usedTimeLabel, 2, 8, 1, 4);
    inputPathChooseButton = new QPushButton("导入");
    connect(inputPathChooseButton, SIGNAL(clicked()), this, SLOT(onInputPathChooseButtonClicked()));
    inputPathLineEdit = new QLineEdit;
    inputPathLineEdit->setReadOnly(true);
    inputPathLineEdit->setPlaceholderText("输入文件路径");
    solveButton = new QPushButton("求解");
    connect(solveButton, SIGNAL(clicked()), this, SLOT(onSolveButtonClicked()));
    outputPathChooseButton = new QPushButton("导出");
    connect(outputPathChooseButton, SIGNAL(clicked()), this, SLOT(onOutputPathChooseButtonClicked()));
    layout->addWidget(inputPathChooseButton, 3, 0, 1, 2);
    layout->addWidget(inputPathLineEdit, 3, 2, 1, 6);
    layout->addWidget(solveButton, 3, 8, 1, 2);
    layout->addWidget(outputPathChooseButton, 3, 10, 1, 2);
    controlGroupBox->setLayout(layout);
}

void WordChainUIQt5::createDisplayBox() {
    displayGroupBox = new QGroupBox;
    auto *layout = new QGridLayout;
    inputContentTextEdit = new QTextEdit;
    inputContentTextEdit->setPlaceholderText("在此处输入单词或导入单词文件");
    layout->addWidget(inputContentTextEdit, 0, 0);
    outputContentTextEdit = new QTextEdit;
    outputContentTextEdit->setPlaceholderText("求解结果");
    outputContentTextEdit->setReadOnly(true);
    layout->addWidget(outputContentTextEdit, 0, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    displayGroupBox->setLayout(layout);
}

void WordChainUIQt5::onInputPathChooseButtonClicked() {
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择待导入文件";
    QString filter = "文本文件(*.txt)";
    QString inputPath = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (!inputPath.isEmpty()) {
        QFile inputFile(inputPath);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        QTextStream inputContentTextStream(&inputFile);
        QString line = inputContentTextStream.readLine();
        QString inputContent;
        while (!line.isNull()) {
            inputContent.append(line).append('\n');
            line = inputContentTextStream.readLine();
        }
        inputPathLineEdit->setText(inputPath);
        inputContentTextEdit->setText(inputContent);
    }
}

void WordChainUIQt5::onSolveButtonClicked() {
    char functionalParam = functionalParamsRadio[0]->isChecked() ? 'n' :
                           functionalParamsRadio[1]->isChecked() ? 'w' :
                           functionalParamsRadio[2]->isChecked() ? 'c' : 0;
    char head = limitChar[0]->text().toStdString().length() > 0 ? tolower(limitChar[0]->text().toStdString()[0]) : 0;
    char tail = limitChar[1]->text().toStdString().length() > 0 ? tolower(limitChar[1]->text().toStdString()[0]) : 0;
    char reject = limitChar[2]->text().toStdString().length() > 0 ? tolower(limitChar[2]->text().toStdString()[0]) : 0;
    bool enable_loop = allowRingsRadio->isChecked();
    char *words[200000];
    char *res[20000];
    std::string inputContent = inputContentTextEdit->toPlainText().toStdString();
    std::string s;
    int len = 0;
    for (int i = 0; i < (int)inputContent.length(); ++i) {
        char c = inputContent[i];
        if (c >= 'A' && c <= 'Z')
            s += char(c - 'A' + 'a');
        else if (c >= 'a' && c <= 'z')
            s += c;
        else {
            if ((int) s.size() > 1) {
                char *tmp = (char *) malloc(s.length() + 1);
                if (tmp != nullptr) {
                    char *str = tmp;
                    for (char i: s) {
                        (*str++) = i;
                    }
                    (*str) = '\0';
                    words[len] = tmp;
                    ++len;
                }
            }
            s = "";
        }
    }
    if ((int) s.size() > 1) {
        char *tmp = (char *) malloc(s.length() + 1);
        if (tmp != nullptr) {
            char *str = tmp;
            for (char i: s) {
                (*str++) = i;
            }
            (*str) = '\0';
            words[len] = tmp;
            ++len;
        }
    }
    QElapsedTimer timer;
    timer.start();
    int ret;
    switch (functionalParam) {
        case 'n':
            ret = gen_chains_all(words, len, res);
            break;
        case 'w':
            ret = gen_chain_word(words, len, res, head, tail, reject, enable_loop);
            break;
        case 'c':
            ret = gen_chain_char(words, len, res, head, tail, reject, enable_loop);
            break;
        default:
            // never hit here
            ret = -1;
            break;
    }
    qint64 elapsed = timer.nsecsElapsed();
    if (ret < 0) {
        if (ret == -kUnexpectedLoop) {
            QMessageBox::information(nullptr, "提示", "输入存在环，请勾选\"允许出现环\"");
        } else if (ret == -kLengthOverflow) {
            QMessageBox::information(nullptr, "提示", "输出单词链过长");
        }
        return;
    }
    std::ostringstream usedTimePromptOStringStream;
    usedTimePromptOStringStream << std::fixed << std::setprecision(3) << elapsed / 1000000000;
    std::string usedTimePrompt = "用时: " + usedTimePromptOStringStream.str() + "秒";
    QString usedTimePromptQ = QString::fromStdString(usedTimePrompt);
    usedTimeLabel->setText(usedTimePromptQ);
    QStringList strList;
    int i = 0;
    while (res[i] != nullptr) strList << QString(res[i++]);
    QString outputContent = strList.join("\n");
    outputContentTextEdit->setText(outputContent);
    for (int j = 0; j < len; ++j) {
        free(words[j]);
    }
}

void WordChainUIQt5::onOutputPathChooseButtonClicked() {
    QString curPath = QDir::currentPath();
    QString dlgTitle = "保存文件";
    QString filter = "文本文件(*.txt)";
    QString outputPath = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (!outputPath.isEmpty()) {
        QFile outputFile(outputPath);
        if (!outputFile.open(QIODevice::ReadWrite)) return;
        QString outputContent = outputContentTextEdit->toPlainText();
        outputFile.write(outputContent.toUtf8());
        outputFile.close();
    }
}

void WordChainUIQt5::onFunctionalParamNButtonClicked(bool checked) {
    if (checked) {
        limitChar[0]->clear();
        limitChar[1]->clear();
        limitChar[2]->clear();
        allowRingsRadio->setChecked(false);
        limitChar[0]->setEnabled(false);
        limitChar[1]->setEnabled(false);
        limitChar[2]->setEnabled(false);
        allowRingsRadio->setEnabled(false);
    } else {
        limitChar[0]->setEnabled(true);
        limitChar[1]->setEnabled(true);
        limitChar[2]->setEnabled(true);
        allowRingsRadio->setEnabled(true);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WordChainUIQt5 wordChainUiQt5;
    wordChainUiQt5.show();
    return QApplication::exec();
}
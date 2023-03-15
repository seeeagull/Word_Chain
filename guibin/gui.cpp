#include <QtWidgets>
#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "../compute/types.h"

#include "gui.h"

WordChainUI::WordChainUI() {
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

void WordChainUI::createMenu() {
    menuBar = new QMenuBar;
    fileMenu = new QMenu("&File", this);
    exitAction = fileMenu->addAction("E&xit");
    menuBar->addMenu(fileMenu);
    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void WordChainUI::createControlBox() {
    controlGroupBox = new QGroupBox;
    auto *layout = new QGridLayout;
    functionalParamsGroup = new QButtonGroup;
    for (int i = 0; i < NumFunctions; ++i) {
        functionalParamsRadio[i] = new QRadioButton(functions[i]);
        functionalParamsGroup->addButton(functionalParamsRadio[i]);
        layout->addWidget(functionalParamsRadio[i], 0, 4 * i, 1, 4);
    }
    functionalParamsRadio[0]->setChecked(true);
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

void WordChainUI::createDisplayBox() {
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

void WordChainUI::onInputPathChooseButtonClicked() {
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
            inputContent.append(line);
            line = inputContentTextStream.readLine();
        }
        inputPathLineEdit->setText(inputPath);
        inputContentTextEdit->setText(inputContent);
    }
}

int gen_chains_all(char *words[], int len, char *result[]) {
    result[0] = new char[2], result[0][0] = 't', result[0][1] = '\0';
    result[1] = new char[2], result[1][0] = 'e', result[1][1] = '\0';
    result[2] = new char[2], result[2][0] = 's', result[2][1] = '\0';
    result[3] = new char[2], result[3][0] = 't', result[3][1] = '\0';
    result[4] = nullptr;
    return -11;
}

int gen_chain_word(char *words[], int len, char *result[], char head, char tail, char reject, bool enable_loop) {
    result[0] = new char[2], result[0][0] = 't', result[0][1] = '\0';
    result[1] = new char[2], result[1][0] = 'e', result[1][1] = '\0';
    result[2] = new char[2], result[2][0] = 's', result[2][1] = '\0';
    result[3] = new char[2], result[3][0] = 't', result[3][1] = '\0';
    result[4] = nullptr;
    return -12;
}

int gen_chain_char(char *words[], int len, char *result[], char head, char tail, char reject, bool enable_loop) {
    result[0] = new char[2], result[0][0] = 't', result[0][1] = '\0';
    result[1] = new char[2], result[1][0] = 'e', result[1][1] = '\0';
    result[2] = new char[2], result[2][0] = 's', result[2][1] = '\0';
    result[3] = new char[2], result[3][0] = 't', result[3][1] = '\0';
    result[4] = nullptr;
    return 0;
}

void WordChainUI::onSolveButtonClicked() {
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
    for (int i = 0; i < inputContent.length(); ++i) {
        char c = inputContent[i];
        if (isupper(c)) s += (char) tolower(c);
        else if (islower(c)) s += c;
        else {
            if (s.length() > 0) {
                words[len] = new char[s.length() + 1];
                for (int j = 0; j < s.length(); ++j) {
                    words[len][j] = s[j];
                }
                words[len++][s.length()] = '\0';
                s = "";
            }
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
    std::string usedTimePrompt = "用时: " + std::to_string(abs(elapsed / 1000)) + "秒";
    QString usedTimePromptQ = QString::fromStdString(usedTimePrompt);
    usedTimeLabel->setText(usedTimePromptQ);
    QStringList strList;
    int i = 0;
    while (res[i] != nullptr) strList << QString(res[i++]);
    QString outputContent = strList.join("\n");
    outputContentTextEdit->setText(outputContent);
}

void WordChainUI::onOutputPathChooseButtonClicked() {
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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WordChainUI wordChainUi;
    wordChainUi.show();
    return QApplication::exec();
}
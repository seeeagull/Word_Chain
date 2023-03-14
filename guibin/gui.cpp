#include <QtWidgets>
#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QApplication>
#include <iostream>

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
            layout->addWidget(allowRingsRadio, 2, 6, 1, 4);
        }
    }
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

void WordChainUI::onSolveButtonClicked() {
    QString outputContent = "666";  // todo
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
        QString outputContent = "666";  // todo
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


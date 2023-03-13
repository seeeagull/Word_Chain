#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
class QLineEdit;
class QValidator;
class QRegularExpressionValidator;
class QMenu;
class QMenuBar;
class QRadioButton;
class QButtonGroup;
class QTextEdit;
class QPushButton;
QT_END_NAMESPACE

class WordChainUI : public QDialog
{
Q_OBJECT

public:
    WordChainUI();

private slots:
    void onInputPathChooseButtonClicked();
//    void onSolveButtonClicked();
    void onOutputPathChooseButtonClicked();

private:
    void createMenu();
    void createControlBox();
    void createDisplayBox();

    enum { NumFunctions = 3, NumLimits = 4};
    const char *functions[NumFunctions] = {"单词链个数", "最多单词链", "最多字母链"};
    const char *limits[NumLimits] = {"指定链首字母", "指定链尾字母", "禁止词首字母", "允许出现环"};

    QMenuBar *menuBar{};
    QMenu *fileMenu{};
    QAction *exitAction{};
    QGroupBox *controlGroupBox{};
    QButtonGroup *functionalParamsGroup{};
    QRadioButton *functionalParamsRadio[NumFunctions]{};
    QLabel *limitLabels[NumLimits-1]{};
    QLineEdit *limitChar[NumLimits-1]{};
    QRadioButton *allowRingsRadio{};
    QPushButton *inputPathChooseButton{};
    QLineEdit *chosenPath{};
    QPushButton *solveButton{};
    QPushButton *outputPathChooseButton{};
    QGroupBox *displayGroupBox{};
    QTextEdit *inputText{};
    QTextEdit *outputRes{};
};

#endif // DIALOG_H
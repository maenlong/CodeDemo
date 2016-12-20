#ifndef CODEDEMO_H
#define CODEDEMO_H

#include <QWidget>

namespace Ui {
class CodeDemo;
}

class CodeDemo : public QWidget
{
    Q_OBJECT

public:
    explicit CodeDemo(QWidget *parent = 0);
    ~CodeDemo();

private:
    Ui::CodeDemo *ui;
};

#endif // CODEDEMO_H

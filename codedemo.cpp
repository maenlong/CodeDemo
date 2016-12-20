#include "codedemo.h"
#include "ui_codedemo.h"

CodeDemo::CodeDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeDemo)
{
    ui->setupUi(this);
}

CodeDemo::~CodeDemo()
{
    delete ui;
}

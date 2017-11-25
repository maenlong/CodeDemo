#include "codedemo.h"

#include "myuiwgt.h"
#include "listviewdemo.h"
#include "select_date_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListViewDemo wgt;
    wgt.show();

//    PSelectDateView x;
//    x.show();

    return a.exec();
}

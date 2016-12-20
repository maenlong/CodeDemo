#ifndef LISTVIEWDEMO_H
#define LISTVIEWDEMO_H

#include <QWidget>
#include <QDrag>
#include <QEvent>
#include <QDebug>

#include <QDragEnterEvent>
#include <QDropEvent>

#include <QMimeData>

namespace Ui {
class ListViewDemo;
}

class ListViewDemo : public QWidget
{
    Q_OBJECT

public:
    explicit ListViewDemo(QWidget *parent = 0);
    ~ListViewDemo();

private:
    void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void slot_addItem();

    void slot_insertItem();
private:
    Ui::ListViewDemo *ui;
};

#endif // LISTVIEWDEMO_H

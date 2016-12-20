#ifndef DRAGWGT_H
#define DRAGWGT_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QDebug>

#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>

class DragWgt : public QWidget
{
    Q_OBJECT

public:
    explicit DragWgt(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
};

#endif // DRAGWGT_H

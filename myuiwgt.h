#ifndef MYUIWGT_H
#define MYUIWGT_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

namespace Ui {
class MyUiWgt;
}

class MyUiWgt : public QWidget
{
    Q_OBJECT

public:
    explicit MyUiWgt(QWidget *parent = 0);
    ~MyUiWgt();

private slots:
    void slot_startAnim();
    void slot_cycleAnim();

private:
    Ui::MyUiWgt *ui;
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool m_bLeftMouseClicked;
    bool m_bMoveEnable;
    QPoint pressPos;

    QLabel *m_pScrollLbl;

};

#endif // MYUIWGT_H

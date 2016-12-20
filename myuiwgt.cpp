#include "myuiwgt.h"
#include "ui_myuiwgt.h"
#include <QTimer>
#include <QFontMetrics>
#include <QPropertyAnimation>

const int nSpeed = 100;

MyUiWgt::MyUiWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyUiWgt)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    m_bMoveEnable = true;

    QString sName = QString(tr(" 滚动字幕测试...这是马恩龙写得一个Demo。。。"));

    QFont tipFont;
    QString strFamily = QStringLiteral("微软雅黑");
    tipFont.setFamily(strFamily);
    tipFont.setPixelSize(20);
    tipFont.setBold(true);

    QFontMetrics font(tipFont);
    int nFontWidth = font.width(sName);

    m_pScrollLbl = new QLabel(ui->ScrollBgLbl);
    m_pScrollLbl->setFixedSize(nFontWidth,ui->ScrollBgLbl->height());
    m_pScrollLbl->move((ui->ScrollBgLbl->width() - m_pScrollLbl->width())/2, 0);
//    m_pScrollLbl->setStyleSheet(
//                "color:rgba(255,255,255,100%);"
//                "background-color:rgba(255,255,255,0%);"
//                "border:1px solid #ffffff;"
//                "border-radius:5px;");
    m_pScrollLbl->setFont(tipFont);
    m_pScrollLbl->setText(sName);
    m_pScrollLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTimer::singleShot(2000,this, SLOT(slot_startAnim()) );
}

MyUiWgt::~MyUiWgt()
{
    delete ui;
}





void MyUiWgt::mouseMoveEvent(QMouseEvent *)
{
    if (m_bLeftMouseClicked)
    {
        if (m_bMoveEnable)
        {
            this->move(QCursor::pos() - pressPos);
        }
    }
}

void MyUiWgt::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftMouseClicked = true;
        pressPos = event->pos();
    }
}

void MyUiWgt::mouseReleaseEvent(QMouseEvent *)
{
    m_bLeftMouseClicked = false;
}





void MyUiWgt::slot_startAnim()
{
    int nDistance = (ui->ScrollBgLbl->width() - m_pScrollLbl->width())/2 + m_pScrollLbl->width();
    int nTime = nDistance / nSpeed*1000;

    QPropertyAnimation *anim = new QPropertyAnimation(m_pScrollLbl, "pos");
    connect(anim, SIGNAL(finished()), this, SLOT(slot_cycleAnim()));
    anim->setDuration(nTime);
    anim->setStartValue(QPoint((ui->ScrollBgLbl->width() - m_pScrollLbl->width())/2, 0));
    anim->setEndValue(QPoint(-m_pScrollLbl->width(), 0));
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->start();
}

void MyUiWgt::slot_cycleAnim()
{
    int nDistance = m_pScrollLbl->width() + ui->ScrollBgLbl->width();
    int nTime = nDistance / nSpeed*1000;

    QPropertyAnimation *anim = new QPropertyAnimation(m_pScrollLbl, "pos");
    connect(anim, SIGNAL(finished()), this, SLOT(slot_cycleAnim()));
    anim->setDuration(nTime);
    anim->setStartValue(QPoint(ui->ScrollBgLbl->width(), 0));
    anim->setEndValue(QPoint(-m_pScrollLbl->width(), 0));
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->start();
}














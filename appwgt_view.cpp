#include "appwgt_view.h"

#include <QEvent>
#if defined(Q_OS_WIN)
#include "windows.h"
#endif

#include <QDesktopWidget>
#include <QApplication>

PAppWgtView::PAppWgtView(QWidget *parent , int nDirection) : QDialog(parent) {
  m_bTitleFlag = true;
  m_nDirection = nDirection;

  QDesktopWidget *deskWidget = QApplication::desktop();
    QRect screenrect = deskWidget->screenGeometry();
  m_nWidth  = screenrect.width();
  m_nHeigth = screenrect.height();
  m_dMagnify = 1;

  setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Popup);
  setAttribute(Qt::WA_TranslucentBackground);
  setModal(true);
//    setAttribute(Qt::WA_DeleteOnClose);
  Init_widget();//初始化控件
  Init_stylesheet();//初始化样式
  Init_shortcut();//初始化快捷键
}

bool PAppWgtView::event(QEvent *event) {
  // class_ameneded 不能是custommenu的成员, 因为winidchange事件触发时, 类成员尚未初始化
#if defined(Q_OS_WIN)
  static bool class_amended = false;
  if (event->type() == QEvent::WinIdChange) {
    HWND hwnd = reinterpret_cast<HWND>(winId());
    if (class_amended == false) {
      class_amended = true;
      DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
      class_style &= ~CS_DROPSHADOW;
      ::SetClassLong(hwnd, GCL_STYLE, class_style); // windows系统函数
    }
  }
#endif
  return QWidget::event(event);
}

//移动弹窗
void PAppWgtView::MoveTo(QPoint pPos , int nDirection) {
  switch (nDirection) {
  case 0:   //箭头在上
    this->move(QPoint(pPos.x() - this->width() / 2 , pPos.y()));
    break;
  case 1:   //箭头在下
    this->move(QPoint(pPos.x() - this->width() / 2 , pPos.y() - this->height()));
    break;
  case 2:   //箭头在左
    this->move(QPoint(pPos.x(), pPos.y() - this->height() / 2));
    break;
  case 3:   //箭头在右
    break;
  default:
    break;
  }
}

//初始化控件
void PAppWgtView::Init_widget() {
  m_pTriangleLbl = new QLabel(this);
  m_pMainWgt = new QWidget(this);
  m_pTitleWgt = new QWidget(m_pMainWgt);
  m_pBackBtn = new QPushButton(m_pTitleWgt);
  m_pTitleLbl = new QLabel(m_pTitleWgt);
  m_pYesBtn = new QPushButton(m_pTitleWgt);
}

//初始化快捷键
void PAppWgtView::Init_shortcut() {
//    m_pBackBtn->setShortcut(QKeySequence(Qt::Key_Escape));
//    m_pYesBtn->setShortcut(QKeySequence(Qt::Key_Enter));
}

//初始化箭头方向和大小
void PAppWgtView::Init_dircection_size(int nWidth , int nHeight,
                                       int nDirection) {
  if (nDirection >= 0) {
    m_nDirection = nDirection;
  }
  m_nFixWidth = nWidth;
  m_nFixHeight = nHeight;
  m_pMainWgt->setFixedSize(m_nFixWidth * m_dMagnify , m_nFixHeight * m_dMagnify);
  m_pTitleWgt->setFixedSize(m_nFixWidth * m_dMagnify , 40 * m_dMagnify);
  m_pBackBtn->setFixedSize(50 * m_dMagnify , 24 * m_dMagnify);
  m_pTitleLbl->setFixedSize((m_nFixWidth - 120)*m_dMagnify , 30 * m_dMagnify);
  m_pYesBtn->setFixedSize(50 * m_dMagnify , 30 * m_dMagnify);
  m_pTitleWgt->move(0 , 0);
  m_pBackBtn->move(10 * m_dMagnify , 8 * m_dMagnify);
  m_pTitleLbl->move(60 * m_dMagnify , 5 * m_dMagnify);
  m_pYesBtn->move((m_nFixWidth - 55)*m_dMagnify , 5 * m_dMagnify);
  switch (m_nDirection) {
  case 0:   //箭头在上
    this->setFixedSize((m_nFixWidth + 0)*m_dMagnify ,
                       (m_nFixHeight + 15)*m_dMagnify);
    m_pTriangleLbl->setFixedSize(30 * m_dMagnify , 15 * m_dMagnify);
    m_pTriangleLbl->move((m_nFixWidth - 30)*m_dMagnify / 2 , 1 * m_dMagnify);
    if (m_bTitleFlag) {
      m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Up_Dark.png);");
    } else {
      m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Up.png);");
    }
    m_pMainWgt->setFixedSize(m_nFixWidth * m_dMagnify , m_nFixHeight * m_dMagnify);
    m_pMainWgt->move(0 , 15 * m_dMagnify);
    break;
  case 1:   //箭头在下
    this->setFixedSize((m_nFixWidth + 0)*m_dMagnify ,
                       (m_nFixHeight + 15)*m_dMagnify);
    m_pTriangleLbl->setFixedSize(30 * m_dMagnify , 15 * m_dMagnify);
    m_pTriangleLbl->move((m_nFixWidth - 30)*m_dMagnify / 2 ,
                         (m_nFixHeight - 1)*m_dMagnify);
    m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Down.png);");
    m_pMainWgt->setFixedSize(m_nFixWidth * m_dMagnify , m_nFixHeight * m_dMagnify);
    m_pMainWgt->move(0 , 0);
    break;
  case 2:   //箭头在左
    this->setFixedSize((m_nFixWidth + 15)*m_dMagnify ,
                       (m_nFixHeight + 0)*m_dMagnify);
    m_pTriangleLbl->setFixedSize(15 * m_dMagnify , 30 * m_dMagnify);
    m_pTriangleLbl->move(1 * m_dMagnify , (m_nFixHeight - 30)*m_dMagnify / 2);
    m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Left.png);");
    m_pMainWgt->setFixedSize(m_nFixWidth * m_dMagnify , m_nFixHeight * m_dMagnify);
    m_pMainWgt->move(15 * m_dMagnify , 0);
    break;
  case 3:   //箭头在右
    this->setFixedSize((m_nFixWidth + 15)*m_dMagnify ,
                       (m_nFixHeight + 0)*m_dMagnify);
    m_pTriangleLbl->setFixedSize(15 * m_dMagnify , 30 * m_dMagnify);
    m_pTriangleLbl->move((m_nFixWidth - 1)*m_dMagnify ,
                         (m_nFixHeight - 30)*m_dMagnify / 2);
    m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Right.png);");
    m_pMainWgt->setFixedSize(m_nFixWidth * m_dMagnify , m_nFixHeight * m_dMagnify);
    m_pMainWgt->move(0 , 0);
    break;
  default:
    break;
  }
}

//初始化样式
void PAppWgtView::Init_stylesheet() {

  this->setObjectName("PAppWgtView");
  this->setStyleSheet("QWidget#PAppWgtView{background-color:rgb(45,48,56,0%);}");

  m_pTitleWgt->setObjectName("TitleWgt");
  m_pTitleWgt->setStyleSheet("QWidget#TitleWgt{border-image:url(:/image/AppWgt/AppWgt_Title_Bg.png);}");

  m_pMainWgt->setObjectName("MainWgt");
  m_pMainWgt->setStyleSheet("QWidget#MainWgt{border:0px solid rgb(255,255,255,100%);"
                            "border-radius:5px;"
                            "background-color:rgb(66,68,73,100%);"
                            "color:rgb(255,255,255,255);}");

  //m_pBackBtn->setFont(getTextFont(14));
  //m_pTitleLbl->setFont(getTextFont(16));
  //m_pYesBtn->setFont(getTextFont(14));
  m_pBackBtn->setText("   返回");
  m_pTitleLbl->setText("自定义");
  m_pYesBtn->setText("确定");
  m_pTitleLbl->setAlignment(Qt::AlignCenter);
  m_pBackBtn->setFocusPolicy(Qt::NoFocus);
  m_pYesBtn->setFocusPolicy(Qt::NoFocus);

//  m_pBackBtn->setStyleSheet(
//    "QPushButton{color:rgb(216,216,216,100%);"
//    "border-image:url(:/image/Base/back_normal.png);}"
//    "QPushButton:pressed{color:rgb(137,137,137,100%);"
//    "border-image:url(:/image/Base/back_pressed.png);}");

  m_pTitleLbl->setStyleSheet("background-color:rgb(255,255,255,0%);"
                             "color:rgb(255,255,255,100%);");

//  m_pYesBtn->setStyleSheet(
//    "QPushButton{background-color:rgb(135,199,69,100%);"
//    "color:rgb(255,255,255,100%);border-radius:2px;}"
//    "QPushButton:pressed{background-color:rgb(112,166,62,100%);"
//    "color:rgb(255,255,255,100%);border-radius:2px;}"
//    "QPushButton:disabled{background-color:rgb(204,204,204,100%);"
//    "color:rgb(161,161,161,100%);border-radius:2px;}");
}

//绘图事件
void PAppWgtView::paintEvent(QPaintEvent *) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

//移动三角坐标
void PAppWgtView::setTriangleMove(double dx, double dy) {
  m_pTriangleLbl->move(m_pTriangleLbl->x() + dx , m_pTriangleLbl->y() + dy);
}

//自定义表头样式
void PAppWgtView::CustomTitle(bool bWgtFlag , bool bBackFlag ,
                              QString sTitleStr , bool bYesFlag) {
  m_bTitleFlag = bWgtFlag;
  if (m_nDirection == 0) {
    if (m_bTitleFlag) {
      m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Up_Dark.png);");
    } else {
      m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Up.png);");
    }
  }
  if (bWgtFlag) {
    m_pTitleWgt->show();
  } else {
    m_pTitleWgt->hide();
  }
  if (bBackFlag) {
    m_pBackBtn->show();
  } else {
    m_pBackBtn->hide();
  }
  m_sTitleStr = sTitleStr;
  m_pTitleLbl->setText(sTitleStr);
  if (bYesFlag) {
    m_pYesBtn->show();
  } else {
    m_pYesBtn->hide();
  }
}



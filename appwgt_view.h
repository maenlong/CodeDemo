#ifndef APPWGT_H
#define APPWGT_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QLayout>
#include <QPainter>
#include <QStyleOption>
#include <QShortcut>

class PAppWgtView : public QDialog {
  Q_OBJECT

    bool event(QEvent *event);

public:
  explicit PAppWgtView(QWidget *parent = 0 , int nDirection = 0);
  void MoveTo(QPoint pPos, int nDirection = 0);

  QLabel *m_pTriangleLbl;
  QWidget *m_pMainWgt;
  QWidget *m_pTitleWgt;
  QPushButton *m_pBackBtn;
  QLabel *m_pTitleLbl;
  QPushButton *m_pYesBtn;

  int m_nWidth;
  int m_nHeigth;
  double m_dMagnify;
  QString m_sTitleStr;
  bool m_bTitleFlag;

  int m_nDirection;
  int m_nFixHeight;
  int m_nFixWidth;

  void Init_widget();
  void Init_stylesheet();
  void Init_shortcut();
  void paintEvent(QPaintEvent *);

  void Init_dircection_size(int nWidth, int nHeight, int nDirection = -1);
  void CustomTitle(bool bWgtFlag = true ,
                   bool bBackFlag = true ,
                   QString sTitleStr = "自定义" ,
                   bool bYesFlag = true);
  void setTriangleMove(double dx, double dy);
};

#endif // APPWGT_H

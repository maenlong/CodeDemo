#include "select_date_view.h"

//获取文字公共字体
QFont getTextFont(int nSize , bool bBold = false)
{
  QFont myFont;
  myFont.setFamily("Microsoft YaHei");/*Hiragino Sans GB W3*/
  myFont.setPixelSize(nSize);
  myFont.setBold(bBold);
  return myFont;
}

//获取数字公共字体
QFont getNumFont(int nSize , bool bBold = false)
{
  QFont myFont;
  myFont.setFamily("Arial");
  myFont.setPixelSize(nSize);
  myFont.setBold(bBold);
  return myFont;
}

PSelectDateView::PSelectDateView(QWidget *parent ,
                                 int nDirection) : PAppWgtView(parent , nDirection) {
  Init_dircection_size(352 , 416);  //初始化箭头方向和大小
  CustomTitle(true, true, "选择日期", true);
  m_pYesBtn->move(m_pTitleWgt->width() - 16 * m_dMagnify
                  - m_pYesBtn->width(), 5 * m_dMagnify);
  m_pTriangleLbl->setStyleSheet("border-image:url(:/image/AppWgt/Triangle_Up.png);");
  m_pTitleWgt->setStyleSheet("QWidget#TitleWgt{background-color:rgb(45,48,56,0%);}");

  m_bNeedTime = true;
  m_nPage = 0;
  m_nNum = -1;

  Init_widget_son();//初始化控件
  Init_stylesheet_son();//初始化样式
  Init_conncet_son();//初始化链接
  m_CurDate = QDate::currentDate();
  m_JumpDate = QDate::currentDate();
  m_CurTime = QTime::currentTime();

  JumpPage(0);
}

//初始化控件
void PSelectDateView::Init_widget_son() {

  m_pDateWgt = new QWidget(m_pMainWgt);
  m_pDateWgt->setFixedSize(352 * m_dMagnify, 376 * m_dMagnify);
  m_pDateWgt->move(0, 40 * m_dMagnify);

  m_pMonthTitleWgt = new QWidget(m_pDateWgt);
  m_pMonthTitleWgt->setFixedSize(320 * m_dMagnify, 40 * m_dMagnify);

  m_pMonthLeftBtn = new QPushButton(m_pMonthTitleWgt);
  m_pMonthLeftBtn->setFixedSize(10 * m_dMagnify, 13 * m_dMagnify);

  m_pMonthTipLbl = new QLabel(m_pMonthTitleWgt);
//  m_pMonthTipLbl->setFixedSize(72 * m_dMagnify, 40 * m_dMagnify);

  m_pYearTipLbl = new QLabel(m_pMonthTitleWgt);
//  m_pYearTipLbl->setFixedSize(64 * m_dMagnify, 40 * m_dMagnify);

  m_pMonthRightBtn = new QPushButton(m_pMonthTitleWgt);
  m_pMonthRightBtn->setFixedSize(10 * m_dMagnify, 13 * m_dMagnify);

  QHBoxLayout *pHL_Date_Title = new QHBoxLayout(m_pMonthTitleWgt);
  pHL_Date_Title->setSpacing(0);
  pHL_Date_Title->setMargin(0);
  pHL_Date_Title->addSpacing(66 * m_dMagnify);
  pHL_Date_Title->addWidget(m_pMonthLeftBtn, 0, Qt::AlignCenter);
  pHL_Date_Title->addStretch(1);
  pHL_Date_Title->addWidget(m_pYearTipLbl, 0, Qt::AlignCenter);
  pHL_Date_Title->addSpacing(10 * m_dMagnify);
  pHL_Date_Title->addWidget(m_pMonthTipLbl, 0, Qt::AlignCenter);
  pHL_Date_Title->addStretch(1);
  pHL_Date_Title->addWidget(m_pMonthRightBtn, 0, Qt::AlignCenter);
  pHL_Date_Title->addSpacing(66 * m_dMagnify);

  QWidget *pCalBgWgt = new QWidget(m_pDateWgt);
  pCalBgWgt->setStyleSheet("background-color:rgb(255,255,255,255);");
  pCalBgWgt->setFixedSize(320 * m_dMagnify, 320 * m_dMagnify);
  m_pCalWgt = new QCalendarWidget(pCalBgWgt);
  m_pCalWgt->setFixedSize(310 * m_dMagnify, 310 * m_dMagnify);

  QGridLayout *pGL_Cal = new QGridLayout(pCalBgWgt);
  pGL_Cal->setSpacing(0);
  pGL_Cal->setContentsMargins(5 * m_dMagnify, 0, 5 * m_dMagnify, 10 * m_dMagnify);
  pGL_Cal->addWidget(m_pCalWgt, 0, 0, 1, 1, Qt::AlignCenter);

  QVBoxLayout *pVL_Date_main = new QVBoxLayout(m_pDateWgt);
  pVL_Date_main->setSpacing(0);
  pVL_Date_main->setMargin(0);
  pVL_Date_main->addWidget(m_pMonthTitleWgt, 0, Qt::AlignCenter);
  pVL_Date_main->addWidget(pCalBgWgt, 0, Qt::AlignCenter);
  pVL_Date_main->addStretch(1);

  //----------------------------------------------------------------------------------------------------

  m_pTimeWgt = new QWidget(m_pMainWgt);
  m_pTimeWgt->setFixedSize(352 * m_dMagnify, 376 * m_dMagnify);
  m_pTimeWgt->move(0, 40 * m_dMagnify);

  m_pDateTitleWgt = new QWidget(m_pTimeWgt);
  m_pDateTitleWgt->setFixedSize(320 * m_dMagnify, 40 * m_dMagnify);

  m_pDayLeftBtn = new QPushButton(m_pDateTitleWgt);
  m_pDayLeftBtn->setFixedSize(10 * m_dMagnify, 13 * m_dMagnify);

  m_pYearMonthTipLbl = new QLabel(m_pDateTitleWgt);
//  m_pYearMonthTipLbl->setFixedSize(72 * m_dMagnify, 40 * m_dMagnify);

  m_pDayTipLbl = new QLabel(m_pDateTitleWgt);
//  m_pDayTipLbl->setFixedSize(64 * m_dMagnify, 40 * m_dMagnify);

  m_pDayRightBtn = new QPushButton(m_pDateTitleWgt);
  m_pDayRightBtn->setFixedSize(10 * m_dMagnify, 13 * m_dMagnify);

  QHBoxLayout *pHL_Time_Title = new QHBoxLayout(m_pDateTitleWgt);
  pHL_Time_Title->setSpacing(0);
  pHL_Time_Title->setMargin(0);
  pHL_Time_Title->addSpacing(66 * m_dMagnify);
  pHL_Time_Title->addWidget(m_pDayLeftBtn, 0, Qt::AlignCenter);
  pHL_Time_Title->addStretch(1);
  pHL_Time_Title->addWidget(m_pYearMonthTipLbl, 0, Qt::AlignCenter);
  pHL_Time_Title->addSpacing(10 * m_dMagnify);
  pHL_Time_Title->addWidget(m_pDayTipLbl, 0, Qt::AlignCenter);
  pHL_Time_Title->addStretch(1);
  pHL_Time_Title->addWidget(m_pDayRightBtn, 0, Qt::AlignCenter);
  pHL_Time_Title->addSpacing(66 * m_dMagnify);

  m_pSelectTimeWgt = new QWidget(m_pTimeWgt);
  m_pSelectTimeWgt->setFixedSize(320 * m_dMagnify, 320 * m_dMagnify);

  QVBoxLayout *pVL_Time_main = new QVBoxLayout(m_pTimeWgt);
  pVL_Time_main->setSpacing(0);
  pVL_Time_main->setMargin(0);
  pVL_Time_main->addWidget(m_pDateTitleWgt, 0, Qt::AlignCenter);
  pVL_Time_main->addWidget(m_pSelectTimeWgt, 0, Qt::AlignCenter);
  pVL_Time_main->addStretch(1);

  //----------------------------------------------------------------------------------------------------

  m_pHourUpBtn = new QPushButton(m_pSelectTimeWgt);
  m_pHourUpBtn->setFixedSize(160 * m_dMagnify, 60 * m_dMagnify);
  m_pHourDownBtn = new QPushButton(m_pSelectTimeWgt);
  m_pHourDownBtn->setFixedSize(160 * m_dMagnify, 60 * m_dMagnify);
  QVBoxLayout *pVL_Hour = new QVBoxLayout;
  pVL_Hour->setSpacing(0);
  pVL_Hour->setMargin(0);
  pVL_Hour->addWidget(m_pHourUpBtn, 0, Qt::AlignHCenter);
  pVL_Hour->addStretch(1);
  pVL_Hour->addWidget(m_pHourDownBtn, 0, Qt::AlignHCenter);

  m_pMinuteUpBtn = new QPushButton(m_pSelectTimeWgt);
  m_pMinuteUpBtn->setFixedSize(160 * m_dMagnify, 60 * m_dMagnify);
  m_pMinuteDownBtn = new QPushButton(m_pSelectTimeWgt);
  m_pMinuteDownBtn->setFixedSize(160 * m_dMagnify, 60 * m_dMagnify);
  QVBoxLayout *pVL_Minute = new QVBoxLayout;
  pVL_Minute->setSpacing(0);
  pVL_Minute->setMargin(0);
  pVL_Minute->addWidget(m_pMinuteUpBtn, 0, Qt::AlignHCenter);
  pVL_Minute->addStretch(1);
  pVL_Minute->addWidget(m_pMinuteDownBtn, 0, Qt::AlignHCenter);

  QHBoxLayout *pHL_Time = new QHBoxLayout(m_pSelectTimeWgt);
  pHL_Time->setSpacing(0);
  pHL_Time->setMargin(0);
  pHL_Time->addLayout(pVL_Hour, 0);
  pHL_Time->addLayout(pVL_Minute, 0);

  QLabel *pShiTipLbl = new QLabel(m_pSelectTimeWgt);
  pShiTipLbl->setText("时");
  pShiTipLbl->setFont(getTextFont(14));
  pShiTipLbl->move(105 * m_dMagnify , 155 * m_dMagnify);

  QLabel *pFenTipLbl = new QLabel(m_pSelectTimeWgt);
  pFenTipLbl->setText("分");
  pFenTipLbl->setFont(getTextFont(14));
  pFenTipLbl->move(265 * m_dMagnify , 155 * m_dMagnify);

  m_lHourLblList.clear();
  for (int a = 0 ; a < 5 ; a++) {
    QLabel *pItemLbl = new QLabel(m_pSelectTimeWgt);
    pItemLbl->setAlignment(Qt::AlignCenter);
    pItemLbl->setFixedSize(60 * m_dMagnify , 60 * m_dMagnify);
    m_lHourLblList << pItemLbl;
  }

  m_lHourLblList.at(0)->setFont(getNumFont(18));
  m_lHourLblList.at(1)->setFont(getNumFont(20));
  m_lHourLblList.at(2)->setFont(getNumFont(32));
  m_lHourLblList.at(3)->setFont(getNumFont(20));
  m_lHourLblList.at(4)->setFont(getNumFont(18));

  m_lHourLblList.at(0)->setStyleSheet("color:rgb(153,153,153);border:0px;");
  m_lHourLblList.at(1)->setStyleSheet("color:rgb(109,109,109);border:0px;");
  m_lHourLblList.at(2)->setStyleSheet("color:rgb(255,137,61);border:0px;");
  m_lHourLblList.at(3)->setStyleSheet("color:rgb(109,109,109);border:0px;");
  m_lHourLblList.at(4)->setStyleSheet("color:rgb(153,153,153);border:0px;");

  m_lHourLblList.at(0)->move(50 * m_dMagnify, 50 * m_dMagnify);
  m_lHourLblList.at(1)->move(50 * m_dMagnify, 80 * m_dMagnify);
  m_lHourLblList.at(2)->move(50 * m_dMagnify, 130 * m_dMagnify);
  m_lHourLblList.at(3)->move(50 * m_dMagnify, 180 * m_dMagnify);
  m_lHourLblList.at(4)->move(50 * m_dMagnify, 210 * m_dMagnify);

  m_lMinuteLblList.clear();
  for (int a = 0 ; a < 5 ; a++) {
    QLabel *pItemLbl = new QLabel(m_pSelectTimeWgt);
    pItemLbl->setAlignment(Qt::AlignCenter);
    pItemLbl->setFixedSize(60 * m_dMagnify , 60 * m_dMagnify);
    m_lMinuteLblList << pItemLbl;
  }

  m_lMinuteLblList.at(0)->setFont(getNumFont(18));
  m_lMinuteLblList.at(1)->setFont(getNumFont(20));
  m_lMinuteLblList.at(2)->setFont(getNumFont(32));
  m_lMinuteLblList.at(3)->setFont(getNumFont(20));
  m_lMinuteLblList.at(4)->setFont(getNumFont(18));

  m_lMinuteLblList.at(0)->setStyleSheet("color:rgb(153,153,153);border:0px;");
  m_lMinuteLblList.at(1)->setStyleSheet("color:rgb(109,109,109);border:0px;");
  m_lMinuteLblList.at(2)->setStyleSheet("color:rgb(255,137,61);border:0px;");
  m_lMinuteLblList.at(3)->setStyleSheet("color:rgb(109,109,109);border:0px;");
  m_lMinuteLblList.at(4)->setStyleSheet("color:rgb(153,153,153);border:0px;");

  m_lMinuteLblList.at(0)->move(210 * m_dMagnify, 50 * m_dMagnify);
  m_lMinuteLblList.at(1)->move(210 * m_dMagnify, 80 * m_dMagnify);
  m_lMinuteLblList.at(2)->move(210 * m_dMagnify, 130 * m_dMagnify);
  m_lMinuteLblList.at(3)->move(210 * m_dMagnify, 180 * m_dMagnify);
  m_lMinuteLblList.at(4)->move(210 * m_dMagnify, 210 * m_dMagnify);
}

//初始化样式
void PSelectDateView::Init_stylesheet_son() {

  this->setFocusPolicy(Qt::NoFocus);

  m_pMonthTitleWgt->setStyleSheet("QWidget{background-color:rgb(216,216,216,100%);}");
                                 // "color:rgb(0,0,0,100%);border-radius:0px;}");
  m_pDateTitleWgt->setStyleSheet("QWidget{background-color:rgb(216,216,216,100%);}");
                                 // "color:rgb(0,0,0,100%);border-radius:0px;}");

//  m_pMonthLeftBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/MonthLeft.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/MonthLeft_Press.png);}");
//  m_pDayLeftBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/MonthLeft.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/MonthLeft_Press.png);}");
//  m_pMonthRightBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/MonthRight.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/MonthRight_Press.png);}");
//  m_pDayRightBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/MonthRight.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/MonthRight_Press.png);}");

  m_pCalWgt->setStyleSheet("selection-background-color:rgb(255,138,61,255);"
                           "selection-color: rgb(255, 255, 255, 255);");

  m_pYearTipLbl->setFont(getTextFont(14));
  m_pYearTipLbl->setAlignment(Qt::AlignCenter);
  m_pYearTipLbl->setText(QString::number(m_pCalWgt->yearShown()) + "年");
  m_pYearMonthTipLbl->setFont(getTextFont(14));
  m_pYearMonthTipLbl->setAlignment(Qt::AlignCenter);
  m_pYearMonthTipLbl->setText(QString::number(m_pCalWgt->yearShown()) + "年"
                              + QString::number(m_pCalWgt->monthShown()) + "月");

  m_pMonthTipLbl->setFont(getTextFont(20));
  m_pMonthTipLbl->setAlignment(Qt::AlignCenter);
  m_pMonthTipLbl->setText(QString::number(m_pCalWgt->monthShown()) + "月");
  m_pDayTipLbl->setFont(getTextFont(20));
  m_pDayTipLbl->setAlignment(Qt::AlignCenter);
  m_pDayTipLbl->setText(QString::number(m_pCalWgt->monthShown()) + "日");

  m_pCalWgt->setFont(getNumFont(20));
  m_pCalWgt->setFocusPolicy(Qt::NoFocus);
  m_pCalWgt->setShortcutEnabled(0, false);
  m_pCalWgt->setFirstDayOfWeek(Qt::DayOfWeek(Qt::Sunday));
  m_pCalWgt->setLocale(QLocale(QLocale::Chinese, QLocale::China));
  m_pCalWgt->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat(
                                         QCalendarWidget::SingleLetterDayNames));
  m_pCalWgt->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat(
                                       QCalendarWidget::NoVerticalHeader));
  m_pCalWgt->setNavigationBarVisible(false);
  m_pCalWgt->setDateEditEnabled(true);

  QTextCharFormat format;
  format.setBackground(QColor(255, 255, 255, 255));
  format.setForeground(QColor(0, 0, 0, 255));

  m_pCalWgt->setWeekdayTextFormat(Qt::Monday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Tuesday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Wednesday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Thursday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Friday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Saturday, format);
  m_pCalWgt->setWeekdayTextFormat(Qt::Sunday, format);

  m_pHourUpBtn->setFont(getTextFont(20));
  m_pHourDownBtn->setFont(getTextFont(20));
  m_pMinuteUpBtn->setFont(getTextFont(20));
  m_pMinuteDownBtn->setFont(getTextFont(20));

  m_pSelectTimeWgt->setObjectName("SelectTime");
//  m_pSelectTimeWgt->setStyleSheet(
//    "QWidget#SelectTime{border-image:url(:/image/AppWgt/SelectTime.png);}"
//    "QPushButton{color:rgb(182,182,182);border:1px;background-color:rgb(255,255,255,0);}"
//    "QLabel{color:rgb(255,137,61);border:1px;background-color:rgb(255,255,255,0);}");

//  m_pHourUpBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/TimeUp.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/TimeUp_Press.png);}");
//  m_pMinuteUpBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/TimeUp.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/TimeUp_Press.png);}");

//  m_pHourDownBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/TimeDown.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/TimeDown_Press.png);}");
//  m_pMinuteDownBtn->setStyleSheet(
//    "QPushButton{border-image:url(:/image/AppWgt/TimeDown.png);}"
//    "QPushButton:pressed{border-image:url(:/image/AppWgt/TimeDown_Press.png);}");
}

//初始化链接
void PSelectDateView::Init_conncet_son() {

  connect(m_pYesBtn, SIGNAL(clicked()),
          this, SLOT(slot_YesBtn_clicked()));

  connect(m_pBackBtn, SIGNAL(clicked()),
          this, SLOT(slot_BackBtn_clicked()));

  connect(m_pMonthLeftBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeMonth()));

  connect(m_pMonthRightBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeMonth()));

  connect(m_pCalWgt, SIGNAL(currentPageChanged(int, int)),
          this, SLOT(slot_Pagechanged(int, int)));

  connect(m_pCalWgt, SIGNAL(clicked(QDate)),
          this, SLOT(slot_CalWgt_clicked(QDate)));

  connect(m_pDayLeftBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeDay()));

  connect(m_pDayRightBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeDay()));

  connect(m_pHourUpBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeHour()));

  connect(m_pHourDownBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeHour()));

  connect(m_pMinuteUpBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeMinute()));

  connect(m_pMinuteDownBtn, SIGNAL(clicked()),
          this, SLOT(slot_ChangeMinute()));
}

//切换页面
void PSelectDateView::JumpPage(int nPage) {

  if (nPage == 0) {

    QTextCharFormat format;
    format.setBackground(QColor(255, 255, 255, 255));
    format.setForeground(QColor(0, 0, 0, 255));
    m_pCalWgt->setDateTextFormat(m_JumpDate, format);

    QTextCharFormat end_format;
    end_format.setBackground(QColor(255, 138, 61, 255));
    end_format.setForeground(QColor(255, 255, 255, 255));
    m_pCalWgt->setDateTextFormat(m_CurDate, end_format);

    m_pCalWgt->setSelectedDate(m_CurDate);
    slot_CalWgt_clicked(m_CurDate);

    m_pBackBtn->setText(" 取消    ");
    m_pBackBtn->move(10 * m_dMagnify , 8 * m_dMagnify);
    if (m_bNeedTime) {
      m_pYesBtn->setEnabled(false);
    } else {
      m_pYesBtn->setEnabled(true);
    }
    m_pTitleLbl->setText("选择日期");
//    m_pBackBtn->setStyleSheet(
//      "QPushButton{color:rgb(216,216,216,100%);"
//      "border-image:url(:/image/Base/back_blank.png);}"
//      "QPushButton:pressed{color:rgb(137,137,137,100%);"
//      "border-image:url(:/image/Base/back_blank.png);}");
    m_pDateWgt->setVisible(true);
    m_pTimeWgt->setVisible(false);

  } else {
    m_pYearMonthTipLbl->setText(QString::number(m_CurDate.year()) + "年"
                                + QString::number(m_CurDate.month()) + "月");
    m_pDayTipLbl->setText(QString::number(m_CurDate.day()) + "日");
    m_JumpDate = m_CurDate;
    setCurTime();//设置当前时间

    m_pBackBtn->setText("  返回");
    m_pBackBtn->move(16 * m_dMagnify , 8 * m_dMagnify);
    if (m_bNeedTime) {
      m_pYesBtn->setEnabled(true);
    }
    m_pTitleLbl->setText("选择时间");
//    m_pBackBtn->setStyleSheet(
//      "QPushButton{color:rgb(216,216,216,100%);"
//      "border-image:url(:/image/Base/back_normal.png);}"
//      "QPushButton:pressed{color:rgb(137,137,137,100%);"
//      "border-image:url(:/image/Base/back_pressed.png);}");
    m_pDateWgt->setVisible(false);
    m_pTimeWgt->setVisible(true);
  }
  m_nPage = nPage;
}

//确定按钮点击
void PSelectDateView::slot_YesBtn_clicked() {
  if (m_bNeedTime) {
    if (m_nPage == 0) {
      JumpPage(1);
    } else if (m_nPage == 1) {
      //  if (m_CurDate != NULL) {
      QDateTime datetime;
      datetime.setDate(m_CurDate);
      datetime.setTime(m_CurTime);

      if (datetime < QDateTime::currentDateTime()) {
        qDebug("此时间已过，请输入有效时间！");
        return;
      }
      emit signal_SendDateTime(datetime);
      this->close();
      //  }
    }
  } else {
    emit signal_SendDate(m_CurDate);
    emit signal_Sender_Date(m_nNum, m_CurDate);
    this->close();
  }
}

//返回按钮点击
void PSelectDateView::slot_BackBtn_clicked() {
  if (m_nPage == 0) {
    this->close();
  } else if (m_nPage == 1) {
    JumpPage(0);
  }
}

//翻页月份改变
void PSelectDateView::slot_ChangeMonth() {
  QPushButton *pSender = qobject_cast<QPushButton *>(sender());
  if (pSender == m_pMonthLeftBtn) {
    m_pCalWgt->showPreviousMonth();
  } else if (pSender == m_pMonthRightBtn) {
    m_pCalWgt->showNextMonth();
  }
}

//日期改变
void PSelectDateView::slot_ChangeDay() {
  QPushButton *pSender = qobject_cast<QPushButton *>(sender());
  if (pSender == m_pDayLeftBtn) {
    m_CurDate = m_CurDate.addDays(-1);
  } else if (pSender == m_pDayRightBtn) {
    m_CurDate = m_CurDate.addDays(1);
  }
  m_pYearMonthTipLbl->setText(QString::number(m_CurDate.year()) + "年"
                              + QString::number(m_CurDate.month()) + "月");
  m_pDayTipLbl->setText(QString::number(m_CurDate.day()) + "日");
}

//小时改变
void PSelectDateView::slot_ChangeHour() {
  QPushButton *pSender = qobject_cast<QPushButton *>(sender());
  if (pSender == m_pHourUpBtn) {
    ScrollAnimation(0, 1);
    setCurTime(m_CurTime.addSecs(60 * 60));
  } else if (pSender == m_pHourDownBtn) {
    ScrollAnimation(0, 0);
    setCurTime(m_CurTime.addSecs(-60 * 60));
  }
}

//分钟改变
void PSelectDateView::slot_ChangeMinute() {
  QPushButton *pSender = qobject_cast<QPushButton *>(sender());
  if (pSender == m_pMinuteUpBtn) {
    ScrollAnimation(1, 1);
    setCurTime(m_CurTime.addSecs(60));
  } else if (pSender == m_pMinuteDownBtn) {
    ScrollAnimation(1, 0);
    setCurTime(m_CurTime.addSecs(-60));
  }
}
//时间滚动动画   nType : 0.小时 1.分钟   nDirection : 0.向上 1.向下
void PSelectDateView::ScrollAnimation(int nType , int nDirection) {

  if (nType == 0) {
    if (nDirection == 0) {
      QParallelAnimationGroup *group = new QParallelAnimationGroup;
      for (int a = 0 ; a < m_lHourLblList.count() ; a++) {
        QPropertyAnimation *anim = new QPropertyAnimation(m_lHourLblList.at(a), "pos");
        anim->setDuration(100);
        if (a == 0) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 40 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 50 * m_dMagnify));
        } else if (a == 1) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 50 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 80 * m_dMagnify));
        } else if (a == 2) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 80 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 130 * m_dMagnify));
        } else if (a == 3) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 130 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 180 * m_dMagnify));
        } else if (a == 4) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 180 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 210 * m_dMagnify));
        }
        anim->setEasingCurve(QEasingCurve::Linear);
        group->addAnimation(anim);
      }
      group->start();
    } else if (nDirection == 1) {
      QParallelAnimationGroup *group = new QParallelAnimationGroup;
      for (int a = 0 ; a < m_lHourLblList.count() ; a++) {
        QPropertyAnimation *anim = new QPropertyAnimation(m_lHourLblList.at(a), "pos");
        anim->setDuration(100);
        if (a == 0) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 80 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 50 * m_dMagnify));
        } else if (a == 1) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 130 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 80 * m_dMagnify));
        } else if (a == 2) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 180 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 130 * m_dMagnify));
        } else if (a == 3) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 210 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 180 * m_dMagnify));
        } else if (a == 4) {
          anim->setStartValue(QPoint(50 * m_dMagnify , 220 * m_dMagnify));
          anim->setEndValue(QPoint(50 * m_dMagnify , 210 * m_dMagnify));
        }
        anim->setEasingCurve(QEasingCurve::Linear);
        group->addAnimation(anim);
      }
      group->start();
    }
  } else if (nType == 1) {
    if (nDirection == 0) {
      QParallelAnimationGroup *group = new QParallelAnimationGroup;
      for (int a = 0 ; a < m_lMinuteLblList.count() ; a++) {
        QPropertyAnimation *anim = new QPropertyAnimation(m_lMinuteLblList.at(a),
            "pos");
        anim->setDuration(100);
        if (a == 0) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 40 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 50 * m_dMagnify));
        } else if (a == 1) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 50 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 80 * m_dMagnify));
        } else if (a == 2) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 80 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 130 * m_dMagnify));
        } else if (a == 3) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 130 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 180 * m_dMagnify));
        } else if (a == 4) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 180 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 210 * m_dMagnify));
        }
        anim->setEasingCurve(QEasingCurve::Linear);
        group->addAnimation(anim);
      }
      group->start();
    } else if (nDirection == 1) {
      QParallelAnimationGroup *group = new QParallelAnimationGroup;
      for (int a = 0 ; a < m_lMinuteLblList.count() ; a++) {
        QPropertyAnimation *anim = new QPropertyAnimation(m_lMinuteLblList.at(a),
            "pos");
        anim->setDuration(100);
        if (a == 0) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 80 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 50 * m_dMagnify));
        } else if (a == 1) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 130 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 80 * m_dMagnify));
        } else if (a == 2) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 180 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 130 * m_dMagnify));
        } else if (a == 3) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 210 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 180 * m_dMagnify));
        } else if (a == 4) {
          anim->setStartValue(QPoint(210 * m_dMagnify , 220 * m_dMagnify));
          anim->setEndValue(QPoint(210 * m_dMagnify , 210 * m_dMagnify));
        }
        anim->setEasingCurve(QEasingCurve::Linear);
        group->addAnimation(anim);
      }
      group->start();
    }
  }

}

//日历翻页
void PSelectDateView::slot_Pagechanged(int nyear , int nmonth) {
  m_pYearTipLbl->setText(QString::number(nyear) + "年");
  m_pMonthTipLbl->setText(QString::number(nmonth) + "月");
}

//日期点击
void PSelectDateView::slot_CalWgt_clicked(QDate date) {

  QTextCharFormat format;
  format.setBackground(QColor(255, 255, 255, 255));
  format.setForeground(QColor(0, 0, 0, 255));
  m_pCalWgt->setDateTextFormat(m_CurDate, format);

  QTextCharFormat end_format;
  end_format.setBackground(QColor(255, 138, 61, 255));
  end_format.setForeground(QColor(255, 255, 255, 255));
  m_pCalWgt->setDateTextFormat(date, end_format);

  m_CurDate = date;

  if (m_bNeedTime) {
    JumpPage(1);
  }
}

//保存发送者
void PSelectDateView::setSender(int nNum) {
  m_nNum = nNum;
}

//是否需要时间
void PSelectDateView::setNeedTime(bool bflag) {

  m_bNeedTime = bflag;
  m_pYesBtn->setEnabled(false);

  m_pCalWgt->setStyleSheet("selection-background-color:rgb(255,138,61,0);"
                           "selection-color: rgb(0, 0, 0, 255);");

}

//设置当前时间
void PSelectDateView::setCurTime(QTime curTime) {

  m_CurTime = curTime;
  for (int a = 0 ; a < m_lHourLblList.count() ; a++) {
    if ((curTime.hour() - 2 + a) < 0) {
      m_lHourLblList.at(a)->setText(QString::number(curTime.hour() - 2 + a + 24));
    } else if ((curTime.hour() - 2 + a) > 23) {
      m_lHourLblList.at(a)->setText(QString::number(curTime.hour() - 2 + a - 24));
    } else {
      m_lHourLblList.at(a)->setText(QString::number(curTime.hour() - 2 + a));
    }
  }

  for (int a = 0 ; a < m_lMinuteLblList.count() ; a++) {
    if ((curTime.minute() - 2 + a) < 0) {
      m_lMinuteLblList.at(a)->setText(QString::number(curTime.minute() - 2 + a + 60));
    } else if ((curTime.minute() - 2 + a) > 59) {
      m_lMinuteLblList.at(a)->setText(QString::number(curTime.minute() - 2 + a - 60));
    } else {
      m_lMinuteLblList.at(a)->setText(QString::number(curTime.minute() - 2 + a));
    }
  }
}

#ifndef PSELECTDATEVIEW_H
#define PSELECTDATEVIEW_H

#include "appwgt_view.h"
#include <QCalendarWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class PSelectDateView : public PAppWgtView {
  Q_OBJECT

 public:
  explicit PSelectDateView(QWidget *parent = 0 , int nDirection = 0);
  void setSender(int nNum);
  void setNeedTime(bool bflag = true);
  void setCurTime(QTime curTime = QTime::currentTime());

signals:
  void signal_Sender_Date(int nNum, QDate date);
  void signal_SendDate(QDate date);
  void signal_SendDateTime(QDateTime datetime);

 private slots:
  void slot_YesBtn_clicked();//确定按钮点击
  void slot_BackBtn_clicked();//返回按钮点击
  void slot_ChangeMonth();//月份改变
  void slot_ChangeDay();//日期改变
  void slot_ChangeHour();//小时改变
  void slot_ChangeMinute();//分钟改变
  void slot_Pagechanged(int nyear, int nmonth);//日历翻页
  void slot_CalWgt_clicked(QDate date);//日期点击

private:
  int m_nNum;
  int m_nPage;
  bool m_bNeedTime;
  QDate m_CurDate;
  QDate m_JumpDate;
  QTime m_CurTime;

  QWidget *m_pDateWgt;
  QWidget *m_pMonthTitleWgt;           //月份标题栏
  QPushButton *m_pMonthLeftBtn;       //上一月按钮
  QLabel *m_pMonthTipLbl;                  //月份提示
  QLabel *m_pYearTipLbl;                      //年份提示
  QPushButton *m_pMonthRightBtn;     //下一月按钮
  QCalendarWidget *m_pCalWgt;          //测试日历

  QWidget *m_pTimeWgt;
  QWidget *m_pDateTitleWgt;             //日期标题栏
  QPushButton *m_pDayLeftBtn;         //前一天按钮
  QLabel *m_pYearMonthTipLbl;         //年月提示
  QLabel *m_pDayTipLbl;                     //日提示
  QPushButton *m_pDayRightBtn;        //后一天按钮
  QWidget *m_pSelectTimeWgt;          //时间选择

  QPushButton *m_pHourUpBtn;             //小时向上
  QPushButton *m_pHourDownBtn;        //小时向下
  QPushButton *m_pMinuteUpBtn;         //分钟向上
  QPushButton *m_pMinuteDownBtn;    //分钟向下

  QList <QLabel *> m_lHourLblList;       //小时滚轮
  QList <QLabel *> m_lMinuteLblList;   //分钟滚轮

  void Init_widget_son();              //初始化控件
  void Init_stylesheet_son();        //初始化样式
  void Init_conncet_son();           //初始化链接
  void JumpPage(int nPage);      //切换页面
  void ScrollAnimation(int nType, int nDirection);//时间滚动动画
  // nType : 0.小时 1.分钟   nDirection : 0.向上 1.向下
};

#endif // PSELECTDATEVIEW_H

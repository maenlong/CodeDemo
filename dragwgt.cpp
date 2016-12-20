#include "dragwgt.h"
#include "ui_dragwgt.h"

DragWgt::DragWgt(QWidget *parent) :
    QWidget(parent)
{
    setAcceptDrops(true);

    QLabel *item = new QLabel (this);
    item->setFixedSize(50,50);
    item->setStyleSheet("background-color:rgb(255,155,55);");
    item->setAttribute(Qt::WA_DeleteOnClose);
    item->show();
}

void DragWgt::mousePressEvent (QMouseEvent *event)
{
   if (event->button() != Qt::LeftButton)
   {
      event->ignore();
      return;
   }

   QLabel *item = (QLabel *)(this->childAt(event->pos()));
   if (item == NULL)
   {
      event->ignore();
      return;
   }
   else
   {
      QByteArray exData;
      QDataStream dataStream (&exData, QIODevice::WriteOnly);
      dataStream<<event->pos() - item->pos();
      dataStream<<QString("1580");
      dataStream<<QString("MEL");
      dataStream<<0;

      QMimeData *mimeData = new QMimeData;
      mimeData->setData("application/x-draganddrop", exData);
      mimeData->setText(tr("Drag and Drop"));

      QDrag *drag = new QDrag (this);
      drag->setMimeData(mimeData);
      drag->setHotSpot(event->pos() - item->pos());

      item->hide();
      QPixmap drag_img(120, 18);
      QPainter painter(&drag_img);
      painter.drawText(QRectF(0,0, 120,18)," ... 拖动时图片信息.. ", QTextOption(Qt::AlignVCenter));
      drag->setPixmap(drag_img);

      if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
      {
          item->close();
      }
      else
      {
          item->show();
      }
   }
}

void DragWgt::dragEnterEvent (QDragEnterEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-draganddrop"))
   {
       event->accept();
   }
   else
  {
      event->ignore();
  }
}


void DragWgt::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}


void DragWgt::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-draganddrop"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}


void DragWgt::dropEvent (QDropEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-draganddrop"))
   {
      const QMimeData *mimeData = event->mimeData();
      QByteArray exData = mimeData->data("application/x-draganddrop");
      QDataStream dataStream (&exData, QIODevice::ReadOnly);
      QPoint pos;
      QString id;
      QString name;
      int nSex;
      dataStream>>pos>>id>>name>>nSex;

      qDebug()<<pos<<id<<name<<nSex;

      QLabel *item = new QLabel (this);
      item->setFixedSize(50,50);
      item->setStyleSheet("background-color:rgb(255,155,55);");
      item->setAttribute (Qt::WA_DeleteOnClose);
      item->move(event->pos()-pos);
      item->show();
   }
}

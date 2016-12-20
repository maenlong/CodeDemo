#include "listviewdemo.h"
#include "ui_listviewdemo.h"

ListViewDemo::ListViewDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListViewDemo)
{
    ui->setupUi(this);

    ui->LeftView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->LeftView->setDragEnabled(true);
    ui->LeftView->viewport()->setAcceptDrops(true);
    ui->LeftView->setDropIndicatorShown(true);
    ui->LeftView->setDragDropMode(QAbstractItemView::DragDrop);

    ui->RightView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->RightView->setDragEnabled(true);
    ui->RightView->viewport()->setAcceptDrops(true);
    ui->RightView->setDropIndicatorShown(true);
    ui->RightView->setDragDropMode(QAbstractItemView::DragDrop);

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slot_addItem()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(slot_insertItem()));
}

ListViewDemo::~ListViewDemo()
{
    delete ui;
}

void ListViewDemo::slot_addItem()
{
    ui->listWidget->insertItem(0,"xxx");
}

void ListViewDemo::slot_insertItem()
{
    ui->listWidget->addItem("NNNN");
}


void ListViewDemo::dragEnterEvent(QDragEnterEvent *event)
{
//    if(event->mimeData()->hasFormat("text/uri-list"))
//    {
//        event->acceptProposedAction();
//        qDebug() << "drag enter";
//    }
}

void ListViewDemo::dropEvent(QDropEvent *event)
{
//    QList urls = event->mimeData()->urls();
//    if(urls.isEmpty())
//            return;

//    foreach(QUrl url, urls) {
//            QString file_name = url.toLocalFile();
//            qDebug() << file_name;
//    }
}

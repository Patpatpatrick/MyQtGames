#include "ChessWelcome.h"
#include "ui_ChessWelcome.h"
#include "BasicGame.h"
#include "ManMachineGame.h"
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>
#include <QColorDialog>
#include <QDebug>
ChessWelcome::ChessWelcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWelcome)
{
    ui->setupUi(this);
    connect(ui->ManMachine,&QPushButton::clicked,[=](){
//        QColorDialog * clrdlg = new QColorDialog(this);
//        clrdlg->show();
//        QColor c = clrdlg->getColor();
//        qDebug()<<c;
        setAttribute(Qt::WA_DeleteOnClose);
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Choose Sequence", "Do you want to play as red(red always goes first)?",
                                        QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
          if (reply == QMessageBox::Yes) {
              //BasicGame * board = new BasicGame(true);

              ManMachineGame * board = new ManMachineGame(true);
              board->show();
          } else {
              //BasicGame * board = new BasicGame(true);

              ManMachineGame * board = new ManMachineGame(false);
              board->show();
          }
    });
}

ChessWelcome::~ChessWelcome()
{
    delete ui;
}

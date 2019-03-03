#include "ChessWelcome.h"
#include "ui_ChessWelcome.h"
#include "Board.h"
#include "ManMachineGame.h"
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>
ChessWelcome::ChessWelcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWelcome)
{
    ui->setupUi(this);
    connect(ui->ManMachine,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Choose Sequence", "Do you want to play as red(red always goes first)?",
                                        QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
          if (reply == QMessageBox::Yes) {
              ManMachineGame * board = new ManMachineGame(true);
              board->show();
          } else {
              ManMachineGame * board = new ManMachineGame(false);
              board->show();
          }
    });
}

ChessWelcome::~ChessWelcome()
{
    delete ui;
}

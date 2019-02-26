#include "ChessWelcome.h"
#include "ui_ChessWelcome.h"
#include "Board.h"
#include <QWidget>
#include <QPushButton>

ChessWelcome::ChessWelcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWelcome)
{
    ui->setupUi(this);
    connect(ui->ManMachine,&QPushButton::clicked,[=](){
        Board * board = new Board();
        board->show();
    });
}

ChessWelcome::~ChessWelcome()
{
    delete ui;
}

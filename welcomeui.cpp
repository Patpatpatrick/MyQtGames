#include "welcomeui.h"
#include "ui_welcomeui.h"
#include "ChessWelcome.h"

WelcomeUI::WelcomeUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeUI)
{
    ui->setupUi(this);
    connect(ui->ChineseChessBtn,&QPushButton::clicked,[=](){
        ChessWelcome * chesswel = new ChessWelcome();
        chesswel->show();
    });
}

WelcomeUI::~WelcomeUI()
{
    delete ui;
}

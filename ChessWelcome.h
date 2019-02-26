#ifndef CHESSWELCOME_H
#define CHESSWELCOME_H

#include <QWidget>

namespace Ui {
class ChessWelcome;
}

class ChessWelcome : public QWidget
{
    Q_OBJECT

public:
    explicit ChessWelcome(QWidget *parent = nullptr);
    ~ChessWelcome();

private:
    Ui::ChessWelcome *ui;
};

#endif // CHESSWELCOME_H

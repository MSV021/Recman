#include "recman.h"
#include "ui_recman.h"

Recman::Recman(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Recman)
{
    ui->setupUi(this);
}

Recman::~Recman()
{
    delete ui;
}


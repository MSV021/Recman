#ifndef RECMAN_H
#define RECMAN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Recman; }
QT_END_NAMESPACE

class Recman : public QMainWindow
{
    Q_OBJECT

public:
    Recman(QWidget *parent = nullptr);
    ~Recman();

private:
    Ui::Recman *ui;
};
#endif // RECMAN_H

#ifndef HST_H
#define HST_H

#include <QWidget>

namespace Ui {
class hst;
}

class hst : public QWidget
{
    Q_OBJECT

public:
    explicit hst(QWidget *parent = nullptr);
    ~hst();

private slots:
    void on_pushButton_clicked();

private:
    Ui::hst *ui;
};

#endif // HST_H

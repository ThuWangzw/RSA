#ifndef RSATOY_H
#define RSATOY_H

#include <QMainWindow>

#include "RSA.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RSAToy; }
QT_END_NAMESPACE

class RSAToy : public QMainWindow
{
    Q_OBJECT

public:
    RSAToy(QWidget *parent = nullptr);
    ~RSAToy();
public:
    RSA rsa;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_btn_generate_clicked();

    void on_btn_send_clicked();

private:
    Ui::RSAToy *ui;
    uint32_t digits[3] = {768, 1024, 2048};
};
#endif // RSATOY_H

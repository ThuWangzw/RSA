#include "rsatoy.h"
#include "ui_rsatoy.h"
#include <iostream>
#include <ctime>
#include <QMessageBox>

using namespace std;

RSAToy::RSAToy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RSAToy)
{
    ui->setupUi(this);
}

RSAToy::~RSAToy()
{
    delete ui;
}

void RSAToy::on_btn_generate_clicked()
{
    // get digit
    uint32_t digit = digits[ui->comboBox->currentIndex()];
    clock_t begin = clock();
    rsa.set_up(digit);
    clock_t end = clock();
    QString text = QString("Generation succeed! Time used: %1s").arg((double)(end-begin)/CLOCKS_PER_SEC);
    ui->text_n->setPlainText(QString(rsa.n.toString().c_str()));
    ui->text_p->setPlainText(QString(rsa.p.toString().c_str()));
    ui->text_q->setPlainText(QString(rsa.q.toString().c_str()));
    ui->text_e->setPlainText(QString(rsa.e.toString().c_str()));
    ui->text_d->setPlainText(QString(rsa.d.toString().c_str()));
    QMessageBox::information(this, "Information", text,
                                    QMessageBox::Ok,QMessageBox::NoButton);
}

void RSAToy::on_comboBox_currentIndexChanged(int index)
{

}

void RSAToy::on_btn_send_clicked()
{
    if(!rsa.is_inited()) {
        QMessageBox::information(this, "Information", "Please generate RSA keys first!",
                                        QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    string msg = ui->text_message->toPlainText().toUtf8().constData();
    cout << "Send message:" << msg << endl;
    vector<Integer> cs = rsa.encryption(msg);
    string rm = rsa.decryption(cs);
    cout << "Recv message:" << rm << endl;
    ui->text_decrypted->setPlainText(QString(rm.c_str()));
    QString encry("");
    for(vector<Integer>::iterator it = cs.begin(); it != cs.end(); it++) {
        encry += QString((*it).toString().c_str());
    }
    ui->text_encrypted->setPlainText(encry);
}

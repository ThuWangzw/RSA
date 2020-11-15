#include "rsatoy.h"
#include "Test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RSAToy w;
    w.show();
    return a.exec();
}

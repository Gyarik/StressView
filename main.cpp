#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel test("Testing.");
    test.show();

    return a.exec();
}

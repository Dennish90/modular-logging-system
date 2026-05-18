#include <logAnalyzer/mainWindow.h>

#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Aly");
    resize(1200, 800);

    QLabel* label = new QLabel("Here there will be cool stuff", this);
    setCentralWidget(label);
}
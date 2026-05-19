#include <logAnalyzer/mainWindow.h>

#include "ui_mainWindow.h"

#include <QAbstractItemView>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle("Anly");

    SetupLogTable();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::SetupLogTable()
{
    _ui->logTableWidget->setColumnCount(4);

    _ui->logTableWidget->setHorizontalHeaderLabels(
        {
            "Timestamp",
            "Level",
            "Category",
            "Message"
        }
    );

    _ui->logTableWidget->setRowCount(0);

    _ui->logTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _ui->logTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->logTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    _ui->logTableWidget->setAlternatingRowColors(true);

    _ui->logTableWidget->horizontalHeader()->setStretchLastSection(true);
    _ui->logTableWidget->verticalHeader()->setVisible(false);
}
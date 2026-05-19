#include <logAnalyzer/mainWindow.h>

#include "ui_mainWindow.h"

#include <QAbstractItemView>
#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle("Anly");

    SetupLogTable();

    connect(
        _ui->btnOpenFile,
        &QPushButton::clicked,
        this,
        &MainWindow::OnOpenFileButtonClicked
    );

    connect(
        _ui->btnBrowse,
        &QPushButton::clicked,
        this,
        &MainWindow::OnBrowseButtonClicked
    );
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

    _ui->logTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    _ui->logTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    _ui->logTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    _ui->logTableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    _ui->logTableWidget->horizontalHeader()->setStretchLastSection(true);
    _ui->logTableWidget->verticalHeader()->setVisible(false);
}

void MainWindow::OnBrowseButtonClicked()
{
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select log file",
        "",
        "Log files (*.txt *.log);;Text files (*.txt);;All files (*.*)"
    );

    if (filePath.isEmpty())
    {
        return;
    }

    _ui->lnEdLogFilePath->setText(filePath);
}

void MainWindow::OnOpenFileButtonClicked()
{
    const QString filePath = _ui->lnEdLogFilePath->text().trimmed();

    if (filePath.isEmpty())
    {
        QMessageBox::warning(
            this,
            "No file path",
            "Please enter a path to a log file."
        );

        return;
    }

    LoadLogFile(filePath);
}

void MainWindow::LoadLogFile(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
            this,
            "Could not open file",
            "Could not open log file:\n" + filePath
        );

        return;
    }

    _ui->logTableWidget->setRowCount(0);

    QTextStream inputStream(&file);

    int totalEntries = 0;
    int parsedEntries = 0;

    while (!inputStream.atEnd())
    {
        const QString line = inputStream.readLine();

        if (line.trimmed().isEmpty())
        {
            continue;
        }

        totalEntries++;

        QString timestamp;
        QString level;
        QString category;
        QString message;

        if (!TryParseLogLine(line, timestamp, level, category, message))
        {
            continue;
        }

        AddLogEntryToTable(timestamp, level, category, message);
        parsedEntries++;
    }

    file.close();

    _ui->lblStatusText->setText("Loaded file: " + filePath);
    UpdateEntryCount(parsedEntries, totalEntries);
}

bool MainWindow::TryParseLogLine(
    const QString& line,
    QString& timestamp,
    QString& level,
    QString& category,
    QString& message
)
{
    const int firstSeparator = line.indexOf('|');

    if (firstSeparator == -1)
    {
        return false;
    }

    const int secondSeparator = line.indexOf('|', firstSeparator + 1);

    if (secondSeparator == -1)
    {
        return false;
    }

    const int thirdSeparator = line.indexOf('|', secondSeparator + 1);

    if (thirdSeparator == -1)
    {
        return false;
    }

    timestamp = line.left(firstSeparator).trimmed();

    level = line.mid(
        firstSeparator + 1,
        secondSeparator - firstSeparator - 1
    ).trimmed();

    category = line.mid(
        secondSeparator + 1,
        thirdSeparator - secondSeparator - 1
    ).trimmed();

    message = line.mid(thirdSeparator + 1).trimmed();

    return true;
}

void MainWindow::AddLogEntryToTable(
    const QString& timestamp,
    const QString& level,
    const QString& category,
    const QString& message
)
{
    const int row = _ui->logTableWidget->rowCount();

    _ui->logTableWidget->insertRow(row);

    _ui->logTableWidget->setItem(row, 0, new QTableWidgetItem(timestamp));
    _ui->logTableWidget->setItem(row, 1, new QTableWidgetItem(level));
    _ui->logTableWidget->setItem(row, 2, new QTableWidgetItem(category));
    _ui->logTableWidget->setItem(row, 3, new QTableWidgetItem(message));
}

void MainWindow::UpdateEntryCount(int shownEntries, int totalEntries)
{
    _ui->lblEntryCount->setText(
        "Showing " +
        QString::number(shownEntries) +
        " / " +
        QString::number(totalEntries) +
        " log entries"
    );
}
#include <logAnalyzer/mainWindow.h>

#include "ui_mainWindow.h"

#include <QAbstractItemView>
#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QTimeEdit>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle("Ally - Log Analyzer");

    _ui->timeEditFrom->setDisplayFormat("HH:mm:ss");
    _ui->timeEditTo->setDisplayFormat("HH:mm:ss");

    _ui->timeEditFrom->setTime(QTime(0, 0, 0));
    _ui->timeEditTo->setTime(QTime(23, 59, 59));

    SetupLogTable();
    ConnectLevelFilterButtons();

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

    connect(
        _ui->lnEdSearch,
        &QLineEdit::textChanged,
        this,
        &MainWindow::ApplyFilters
    );

    connect(
        _ui->chkEnableTimeFilter,
        &QCheckBox::toggled,
        this,
        &MainWindow::ApplyFilters
        );

    connect(
        _ui->timeEditFrom,
        &QTimeEdit::timeChanged,
        this,
        &MainWindow::ApplyFilters
    );

    connect(
        _ui->timeEditTo,
        &QTimeEdit::timeChanged,
        this,
        &MainWindow::ApplyFilters
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
    ApplyFilters();
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

void MainWindow::ConnectLevelFilterButtons()
{
    connect(_ui->btnTrace, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
    connect(_ui->btnDebug, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
    connect(_ui->btnInfo, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
    connect(_ui->btnWarning, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
    connect(_ui->btnError, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
    connect(_ui->btnCritical, &QPushButton::toggled, this, &MainWindow::ApplyFilters);
}

void MainWindow::ApplyFilters()
{
    int shownEntries = 0;
    const int totalEntries = _ui->logTableWidget->rowCount();

    for (int row = 0; row < totalEntries; row++)
    {
        QTableWidgetItem* levelItem = _ui->logTableWidget->item(row, 1);

        if (levelItem == nullptr)
        {
            _ui->logTableWidget->setRowHidden(row, true);
            continue;
        }

        const QString level = levelItem->text().trimmed();

        const bool levelMatches = IsLevelEnabled(level);
        const bool searchMatches = DoesRowMatchSearch(row);
        const bool timeMatches = DoesRowMatchTimeFilter(row);

        const bool shouldShow = levelMatches && searchMatches && timeMatches;

        _ui->logTableWidget->setRowHidden(row, !shouldShow);

        if (shouldShow)
        {
            shownEntries++;
        }
    }

    UpdateEntryCount(shownEntries, totalEntries);
}

bool MainWindow::IsLevelEnabled(const QString& level) const
{
    if (level == "TRACE")
    {
        return _ui->btnTrace->isChecked();
    }

    if (level == "DEBUG")
    {
        return _ui->btnDebug->isChecked();
    }

    if (level == "INFO")
    {
        return _ui->btnInfo->isChecked();
    }

    if (level == "WARNING")
    {
        return _ui->btnWarning->isChecked();
    }

    if (level == "ERROR")
    {
        return _ui->btnError->isChecked();
    }

    if (level == "CRITICAL")
    {
        return _ui->btnCritical->isChecked();
    }

    return true;
}

bool MainWindow::DoesRowMatchTimeFilter(int row) const
{
    if (!_ui->chkEnableTimeFilter->isChecked())
    {
        return true;
    }

    QTableWidgetItem* timestampItem = _ui->logTableWidget->item(row, 0);

    if (timestampItem == nullptr)
    {
        return false;
    }

    QTime rowTime;

    if (!TryGetTimeFromTimestamp(timestampItem->text(), rowTime))
    {
        return false;
    }

    const int rowSeconds = QTime(0, 0, 0).secsTo(rowTime);
    const int fromSeconds = QTime(0, 0, 0).secsTo(_ui->timeEditFrom->time());
    const int toSeconds = QTime(0, 0, 0).secsTo(_ui->timeEditTo->time());

    if (fromSeconds <= toSeconds)
    {
        return rowSeconds >= fromSeconds && rowSeconds <= toSeconds;
    }

    return rowSeconds >= fromSeconds || rowSeconds <= toSeconds;
}

bool MainWindow::TryGetTimeFromTimestamp(const QString& timestamp, QTime& time) const
{
    // Expected format:
    // 2026-06-01 16:04:28.571

    if (timestamp.length() < 19)
    {
        return false;
    }

    const QString timePart = timestamp.mid(11, 8);

    time = QTime::fromString(timePart, "HH:mm:ss");

    return time.isValid();
}

bool MainWindow::DoesRowMatchSearch(int row) const
{
    const QString searchText = _ui->lnEdSearch->text().trimmed();

    if (searchText.isEmpty())
    {
        return true;
    }

    for (int column = 0; column < _ui->logTableWidget->columnCount(); column++)
    {
        QTableWidgetItem* item = _ui->logTableWidget->item(row, column);

        if (item == nullptr)
        {
            continue;
        }

        if (item->text().contains(searchText, Qt::CaseInsensitive))
        {
            return true;
        }
    }

    return false;
}
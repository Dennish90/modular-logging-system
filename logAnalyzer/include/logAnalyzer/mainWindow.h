#pragma once

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void SetupLogTable();

    void OnOpenFileButtonClicked();
    void OnBrowseButtonClicked();
    
    void LoadLogFile(const QString& filePath);
    bool TryParseLogLine(
        const QString& line,
        QString& timestamp,
        QString& level,
        QString& category,
        QString& message
    );

    void AddLogEntryToTable(
        const QString& timestamp,
        const QString& level,
        const QString& category,
        const QString& message
    );

    void UpdateEntryCount(int shownEntries, int totalEntries);

    Ui::MainWindow* _ui;
};
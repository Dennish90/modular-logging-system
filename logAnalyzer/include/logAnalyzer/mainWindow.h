#pragma once

#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QDate>

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
    /**
     * @brief Configures the log table used to display parsed log entries.
     */
    void SetupLogTable();

    /**
     * @brief Connects all level filter buttons to the filter update function.
     */
    void ConnectLevelFilterButtons();

    void OnOpenFileButtonClicked();
    void OnBrowseButtonClicked();
    
    /**
     * @brief Opens and loads a log file from the given file path.
     *
     * The file is parsed line by line using the expected log format.
     * Parsed entries are added to the table and the date filter range is updated
     * based on the timestamps found in the file.
     *
     * @param filePath Path to the log file.
     */
    void LoadLogFile(const QString& filePath);

    /**
     * @brief Attempts to parse a single structured log line.
     *
     * Expected format:
     * timestamp | level | category | message
     *
     * The message field may contain additional separator characters.
     *
     * @param line The raw log line to parse.
     * @param timestamp Output timestamp value.
     * @param level Output log level value.
     * @param category Output category value.
     * @param message Output message value.
     * @return true if the line was parsed successfully; otherwise false.
     */
    bool TryParseLogLine(
        const QString& line,
        QString& timestamp,
        QString& level,
        QString& category,
        QString& message
    );

    /**
     * @brief Adds a parsed log entry as a new row in the log table.
     *
     * @param timestamp Parsed timestamp value.
     * @param level Parsed log level value.
     * @param category Parsed category value.
     * @param message Parsed message value.
     */
    void AddLogEntryToTable(
        const QString& timestamp,
        const QString& level,
        const QString& category,
        const QString& message
    );

    /**
     * @brief Applies all active filters to the log table.
     *
     * Level, search, date and time filters are combined using AND logic.
     * A row is shown only when it matches all active filters.
     */
    void ApplyFilters();
    
    /**
     * @brief Checks whether the given log level is enabled in the level filter.
     *
     * Unknown or custom log levels are treated as enabled.
     *
     * @param level Log level text from a parsed log entry.
     * @return true if the level should be shown; otherwise false.
     */
    bool IsLevelEnabled(const QString& level) const;

    /**
     * @brief Checks whether a table row matches the current search text.
     *
     * The search is case-insensitive and checks all visible table columns.
     *
     * @param row Row index in the log table.
     * @return true if the row matches the search text; otherwise false.
     */
    bool DoesRowMatchSearch(int row) const;

    /**
     * @brief Checks whether a table row matches the active time filter.
     *
     * If the time filter is disabled, the row always matches.
     *
     * @param row Row index in the log table.
     * @return true if the row matches the active time filter; otherwise false.
     */
    bool DoesRowMatchTimeFilter(int row) const;

    /**
     * @brief Extracts the time part from a timestamp string.
     *
     * Expected timestamp format:
     * YYYY-MM-DD HH:MM:SS.mmm
     *
     * Milliseconds are ignored because the time filter works on whole seconds.
     *
     * @param timestamp Timestamp string from the log table.
     * @param time Output time value.
     * @return true if a valid time could be extracted; otherwise false.
     */
    bool TryGetTimeFromTimestamp(const QString& timestamp, QTime& time) const;

    /**
     * @brief Checks whether a table row matches the active date filter.
     *
     * If the date filter is disabled, the row always matches.
     *
     * @param row Row index in the log table.
     * @return true if the row matches the active date filter; otherwise false.
     */
    bool DoesRowMatchDateFilter(int row) const;

    /**
     * @brief Extracts the date part from a timestamp string.
     *
     * Expected timestamp format:
     * YYYY-MM-DD HH:MM:SS.mmm
     *
     * @param timestamp Timestamp string from the log table.
     * @param date Output date value.
     * @return true if a valid date could be extracted; otherwise false.
     */
    bool TryGetDateFromTimestamp(const QString& timestamp, QDate& date) const;

    void UpdateEntryCount(int shownEntries, int totalEntries);

    Ui::MainWindow* _ui;
};
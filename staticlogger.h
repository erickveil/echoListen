/**
 * staticlogger.h
 * Erick Veil
 * 2018-10-02
 * Copywrite 2018 ComTech Communications
 */
#ifndef STATICLOGGER_H
#define STATICLOGGER_H

#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>

namespace stnctl {
/**
 * @brief The StaticLogger class
 * A simple logger that writes to stdout
 */
class StaticLogger
{
public:
    StaticLogger();
    static void logDebug(const char* method, int line, QString msg);
    static void logInfo(const char* method, int line, QString msg);
    static void logWarn(const char* method, int line, QString msg);
    static void writeLog(QString level, const char* method, int line,
                         QString msg);
private:
    static void writeDebug(QString level, const char* method, int line,
                           QString msg);
    static QString createRecord(QString level, const char* method, int line,
                                QString msg);
};

} // namespace stnctl

#endif // STATICLOGGER_H

#include "staticlogger.h"

namespace stnctl {

StaticLogger::StaticLogger()
{

}

void StaticLogger::logDebug(const char *method, int line, QString msg)
{
    writeDebug("DEBUG", method, line, msg);
}

void StaticLogger::logInfo(const char *method, int line, QString msg)
{
    writeLog("INFO", method, line, msg);
}

void StaticLogger::logWarn(const char *method, int line, QString msg)
{
    writeLog("WARN", method, line, msg);
}

void StaticLogger::writeLog(QString level, const char *method, int line,
                            QString msg)
{
    QString record = createRecord(level, method, line, msg);
    QTextStream output( stdout );
    output << record;
}

void StaticLogger::writeDebug(QString level, const char *method, int line,
                            QString msg)
{
    QString record = createRecord(level, method, line, msg);
    qDebug() << record;
}

QString StaticLogger::createRecord(QString level, const char *method, int line, QString msg)
{
    Qt::DateFormat format = Qt::ISODateWithMs;
    QString timestamp = QDateTime::currentDateTime().toString(format);
    QString delim = " | ";
    return level + delim + timestamp + delim + QString(method)
            + delim + QString::number(line) + delim + msg + "\n";
}

} // namespace stnctl

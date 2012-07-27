/*
 * Copyright (C) 2012 Andres Pagliano, Gabriel Miretti, Gonzalo Buteler,
 * Nestor Bustamante, Pablo Perez de Angelis
 *
 * This file is part of LVK Chatbot.
 *
 * LVK Chatbot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LVK Chatbot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LVK Chatbot.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "logger.h"
#include "settings.h"
#include "version.h"
#include "settingskeys.h"

#include <cstdlib>
#include <iostream>
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QDateTime>

#define DEBUG_STR            "Debug: "
#define WARNING_STR          "Warning: "
#define CRITICAL_STR         "Critical: "
#define FATAL_STR            "Fatal: "

#define LOG_FILENAME         "chatbot.log"
#define LOG_MAX_SIZE         (1024*1024)

#define DATE_TIME_LOG_FORMAT "yyyy-MM-dd hh:mm:ss.zzz"

//--------------------------------------------------------------------------------------------------
// Helpers
//--------------------------------------------------------------------------------------------------

namespace
{

bool makeLogsPath()
{
    Lvk::Cmn::Settings settings;
    QString logsPath = settings.value(SETTING_LOGS_PATH).toString();

    bool success = true;

    QDir qdir;
    if (!qdir.exists(logsPath)) {
        success = qdir.mkpath(logsPath);
    }

    return success;
}

//--------------------------------------------------------------------------------------------------

QString chatbotLogFilename()
{
    Lvk::Cmn::Settings settings;
    QString logsPath = settings.value(SETTING_LOGS_PATH).toString();

    return logsPath + QDir::separator() + LOG_FILENAME;
}

//--------------------------------------------------------------------------------------------------

void rotateLog(const QString &logFilename)
{
    QString rlogFilename = logFilename + ".1";

    QFileInfo logFile(logFilename);

    if (logFile.size() > LOG_MAX_SIZE) {
        QFile::remove(rlogFilename);
        QFile::rename(logFilename, rlogFilename);
    }
}

} // namespace


//--------------------------------------------------------------------------------------------------
// Logger
//--------------------------------------------------------------------------------------------------

QFile *Lvk::Cmn::Logger::m_logFile = 0;

//--------------------------------------------------------------------------------------------------

void Lvk::Cmn::Logger::init()
{
    if (m_logFile) {
        return; // Already initialized
    }

    QString logFilename = chatbotLogFilename();

    if (makeLogsPath()) {
        rotateLog(logFilename);

        m_logFile = new QFile(logFilename);

        if (m_logFile->open(QFile::Append)) {
            qInstallMsgHandler(msgHandler);
            qDebug() << "Logger initialized on"
                     << APP_NAME " v" APP_VERSION_STR " rev:" APP_VERSION_REV;
        } else {
            delete m_logFile;
            m_logFile = 0;
            qCritical() << CRITICAL_STR "Cannot open" << logFilename << " in append mode.";
        }
    } else {
        qCritical() << CRITICAL_STR "Cannot create path for log file" << logFilename;
    }
}


//--------------------------------------------------------------------------------------------------

void Lvk::Cmn::Logger::shutdown()
{
    qDebug() << "Logger shutdown";

    qInstallMsgHandler(0); // Restore handler

    delete m_logFile;
    m_logFile = 0;
}

//--------------------------------------------------------------------------------------------------

void Lvk::Cmn::Logger::msgHandler(QtMsgType type, const char *msg)
{
    m_logFile->write(QDateTime::currentDateTime().toString(DATE_TIME_LOG_FORMAT).toUtf8());
    m_logFile->write(" ");

    switch (type) {
    case QtDebugMsg:
        std::cout << DEBUG_STR << msg << std::endl;
        m_logFile->write(DEBUG_STR);
        break;

    case QtWarningMsg:
        std::cerr << WARNING_STR << msg << std::endl;
        m_logFile->write(WARNING_STR);
        break;

    case QtCriticalMsg:
        std::cerr << CRITICAL_STR << msg << std::endl;
        m_logFile->write(CRITICAL_STR);
        break;

    case QtFatalMsg:
        std::cerr << FATAL_STR << msg << std::endl;
        m_logFile->write(FATAL_STR);
        break;
    }

    m_logFile->write(msg);
    m_logFile->write("\n");
    m_logFile->flush();

    if (type == QtFatalMsg) {
        abort();
    }
}
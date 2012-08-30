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

#include "remoteloggerfactory.h"

#ifdef GELF_STATS_SUPPORT
# include "common/graylogremotelogger.h"
#else
# include "common/nullremotelogger.h"
#endif

//--------------------------------------------------------------------------------------------------
// RemoteLoggerFactory
//--------------------------------------------------------------------------------------------------

Lvk::Cmn::RemoteLogger * Lvk::Cmn::RemoteLoggerFactory::createFastLogger()
{
#ifdef GELF_STATS_SUPPORT
    return new GraylogRemoteLogger(GraylogRemoteLogger::GELF, false);
#else
    return new NullRemoteLogger();
#endif

}

//--------------------------------------------------------------------------------------------------

Lvk::Cmn::RemoteLogger * Lvk::Cmn::RemoteLoggerFactory::createSecureLogger()
{
#ifdef GELF_STATS_SUPPORT
    return new GraylogRemoteLogger(GraylogRemoteLogger::SyslogTCP, true);
#else
    return new NullRemoteLogger();
#endif
}

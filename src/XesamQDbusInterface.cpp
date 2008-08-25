/* This file is part of XesamQLib
 *
 * Copyright (C) 2008 Flavio Castelli <flavio.castelli@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "XesamQDbusInterface.h"

#include "XesamQDbusSearcher.h"

namespace XesamQLib
{

  XesamQDbusInterface::XesamQDbusInterface ( const QString &service,
                                             const QString &path,
                                             const QDBusConnection &connection,
                                             QObject *parent)
        : XesamQSearchInterface(service, path, connection, parent)
  {
    m_closed = false;
  }
  
  
  XesamQSearcher* XesamQDbusInterface::searcher() {
    return new XesamQDbusSearcher (this);
  }
}

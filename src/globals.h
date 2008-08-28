/* This file is part of Xesam Client library
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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtCore/QList>
#include <QtCore/QVariant>

namespace Xesam {
  namespace Client {
    //Q_ENUMS(SortOrder)
    #define XESAM_SERVER_DBUS_NAME "org.freedesktop.xesam.searcher"
    #define XESAM_SERVER_DBUS_INTERFACE "org.freedesktop.xesam.Search"
    #define XESAM_SERVER_DBUS_OBJECT "/org/freedesktop/xesam/searcher/main"
  
    enum SortOrder { Ascending, Descending};
  
    enum VendorState { Idle, Update, FullIndex};
    
    typedef QList < QVariantList > ListVariantList; 
   
  }
}
#endif /* GLOBALS_H */

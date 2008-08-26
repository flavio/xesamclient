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

#ifndef XESAMQDBUSINTERFACE_H_
#define XESAMQDBUSINTERFACE_H_

#include "XesamQGlobals.h"
#include "XesamQSearchInterface.h"

namespace XesamQLib
{
  class XesamQSearcher;

  /**
  *
  **/
  class XesamQDbusInterface : public XesamQSearchInterface
  {
    Q_OBJECT

    private:
      bool m_closed;

    public:
      XesamQDbusInterface ( const QString &service,
                            const QString &path,
                            const QDBusConnection &connection,
                            QObject *parent = 0 );
      virtual ~XesamQDbusInterface() {}
  
      XesamQSearcher* searcher();

      /**
      * @return true if the interface is ready to use, false otherwise
      */
      bool isReady () {
        return this->isValid();
      }

      /**
      * Convenience method used to set sort properties
      * @param session_handle ID of the current session
      * @param propertyName name of the property to set
      * @param order desired value
      */
      inline void SetPropertySortOrder( const QString& session_handle,
                                        const QString& propertyName,
                                        const SortOrder& order) {
        QString value;
        if (order == Ascending)
          value = "ascending";
        else
          value = "descending";
  
        this->SetProperty( session_handle, propertyName, QDBusVariant(value));
      }
  
      inline SortOrder GetPropertySortOrder(const QString& session_handle, const QString& propertyName) {
        QDBusVariant dbusVariant;
        dbusVariant = this->GetProperty(session_handle, propertyName).value();
        QString order = dbusVariant.variant().toString();
        if (order.compare( "ascending") == 0)
          return Ascending;
  
        return Descending;
      }
  }; 
}



#endif /*XESAMQDBUSINTERFACE_H_*/

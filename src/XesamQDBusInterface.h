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

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>


Q_DECLARE_METATYPE (QList < quint32>)
Q_DECLARE_METATYPE (XesamQLib::Hit)
Q_DECLARE_METATYPE (XesamQLib::Hit::List)
Q_DECLARE_METATYPE (QList<QVariantList>)

namespace XesamQLib {

  class DBusInterface : public QDBusAbstractInterface {
    Q_OBJECT

    public:
      DBusInterface(const QString &service, const QString &path,
          const QDBusConnection &connection, QObject *parent = 0);

      ~DBusInterface();

      static inline const char *staticInterfaceName() {
            return "org.freedesktop.xesam.Search";
      }
      
      /**
       * @return true if the interface is ready to use, false otherwise
       */
      bool isReady() {
        return this->isValid();
      }

      /**
       * Convenience method used to set sort properties
       * @param session_handle ID of the current session
       * @param propertyName name of the property to set
       * @param order desired value
       */
      void setPropertySortOrder(const QString& session_handle,
                                const QString& propertyName,
                                const SortOrder& order);
      
      /**
      * Convenience method used to get sort properties
      * @param session_handle ID of the current session
      * @param propertyName name of the property to set
      * @return the sort order of the required property
      */
      SortOrder getPropertySortOrder( const QString& session_handle,
                                      const QString& propertyName);
      
    public Q_SLOTS:
      QDBusReply<void> closeSearch(const QString &search_handle);
      QDBusReply<void> closeSession(const QString &session_handle);
      QDBusReply<uint> getHitCount(const QString &search_handle);
      QDBusReply<QList<QVariantList> > getHitData(
                    const QString &search_handle, const QList<quint32> &hit_ids,
                    const QStringList &fields);
      QDBusReply<Hit::List > getHits(
                    const QString &search_handle, uint count);
      QDBusReply<QDBusVariant> getProperty( const QString &session_handle,
                                            const QString &key);
      QDBusReply<QStringList> getState();
      QDBusReply<QString> newSearch(const QString &session_handle,
                                    const QString &query_xml);
      QDBusReply<QString> newSession();
      QDBusReply<QDBusVariant> setProperty( const QString &session_handle,
                                            const QString &key,
                                            const QDBusVariant &value);
      QDBusReply<void> startSearch(const QString &search_handle);

    Q_SIGNALS:
      void hitsAdded(const QString &search_handle, uint count);
      void hitsModified(const QString &search_handle,
                        const QList<quint32> &hit_ids);
      void hitsRemoved( const QString &search_handle,
                        const QList<quint32> &hit_ids);
      void searchDone(const QString &search_handle);
      void stateChanged(const QStringList &state_info);
      
    private:
      bool m_closed;

  };
}

#endif /*XESAMQDBUSINTERFACE_H_*/

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

#ifndef XESAMQSESSION_P_H_
#define XESAMQSESSION_P_H_

#include <QtDBus/QDBusVariant>
#include <QObject>
#include <QMap>

#include "XesamQGlobals.h"

namespace XesamQLib {

  class XesamQDBusInterface;
  class XesamQSearch;
  class XesamQQuery;

  class XesamQSessionPrivate : public QObject {
    Q_OBJECT

    private:
      QString m_sessionHanlde;
      XesamQDBusInterface* m_dbusInterface;
      QMap<QString, XesamQSearch*> m_searches;


    public:
      XesamQSessionPrivate(const QString& bus_name,
                           const QString& object_path,
                           QObject * parent = 0);

      ~XesamQSessionPrivate();

      bool isReady();

      bool isClosed();

      void close();

      XesamQSearch* newSearch(XesamQQuery* query);

      XesamQSearch* newSearchFromText(const QString& searchText);

      QDBusVariant getProperty(const QString& propName);

      void setProperty (const QString& propName, const QDBusVariant& value);

      SortOrder sortOrder(const QString& propName);

       void setSortOrder(const QString& propName, const SortOrder& order);

      bool vendorState(VendorState& state, int& done);

    Q_SIGNALS:
      void stateChanged (const QStringList &state_info);

    private Q_SLOTS:
      void slotHitsAdded(const QString &search_handle, quint32 count);

      void slotHitsModified(const QString &search_handle,
                        const QList<quint32> &hit_ids);

      void slotHitsRemoved( const QString &search_handle,
                        const QList<quint32> &hit_ids);

      void slotSearchDone(const QString &search_handle);

      void slotStateChanged(const QStringList &state_info);
  };
}

#endif /*XESAMQSESSION_P_H_*/

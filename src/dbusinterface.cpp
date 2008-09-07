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

#include "dbusinterface.h"

#include <QtDBus/QDBusArgument>

using namespace Xesam::Client;

DBusInterface::DBusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
  m_closed = false;
  qDBusRegisterMetaType<ListVariantList>();
}

DBusInterface::~DBusInterface()
{
}

QDBusReply<void> DBusInterface::closeSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::NoBlock, QLatin1String("CloseSearch"),
      argumentList);
}

QDBusReply<void> DBusInterface::closeSession(const QString &session_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle);
  return callWithArgumentList(QDBus::NoBlock,
      QLatin1String("CloseSession"), argumentList);
}

QDBusReply<uint> DBusInterface::getHitCount(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  QDBusMessage msg = callWithArgumentList(QDBus::Block, QLatin1String("GetHitCount"),
      argumentList);
  qDebug() << msg;
  return msg;
}

QDBusReply<ListVariantList > DBusInterface::getHitData(
                    const QString &search_handle, const QList<uint> &hit_ids,
                    const QStringList &fields)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(hit_ids) << qVariantFromValue(fields);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHitData"),
      argumentList);
}

QDBusReply<ListVariantList > DBusInterface::getHits(
    const QString &search_handle, uint count) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(count);
  QDBusReply<ListVariantList> reply = callWithArgumentList(QDBus::Block, QLatin1String("GetHits"),
      argumentList);
  ListVariantList hit (reply);
//  qDebug() << "DBusInterface::getHits - " << hit;
  return reply;
 }

QDBusReply<QDBusVariant> DBusInterface::getProperty(
    const QString &session_handle,
    const QString &key)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetProperty"),
      argumentList);
}

QDBusReply<QStringList> DBusInterface::getState() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("GetState"),
      argumentList);
}

QDBusReply<QString> DBusInterface::newSearch(
    const QString &session_handle,
    const QString &query_xml)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(query_xml);
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSearch"),
      argumentList);
}

QDBusReply<QString> DBusInterface::newSession() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSession"),
      argumentList);
}

QDBusReply<QDBusVariant> DBusInterface::setProperty(
                                const QString &session_handle,
                                const QString &key, const QDBusVariant &value)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key) << qVariantFromValue(value);
  return callWithArgumentList(QDBus::Block, QLatin1String("SetProperty"),
      argumentList);
}

QDBusReply<void> DBusInterface::startSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::NoBlock, QLatin1String("StartSearch"),
      argumentList);
}

void DBusInterface::setPropertySortOrder(const QString& session_handle,
                        const QString& propertyName, const Qt::SortOrder& order)
{
  QString value;
  if (order == Qt::AscendingOrder)
    value = "ascending";
  else
    value = "descending";

  this->setProperty(session_handle, propertyName, QDBusVariant(value));
}

Qt::SortOrder DBusInterface::getPropertySortOrder(
                                            const QString& session_handle,
                                            const QString& propertyName)
{
  QDBusVariant dbusVariant;
  dbusVariant = this->getProperty(session_handle, propertyName).value();
  QString order = dbusVariant.variant().toString();
  if (order.compare("ascending") == 0)
    return Qt::AscendingOrder;

  return Qt::DescendingOrder;
}

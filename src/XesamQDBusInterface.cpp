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

#include "XesamQDBusInterface.h"

//#include "dbusoperators.h"

#include <QtDBus/QDBusArgument>

using namespace XesamQLib;

XesamQDBusInterface::XesamQDBusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
  m_closed = false;
  qDBusRegisterMetaType<XesamQLib::Hit>();
  qDBusRegisterMetaType<XesamQLib::Hit::List>();
}

XesamQDBusInterface::~XesamQDBusInterface()
{
}

QDBusReply<void> XesamQDBusInterface::CloseSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::Block, QLatin1String("CloseSearch"),
      argumentList);
}

QDBusReply<void> XesamQDBusInterface::CloseSession(const QString &session_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle);
  return callWithArgumentList(QDBus::Block,
      QLatin1String("CloseSession"), argumentList);
}

QDBusReply<uint> XesamQDBusInterface::GetHitCount(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  QDBusMessage msg = callWithArgumentList(QDBus::Block, QLatin1String("GetHitCount"),
      argumentList);
  qDebug() << msg;
  return msg;
}

QDBusReply<QList<QVariantList> > XesamQDBusInterface::GetHitData(
                    const QString &search_handle, const QList<quint32> &hit_ids,
                    const QStringList &fields)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(hit_ids) << qVariantFromValue(fields);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHitData"),
      argumentList);
}

QDBusReply<Hit::List > XesamQDBusInterface::GetHits(
    const QString &search_handle, uint count) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(count);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHits"),
      argumentList);
 }

QDBusReply<QDBusVariant> XesamQDBusInterface::GetProperty(
    const QString &session_handle,
    const QString &key)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetProperty"),
      argumentList);
}

QDBusReply<QStringList> XesamQDBusInterface::GetState() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("GetState"),
      argumentList);
}

QDBusReply<QString> XesamQDBusInterface::NewSearch(
    const QString &session_handle,
    const QString &query_xml)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(query_xml);
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSearch"),
      argumentList);
}

QDBusReply<QString> XesamQDBusInterface::NewSession() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSession"),
      argumentList);
}

QDBusReply<QDBusVariant> XesamQDBusInterface::SetProperty(
                                const QString &session_handle,
                                const QString &key, const QDBusVariant &value)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key) << qVariantFromValue(value);
  return callWithArgumentList(QDBus::Block, QLatin1String("SetProperty"),
      argumentList);
}

QDBusReply<void> XesamQDBusInterface::StartSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::Block, QLatin1String("StartSearch"),
      argumentList);
}

void XesamQDBusInterface::SetPropertySortOrder(const QString& session_handle,
                          const QString& propertyName, const SortOrder& order)
{
  QString value;
  if (order == Ascending)
    value = "ascending";
  else
    value = "descending";

  this->SetProperty(session_handle, propertyName, QDBusVariant(value));
}

SortOrder XesamQDBusInterface::GetPropertySortOrder(
                                            const QString& session_handle,
                                            const QString& propertyName)
{
  QDBusVariant dbusVariant;
  dbusVariant = this->GetProperty(session_handle, propertyName).value();
  QString order = dbusVariant.variant().toString();
  if (order.compare("ascending") == 0)
    return Ascending;

  return Descending;
}

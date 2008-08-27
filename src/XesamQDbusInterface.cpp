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

using namespace XesamQLib;

XesamQDbusInterface::XesamQDbusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
  m_closed = false;
}

XesamQDbusInterface::~XesamQDbusInterface()
{
}

XesamQSearcher* XesamQDbusInterface::searcher() {
  return new XesamQDbusSearcher (this);
}


QDBusReply<void> XesamQDbusInterface::CloseSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::Block, QLatin1String("CloseSearch"),
      argumentList);
}

QDBusReply<void> XesamQDbusInterface::CloseSession(const QString &session_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle);
  return callWithArgumentList(QDBus::Block,
      QLatin1String("CloseSession"), argumentList);
}

QDBusReply<uint> XesamQDbusInterface::GetHitCount(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHitCount"),
      argumentList);
}

QDBusReply<QList<QVariantList> > XesamQDbusInterface::GetHitData(
                    const QString &search_handle, const QList<quint32> &hit_ids,
                    const QStringList &fields)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(hit_ids) << qVariantFromValue(fields);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHitData"),
      argumentList);
}

QDBusReply<QList<QVariantList> > XesamQDbusInterface::GetHits(
    const QString &search_handle, uint count) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle)
      << qVariantFromValue(count);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetHits"),
      argumentList);
}

QDBusReply<QDBusVariant> XesamQDbusInterface::GetProperty(
    const QString &session_handle,
    const QString &key)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key);
  return callWithArgumentList(QDBus::Block, QLatin1String("GetProperty"),
      argumentList);
}

QDBusReply<QStringList> XesamQDbusInterface::GetState() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("GetState"),
      argumentList);
}

QDBusReply<QString> XesamQDbusInterface::NewSearch(
    const QString &session_handle,
    const QString &query_xml)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(query_xml);
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSearch"),
      argumentList);
}

QDBusReply<QString> XesamQDbusInterface::NewSession() {
  QList<QVariant> argumentList;
  return callWithArgumentList(QDBus::Block, QLatin1String("NewSession"),
      argumentList);
}

QDBusReply<QDBusVariant> XesamQDbusInterface::SetProperty(
                                const QString &session_handle,
                                const QString &key, const QDBusVariant &value)
{
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(session_handle)
      << qVariantFromValue(key) << qVariantFromValue(value);
  return callWithArgumentList(QDBus::Block, QLatin1String("SetProperty"),
      argumentList);
}

QDBusReply<void> XesamQDbusInterface::StartSearch(const QString &search_handle) {
  QList<QVariant> argumentList;
  argumentList << qVariantFromValue(search_handle);
  return callWithArgumentList(QDBus::Block, QLatin1String("StartSearch"),
      argumentList);
}

void XesamQDbusInterface::SetPropertySortOrder(const QString& session_handle,
                          const QString& propertyName, const SortOrder& order)
{
  QString value;
  if (order == Ascending)
    value = "ascending";
  else
    value = "descending";

  this->SetProperty(session_handle, propertyName, QDBusVariant(value));
}

SortOrder XesamQDbusInterface::GetPropertySortOrder(
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

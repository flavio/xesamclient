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

#include "XesamQDbusSearcher.h"
#include "XesamQDbusInterface.h"

using namespace XesamQLib;

XesamQDbusSearcher::XesamQDbusSearcher(XesamQDbusInterface* interface)
  : m_dbusInterface (interface)
{       
  // TODO: finish
  //  connect (interface, SIGNAL())
}

XesamQDbusSearcher::~XesamQDbusSearcher()
{
}

void XesamQDbusSearcher::startSearch () {
  if (m_searchHandle.isEmpty())
    return;
  
  //TODO: check if session is ready
  
  m_dbusInterface->StartSearch( m_searchHandle);  
  emit started();
}

void XesamQDbusSearcher::closeSearch () {
  if (m_searchHandle.isEmpty())
    return;
  
  //TODO: check if session is ready

  m_dbusInterface->CloseSearch( m_searchHandle);  
  emit closed();
}

int XesamQDbusSearcher::getHitCount() {
  return m_dbusInterface->GetHitCount( m_searchHandle);
}

QList < QVariantList> XesamQDbusSearcher::getHits (int count){
  return m_dbusInterface->GetHits(m_searchHandle, count);
}

QList < QVariantList> XesamQDbusSearcher::getHitData (
                                          const QList<quint32>&  hit_ids,
                                          const QStringList& fields)
{
  return m_dbusInterface->GetHitData(m_searchHandle, hit_ids, fields);
}



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

#include "session_p.h"

#include "query.h"
#include "search.h"
#include "dbusinterface.h"

using namespace Xesam::Client;

SessionPrivate::SessionPrivate( const QString& bus_name,
                                            const QString& object_path,
                                            QObject * parent)
  :QObject(parent)
{
  m_dbusInterface = new DBusInterface (bus_name,
                                             object_path,
                                             QDBusConnection::sessionBus(),
                                             this);
  
  //connect 
  
  if (m_dbusInterface->isReady()) {
    m_sessionHandle = m_dbusInterface->newSession();
  
    connect ( m_dbusInterface, 
          SIGNAL (HitsAdded(const QString&, uint)),
          this,
          SLOT (slotHitsAdded(const QString&, uint)));
    
    connect ( m_dbusInterface,
          SIGNAL (HitsModified(const QString&, const QList<uint>&)),
          this,
          SLOT (slotHitsModified(const QString&, const QList<uint>&)));
    
    connect ( m_dbusInterface, 
          SIGNAL (HitsRemoved(const QString&, const QList<uint>&)),
          this,
          SLOT (slotHitsRemoved(const QString&, const QList<uint>&)));
    
    connect ( m_dbusInterface,
          SIGNAL (SearchDone(const QString&)),
          this,
          SLOT (slotSearchDone(const QString&)));
    
    connect ( m_dbusInterface,
              SIGNAL (StateChanged(const QStringList &)),
              this,
              SLOT (slotStateChanged(const QStringList&)));
    
    connect ( m_dbusInterface,
                  SIGNAL (StateChanged(const QStringList &)),
                  this,
                  SIGNAL (StateChanged(const QStringList &)));
  }
}
      
SessionPrivate::~SessionPrivate() {
  delete m_dbusInterface;
  m_dbusInterface = NULL;
  
  QMap<QString, Search*>::iterator iter;
  for (iter = m_searches.begin(); iter != m_searches.end(); iter++) {
    Search* search = iter.value();
    if (search != NULL)
      delete search;
  }
  
  m_searches.clear();
}
      
bool SessionPrivate::isReady() {
  return (m_dbusInterface->isReady() && !m_sessionHandle.isEmpty());
}
  
bool SessionPrivate::isClosed() {
  return m_sessionHandle.isEmpty();
}

void SessionPrivate::close() {
  m_dbusInterface->closeSession(m_sessionHandle);
  m_sessionHandle = "";
}

Search* SessionPrivate::newSearch(Query* query, const QStringList& hitFields) {
  Search* search = 0;
  QString searchHandle = m_dbusInterface->newSearch(m_sessionHandle,
                                                    query->getXml());

  if (searchHandle.isEmpty())
    return search;
  
  search = new Search (m_dbusInterface, searchHandle, hitFields);
  
  m_searches.insert( searchHandle, search);
  
  return search;
}

QDBusVariant SessionPrivate::getProperty(const QString& propName) {
  return m_dbusInterface->getProperty(m_sessionHandle, propName).value();
}

void SessionPrivate::setProperty (const QString& propName, const QDBusVariant& value) {
  m_dbusInterface->setProperty( m_sessionHandle, propName, value);
}

Qt::SortOrder SessionPrivate::sortOrder(const QString& propName) {
  return m_dbusInterface->getPropertySortOrder(m_sessionHandle, propName);
 }

 void SessionPrivate::setSortOrder(const QString& propName,
                                   const Qt::SortOrder& order) {
   m_dbusInterface->setPropertySortOrder(m_sessionHandle, propName, order);
 }

bool SessionPrivate::vendorState(VendorState& state, int& done) {
  QStringList ret = m_dbusInterface->getState();
  
  if (ret[0].compare ("Idle", Qt::CaseInsensitive) == 0)
    state = Idle;
  else if (ret[0].compare ("Update", Qt::CaseInsensitive) == 0) {
    state = Update;
    
    bool ok;
    done = ret[1].toInt(&ok);
    if (!ok)
      return false;
  }
  else if  (ret[0].compare ("FullIndex", Qt::CaseInsensitive) == 0) {
    state = FullIndex;
    
    bool ok;
    done = ret[1].toInt(&ok);
    if (!ok)
      return false;
  }
  else
    return false;
  
  return true;
}

void SessionPrivate::slotHitsAdded( const QString &search_handle,
                                          uint count) {
  qDebug() << "XesamQSessionPrivate::slotHitsAdded, count " << count;
  QMap<QString, Search*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    Search* search = match.value();
    search->slotHitsAdded( count);
  }
  else
      qDebug() << "unable to find search instance for handle" << search_handle;
}

void SessionPrivate::slotHitsModified(const QString &search_handle,
                                          const QList<uint> &hit_ids) {
  qDebug() << "XesamQSessionPrivate::slotHitsModified";
  QMap<QString, Search*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    Search* search = match.value();
    search->slotHitsModified(hit_ids);
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}

void SessionPrivate::slotHitsRemoved( const QString &search_handle,
                                          const QList<uint> &hit_ids) {
  qDebug() << "XesamQSessionPrivate::slotHitsRemoved";
  QMap<QString, Search*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    Search* search = match.value();
    search->slotHitsRemoved( hit_ids);
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}
  
void SessionPrivate::slotSearchDone(const QString &search_handle) {
  qDebug() << "XesamQSessionPrivate::slotSearchDone";
  QMap<QString, Search*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    Search* search = match.value();
    search->slotSearchDone();
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}

void SessionPrivate::slotStateChanged(const QStringList &state_info) {
  qDebug() << "XesamQSessionPrivate::slotStateChanged";
  emit stateChanged( state_info);
}

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

#include "XesamQSession_p.h"

#include "XesamQQuery.h"
#include "XesamQSearch.h"
#include "XesamQDBusInterface.h"

using namespace XesamQLib;

XesamQSessionPrivate::XesamQSessionPrivate( const QString& bus_name,
                                            const QString& object_path,
                                            QObject * parent)
  :QObject(parent)
{
  m_dbusInterface = new XesamQDBusInterface (bus_name,
                                             object_path,
                                             QDBusConnection::sessionBus(),
                                             this);
  
  //connect 
  
  if (m_dbusInterface->isReady()) {
    m_sessionHanlde = m_dbusInterface->NewSession();
  
    connect ( m_dbusInterface, 
          SIGNAL (HitsAdded(const QString&, quint32)),
          this,
          SLOT (slotHitsAdded(const QString&, quint32)));
    
    connect ( m_dbusInterface,
          SIGNAL (HitsModified(const QString&, const QList<quint32>&)),
          this,
          SLOT (slotHitsModified(const QString&, const QList<quint32>&)));
    
    connect ( m_dbusInterface, 
          SIGNAL (HitsRemoved(const QString&, const QList<quint32>&)),
          this,
          SLOT (slotHitsRemoved(const QString&, const QList<quint32>&)));
    
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
                  SIGNAL (stateChanged(const QStringList &)));
  }
}
      
XesamQSessionPrivate::~XesamQSessionPrivate() {
  delete m_dbusInterface;
  m_dbusInterface = NULL;
  
  QMap<QString, XesamQSearch*>::iterator iter;
  for (iter = m_searches.begin(); iter != m_searches.end(); iter++) {
    XesamQSearch* search = iter.value();
    if (search != NULL)
      delete search;
  }
  
  m_searches.clear();
}
      
bool XesamQSessionPrivate::isReady() {
  return (m_dbusInterface->isReady() && !m_sessionHanlde.isEmpty());
}
  
bool XesamQSessionPrivate::isClosed() {
  return m_sessionHanlde.isEmpty();
}

void XesamQSessionPrivate::close() {
  m_dbusInterface->CloseSession(m_sessionHanlde);
  m_sessionHanlde = "";
}

XesamQSearch* XesamQSessionPrivate::newSearch(XesamQQuery* query) {
  XesamQSearch* search = 0;
  QString searchHandle = m_dbusInterface->NewSearch(m_sessionHanlde,
                                                    query->getXml());
  
  search = new XesamQSearch (m_dbusInterface, searchHandle);
  
  m_searches.insert( searchHandle, search);
  
  return search;
}

XesamQSearch* XesamQSessionPrivate::newSearchFromText(const QString& searchText) {
  XesamQSearch* search = 0;
  XesamQQuery* query = XesamQQuery::fromText(searchText);
  QString searchHandle = m_dbusInterface->NewSearch(m_sessionHanlde, query->getXml());

  if (searchHandle.isEmpty())
    return search;
  
  search = new XesamQSearch (m_dbusInterface, searchHandle);
  
  delete query;
  
  m_searches.insert( searchHandle, search);
  
  return search;
}

QDBusVariant XesamQSessionPrivate::getProperty(const QString& propName) {
  return m_dbusInterface->GetProperty(m_sessionHanlde, propName).value();
}

void XesamQSessionPrivate::setProperty (const QString& propName, const QDBusVariant& value) {
  m_dbusInterface->SetProperty( m_sessionHanlde, propName, value);
}

SortOrder XesamQSessionPrivate::sortOrder(const QString& propName) {
  return m_dbusInterface->GetPropertySortOrder(m_sessionHanlde, propName);
 }

 void XesamQSessionPrivate::setSortOrder(const QString& propName, const SortOrder& order) {
   m_dbusInterface->SetPropertySortOrder(m_sessionHanlde, propName, order);
 }

bool XesamQSessionPrivate::vendorState(VendorState& state, int& done) {
  QStringList ret = m_dbusInterface->GetState();
  
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

void XesamQSessionPrivate::slotHitsAdded( const QString &search_handle,
                                          quint32 count) {
  qDebug() << "XesamQSessionPrivate::slotHitsAdded, count " << count;
  QMap<QString, XesamQSearch*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    XesamQSearch* search = match.value();
    search->slotHitsAdded( count);
  }
  else
      qDebug() << "unable to find search instance for handle" << search_handle;
}

void XesamQSessionPrivate::slotHitsModified(const QString &search_handle,
                                          const QList<quint32> &hit_ids) {
  qDebug() << "XesamQSessionPrivate::slotHitsModified";
  QMap<QString, XesamQSearch*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    XesamQSearch* search = match.value();
    search->slotHitsModified(hit_ids);
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}

void XesamQSessionPrivate::slotHitsRemoved( const QString &search_handle,
                                          const QList<quint32> &hit_ids) {
  qDebug() << "XesamQSessionPrivate::slotHitsRemoved";
  QMap<QString, XesamQSearch*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    XesamQSearch* search = match.value();
    search->slotHitsRemoved( hit_ids);
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}
  
void XesamQSessionPrivate::slotSearchDone(const QString &search_handle) {
  qDebug() << "XesamQSessionPrivate::slotSearchDone";
  QMap<QString, XesamQSearch*>::iterator match = m_searches.find(search_handle);
  if (match != m_searches.end()) {
    XesamQSearch* search = match.value();
    search->slotSearchDone();
  }
  else
    qDebug() << "unable to find search instance for handle" << search_handle;
}

void XesamQSessionPrivate::slotStateChanged(const QStringList &state_info) {
  qDebug() << "XesamQSessionPrivate::slotStateChanged";
  emit stateChanged( state_info);
}

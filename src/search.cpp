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

#include "search.h"
#include "dbusinterface.h"

using namespace Xesam::Client;

class Search::Private {

  private:
    bool m_continueRead;
    uint m_numFound;
    uint m_numRead;
    DBusInterface* m_searchInterface;
    QString m_searchHandle;

  public:
    Private(DBusInterface* searchInterface, const QString& searchHandle) :
      m_searchInterface(searchInterface), m_searchHandle(searchHandle) {
      m_continueRead = true;
      m_numFound = 0;
      m_numRead = 0;
    }

    ~Private() {
    }

    bool continueRead() {
      return m_continueRead;
    }

    void setContinueRead(bool value) {
      m_continueRead = value;
    }

    int getNumFound() {
      return m_numFound;
    }

    void retrieveHits() {
      //      int numRead = qMin (pendingHits(), m_maxBatchSize);
      //      
      //      if (numRead == 0) {
      //        qDebug() << "Ingnoring retrieveHits request: no pending hits";
      //        return;
      //      } else if (!m_continueRead) {
      //        qDebug() << "Ingnoring retrieveHits request: \"continue read \""
      //                    "not set";
      //        return;
    }

    void startSearch() {
      m_searchInterface->startSearch(m_searchHandle);
    }

    void closeSearch() {
      m_searchInterface->closeSearch(m_searchHandle);
    }

    int getNumRead() {
      //TODO: code it!
      return 0;
    }

    int getHitCount() {
      return m_searchInterface->getHitCount(m_searchHandle);
    }

    ListVariantList getHits(uint count) {
      return m_searchInterface->getHits(m_searchHandle, count);
    }

    ListVariantList getHitData(const QList<uint>& hit_ids,
        const QStringList& fields) {
      return m_searchInterface->getHitData(m_searchHandle, hit_ids, fields);
    }
};

Search::Search( DBusInterface* searchInterface,
                const QString& searchHandle,
                const QStringList& hitFields,
                QObject * parent)
  : QObject(parent),
    p(new Search::Private (searchInterface, searchHandle)),
    m_hitFields (hitFields),
    m_hanlde (searchHandle),
    m_started (false)    
{
}

Search::~Search() {
  delete p;
}

void Search::continueSearch() {
  p->setContinueRead( true);
  p->retrieveHits();
}

void Search::start() {
  p->startSearch();
  m_started = true;
}

void Search::close() {
  p->closeSearch();
  emit closed();
}

int Search::getNumFound() {
  return p->getNumFound();
}

int Search::getNumRead() {
  return p->getNumRead();
}

QStringList Search::getHitFields() {
  return m_hitFields;
}

void Search::slotParentSessionClosed() {
  //TODO: do something
}
int Search::getHitCount() {
  return p->getHitCount();
}

SearchHits Search::getHits(uint count) {
  ListVariantList result = p->getHits(count);
  
  return SearchHits (this->getHitFields(), result);  
}

ListVariantList Search::getHitData(const QList<uint> &hit_ids,
                                               const QStringList& fields) {
  return p->getHitData(hit_ids, fields);
}

void Search::slotHitsAdded(uint count) {
  emit   hitsAdded();
}

void Search::slotHitsModified(const QList<uint> &hit_ids) {
  emit   hitsModified();
}

void Search::slotHitsRemoved(const QList<uint> &hit_ids) {
  emit   hitsRemoved();
}

void Search::slotSearchDone() {
  emit   done();
}

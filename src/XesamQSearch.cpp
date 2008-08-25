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

#include "XesamQSearch.h"

#include "XesamQSearcher.h"

#include <QObject>

using namespace XesamQLib;
namespace XesamQLib {
  
  class XesamQSearch::Private {
      
    private:
      bool m_continueRead;
      quint32 m_numFound;
      quint32 m_numRead;
      XesamQSearcher* m_searcher;
    
    public:
      Private(XesamQSearcher* searcher)
//        : QObject ()
      {
        m_continueRead = true;
        m_numFound = 0;
        m_numRead = 0;
        m_searcher = searcher;
      }
      
      ~Private() {
        delete m_searcher;
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
        
        //m_searcher->
        
  //      m_continueRead = false;
      
      void startSearch() {
        m_searcher->startSearch();
      }
      
      void closeSearch() {
        m_searcher->closeSearch();
      }
  
      int getNumRead() {
        //TODO: code it!
        return 0;
      }
      
      int getHitCount() {
        return m_searcher->getHitCount();
      }
      
      QList<QVariantList> getHits(quint32 count) {
        return m_searcher->getHits(count);
      }
      
      QList < QVariantList> getHitData (const QList<quint32>& hit_ids,
                                              const QStringList& fields) {
        return m_searcher->getHitData( hit_ids, fields);
      }
  };
}

XesamQSearch::XesamQSearch(XesamQSearcher* searcher, QObject * parent)
  : QObject(parent),
    p (new XesamQSearch::Private (searcher))
{
}

XesamQSearch::~XesamQSearch()
{
  delete p;
}

void XesamQSearch::continueSearch() {
  p->setContinueRead( true);
  p->retrieveHits();
}

//XesamQSession* XesamQQuery::getSession() {
//  return m_searcher->session();
//}

//const QString& XesamQSearch::id() {
//  return p->m_handler;
//}

void XesamQSearch::start() {
  p->startSearch();
  emit started();
}

void XesamQSearch::close() {
  p->closeSearch();
  emit closed();
}

int XesamQSearch::getNumFound() {
  return p->getNumFound();
}

int XesamQSearch::getNumRead() {
  return p->getNumRead();
}

void XesamQSearch::slotParentSessionClosed() {
  //TODO: do something
}
int XesamQSearch::getHitCount() {
  return p->getHitCount();
}

QList<QVariantList> XesamQSearch::getHits(quint32 count)
{
  return p->getHits(count);
}

QList < QVariantList>
XesamQSearch::getHitData (const QList<quint32> &hit_ids,
                          const QStringList& fields) {
  return p->getHitData (hit_ids, fields);
}

void XesamQSearch::slotHitsAdded( quint32 count) {
  emit hitsAdded();
}

void XesamQSearch::slotHitsModified( const QList<quint32> &hit_ids) {
  emit hitsModified();
}

void XesamQSearch::slotHitsRemoved( const QList<quint32> &hit_ids) {
  emit hitsRemoved();
}

void XesamQSearch::slotSearchDone() {
  emit done();
}

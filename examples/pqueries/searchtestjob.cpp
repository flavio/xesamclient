#include "searchtestjob.h"
#include "search.h"
#include "searchhit.h"

#include <QtCore/QDebug>
#include <QtCore/QVariant>

using namespace Xesam::Client;

SearchTestJob::SearchTestJob(Search* search, QObject* parent)
  : QThread (parent),
    m_search (search)
{
  m_search->setParent(this);
  m_done = false;
  
  connect(m_search, SIGNAL (closed()), this, SLOT(slotClosed()));
  connect(m_search, SIGNAL (done()), this, SLOT(slotDone()));
  connect(m_search, SIGNAL (extendedDataReady()), this, SLOT(slotExtendedDataReady()));
  connect(m_search, SIGNAL (hitsAdded()), this, SLOT(slotHitsAdded()));
  connect(m_search, SIGNAL (hitsModified()), this, SLOT(slotHitsModified()));
  connect(m_search, SIGNAL (hitsRemoved()), this, SLOT(slotHitsRemoved()));
  connect(m_search, SIGNAL (ready()), this, SLOT(slotReady()));
}

SearchTestJob::~SearchTestJob()
{
//  delete m_search;
}

void SearchTestJob::run() {
  qDebug () << "SearchTestJob for query:" << m_search->id() << "started";
  
  m_search->start();
  
  bool done = false;
  
  while (!done) {
    sleep (1);
    
    m_mutex.lock();
    done = m_done;
    m_mutex.unlock();
  }
  
//  m_mutex.lock();
//  m_wait.wait(&m_mutex);
//  m_mutex.unlock();
  
  qDebug () << "SearchTestJob for query:" << m_search->id() << "finished";
  
  quit();
}

void SearchTestJob::slotClosed() {
  qDebug() << "SearchTestJob::closed" << endl;
}

void SearchTestJob::slotDone() {
  qDebug() << "SearchTestJob::slotDone()" << endl;

  int count = m_search->getHitCount();
  qDebug() << "search->getHitCount() returned " << count << endl;
  SearchHits searchHits = m_search->getHits(count);

  qDebug() << "hits size: " << searchHits.size() << endl;
  qDebug() << "hit field = " << searchHits.hitFields();

  if (searchHits.size() != 0) {
    qDebug() << "Printing hits:" << endl;
    QList<SearchHit*> hits = searchHits.hits();
    foreach (SearchHit* hit, hits) {
      QString msg = "[ ";
      foreach (QVariant result, hit->results()) {
        msg += "|" + result.toString() + "| ";
      }
      msg += "]";
      qDebug() << msg;
    }
  }
  
//  m_wait.wakeAll();
  m_mutex.lock();
  m_done = true;
  m_mutex.unlock();
}

void SearchTestJob::slotExtendedDataReady() {
  qDebug() << "SearchTestJob::extendedDataReady" << endl;
}

void SearchTestJob::slotHitsAdded() {
  qDebug() << "SearchTestJob::hitsAdded" << endl;
}

void SearchTestJob::slotHitsModified() {
  qDebug() << "SearchTestJob::hitsModified" << endl;
}
void SearchTestJob::slotHitsRemoved() {
  qDebug() << "SearchTestJob::hitsRemoved" << endl;
}

void SearchTestJob::slotReady() {
  qDebug() << "SearchTestJob::ready" << endl;
}

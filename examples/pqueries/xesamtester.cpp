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

#include "xesamtester.h"

#include "session.h"
#include "search.h"
#include "searchtestjob.h"

#include <QtCore/QDebug>

using namespace Xesam::Client;

XesamTester::XesamTester(QObject* parent)
  : QThread(parent)
{
  m_session = new Session (this);
  
  QStringList hitFields;
  hitFields << "xesam:url";
  hitFields << "xesam:size";
  m_session->setHitFields(hitFields);

  m_jobsTodoCounter = 0;
  
  if (m_session->isReady())
    qDebug() << "Service available" << endl;
  else
    qDebug() << "Service NOT available" << endl;
}

XesamTester::~XesamTester() {
}

void XesamTester::query(const QString& query) {
  Search* search = m_session->newSearchFromText(query);
  if (search == 0) {
    qCritical() << "Got a null search instance for query:" << query << endl;
    return;
  }    

  QMutexLocker locker (& m_jobsTodoMutex);
  
  SearchTestJob* testJob = new SearchTestJob (search, this);
  connect (testJob, SIGNAL (finished()), this, SLOT (slotJobFinished()));

  m_searches.push_back( testJob);
  
  if (this->isRunning())
    testJob->start();

  m_jobsTodoCounter++;
}

void XesamTester::run() {
  if (m_jobsTodoCounter == 0) {
    qDebug() << "Nothing to do, exiting";
    quit();
  }
  
  qDebug() << "XesamTester started";

  foreach (SearchTestJob* search, m_searches)
    search->start();
  
  m_mutex.lock();
  m_waitCondition.wait(&m_mutex);
  
  qDebug() << "XesamTester finished";
  quit();
}

void XesamTester::slotJobFinished() {
  QMutexLocker locker (& m_jobsTodoMutex);
  m_jobsTodoCounter--;
  
  qDebug () << "XesamTester::slotJobFinished() - there're"
            << m_jobsTodoCounter << "jobs in TODO list";
  
  if (m_jobsTodoCounter == 0)
    m_waitCondition.wakeAll();
}

void XesamTester::vendorState() {
  VendorState state;
  int done = 0;

  if (m_session->vendorState(state, done)) {
    switch (state) {
      case Idle:
        qDebug() << "Idle" << endl;
        break;
      case Update:
        qDebug() << "Update [" << done << "]" << endl;
        break;
      case FullIndex:
        qDebug() << "FullIndex [" << done << "]" << endl;
        break;
    }
  } else
    qDebug() << "Unable to fetch vendor state" << endl;
}

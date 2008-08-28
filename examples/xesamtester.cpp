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

#include <iostream>

#include <QCoreApplication>

#include <QDebug>

using namespace Xesam::Client;
using namespace std;

XesamTester::XesamTester() :
  QObject() {
  session = new Session ();
  search = NULL;

  if (session->isReady())
    cout << "Service available" << endl;
  else
    cout << "Service NOT available" << endl;
}

XesamTester::~XesamTester() {
  if (session != NULL) {
    session->close();

    if (session->isClosed())
      cout << "Session is closed" << endl;
    else
      cout << "Session is NOT closed" << endl;

    delete session;
  }
}

void XesamTester::query(const QString& query) {
  search = session->newSearchFromText(query);
  if (search == 0)
    return;

  cout << "starting query" << endl;

  connect(search, SIGNAL (closed()), this, SLOT(slotClosed()));
  connect(search, SIGNAL (done()), this, SLOT(slotDone()));
  connect(search, SIGNAL (extendedDataReady()), this, SLOT(slotExtendedDataReady()));
  connect(search, SIGNAL (hitsAdded()), this, SLOT(slotHitsAdded()));
  connect(search, SIGNAL (hitsModified()), this, SLOT(slotHitsModified()));
  connect(search, SIGNAL (hitsRemoved()), this, SLOT(slotHitsRemoved()));
  connect(search, SIGNAL (ready()), this, SLOT(slotReady()));
  connect(search, SIGNAL (started()), this, SLOT(slotStarted()));

  search->start();
}

void XesamTester::slotClosed() {
  cout << "XesamTester::closed" << endl;
}

void XesamTester::slotDone() {
  cout << "XesamTester::slotDone()" << endl;

  int count = search->getHitCount();
  cout << "search->getHitCount() returned " << count << endl;
  QList <Hit> hits = search->getHits(count);

  cout << "hits size: " << hits.size() << endl;
  if (hits.size() != 0) {
    cout << "Printing hits:" << endl;
    foreach (QVariantList hit, hits) {
      foreach (QVariant variant, hit) {
        //cout << variant.toString().toStdString() << endl;
        qDebug() << variant.toString();
      }
    }
  }
  
  QCoreApplication::exit(0);
}

void XesamTester::slotExtendedDataReady() {
  cout << "XesamTester::extendedDataReady" << endl;
}

void XesamTester::slotHitsAdded() {
  cout << "XesamTester::hitsAdded" << endl;
}

void XesamTester::slotHitsModified() {
  cout << "XesamTester::hitsModified" << endl;
}
void XesamTester::slotHitsRemoved() {
  cout << "XesamTester::hitsRemoved" << endl;
}

void XesamTester::slotReady() {
  cout << "XesamTester::ready" << endl;
}

void XesamTester::slotStarted() {
  cout << "XesamTester::started" << endl;
}

void XesamTester::vendorState() {
  VendorState state;
  int done = 0;

  if (session->vendorState(state, done)) {
    switch (state) {
      case Idle:
        cout << "Idle" << endl;
        break;
      case Update:
        cout << "Update [" << done << "]" << endl;
        break;
      case FullIndex:
        cout << "FullIndex [" << done << "]" << endl;
        break;
    }
  } else
    cout << "Unable to fetch vendor state" << endl;
}

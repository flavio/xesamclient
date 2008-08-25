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

#include "XesamTester.h"

#include "XesamQSession.h"
#include "XesamQSearch.h"

#include <iostream>

using namespace XesamQLib;
using namespace std;

XesamTester::XesamTester()
  : QObject()
{
  session = new XesamQSession ();
  search = NULL;
    
  if (session->isReady())
    cout << "Service available" << endl;
  else
    cout << "Service NOT available" << endl;
}

XesamTester::~XesamTester()
{
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
  cout << "starting query" << endl;
  search = session->newSearchFromText( query);
  
  connect (search, SIGNAL (closed()), this, SLOT(slotClosed()));
  connect (search, SIGNAL (done()), this, SLOT(slotDone()));
  connect ( search, SIGNAL (extendedDataReady()),
            this, SLOT(slotExtendedDataReady()));
  connect (search, SIGNAL (hitsAdded()), this, SLOT(slotHitsAdded()));
  connect (search, SIGNAL (hitsModified()), this, SLOT(slotHitsModified()));
  connect (search, SIGNAL (hitsRemoved()), this, SLOT(slotHitsRemoved()));
  connect (search, SIGNAL (ready()), this, SLOT(slotReady()));
  connect (search, SIGNAL (started()), this, SLOT(slotStarted()));
  connect (search, SIGNAL (done()), this, SLOT (slotDone()));
  
  search->start();
}

void XesamTester::slotClosed() {
  cout << "XesamTester::closed" << endl;
}

void XesamTester::slotDone() {
  cout << "XesamTester::done" << endl;

  int count = search->getHitCount();
  cout << "search->getHitCount() " << count << endl;
  QList <QVariantList> hits = search->getHits(count);
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

void XesamTester::vendorState () {
  VendorState state;
  int done = 0;
  
  if (session->vendorState(state, done)) {
    switch (state){
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
  }
  else
    cout << "Unable to fetch vendor state" << endl;
}

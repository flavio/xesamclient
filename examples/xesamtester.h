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

#ifndef XESAMTESTER_H_
#define XESAMTESTER_H_

#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QThread>
#include <QtCore/QWaitCondition>

namespace Xesam {
  namespace Client {
    class Session;
  }
}
class SearchTestJob;

class XesamTester : public QThread
{
  Q_OBJECT
  
  public:
  	XesamTester(QObject* parent = 0);
  	virtual ~XesamTester();
  	
  	void query (const QString&);
  	void vendorState();

    void run();
  	
  private Q_SLOTS:
    void slotJobFinished();
    
  private:
    QVector <SearchTestJob*> m_searches;
    
    Xesam::Client::Session* m_session;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
    
    QMutex m_jobsTodoMutex;
    uint m_jobsTodoCounter;
};

#endif /*XESAMTESTER_H_*/

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

#ifndef SEARCHTESTJOB_H_
#define SEARCHTESTJOB_H_

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

namespace Xesam {
  namespace Client {
    class Search;
  }
}

class SearchTestJob : public QThread 
{
  Q_OBJECT
  
  public:
	SearchTestJob(Xesam::Client::Search* search, QObject* parent = 0);
	virtual ~SearchTestJob();
	
    void run();
    
  private slots:
    void slotClosed();
    void slotDone();
    void slotExtendedDataReady();
    void slotHitsAdded();
    void slotHitsModified();
    void slotHitsRemoved();
    void slotReady();
    
  private:
    Xesam::Client::Search* m_search;
    QMutex m_mutex;
    QWaitCondition m_wait;
    bool m_done;
};

#endif /*SEARCHTESTJOB_H_*/

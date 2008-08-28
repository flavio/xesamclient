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

#ifndef SEARCH_H
#define SEARCH_H

#include <QtCore/QObject>
#include <QtDBus/QDBusVariant>

#include "globals.h"

namespace Xesam {
  namespace Client {

    class DBusInterface;
  
    /*!
     * \brief Client side representation of a search
     *
     * Search is a client side representation of a search.
     * A search is created via a Session object's
     * Session::newSearchFromText Session::newSearch methods.
     * All communications with the search engine is completely asynchronous.
     * When hits are available the "hits-ready" signal will be emitted.
     * A search will not emit any hits before the start method is invoked.
     */
    class Search : public QObject {
      Q_OBJECT
  
  //    Q_PROPERTY(int maxBatchSize READ maxBatchSize WRITE setMaxBatchSize)
  
      public:
        Search(DBusInterface*, const QString&, QObject * parent = 0);
        ~Search();
  
        /*! Instruct the server to start a given search.
         * No hits will be returned before this method has been invoked.
         * */
        void start();
  
        /*!
         * Close a search. The server is allowed to free all resources related to
         * the search when this method is invoked.
         *
         * A closed search is considered invalid for further use.
         *
         * There are two ways in which a search can automatically be closed.
         * If the last reference to the search is dropped (the object is
         * finalized), or if the parent session is closed.
         *
         * A search will be marked closed as soon as xesam_g_search_close() is
         * invoked. The "closed" signal will be emitted when the close request has
         * been acknowledged by the underlying XesamGSearcher.
         */
        void close();
        void continueSearch();
        int  getNumFound();
        int  getNumRead();
        int  getHitCount();
        Hit::List getHits(uint count);
        QList <QVariantList> getHitData (const QList<uint>&,
                                          const QStringList&);
  
        //xesam_g_search_get_extended_data ()
  
      public Q_SLOTS:
        void slotHitsAdded( uint count);
        void slotHitsModified( const QList<uint> &hit_ids);
        void slotHitsRemoved( const QList<uint> &hit_ids);
        void slotSearchDone();
  
      private Q_SLOTS:
        void slotParentSessionClosed();
  
      Q_SIGNALS:
        void closed();
        void done();
        void extendedDataReady();
        void hitsAdded();
        void hitsModified();
        void hitsRemoved();
        void ready();
        void started();
  
      private:
        class Private;
        Private* const p;
    };
  }
}

#endif

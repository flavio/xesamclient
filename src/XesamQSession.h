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

#ifndef XESAMQSESSION_H
#define XESAMQSESSION_H

#include <QObject>
#include <QStringList>

#include "XesamQGlobals.h"

namespace XesamQLib {

  class Search;
  class Query;
  class SessionPrivate;

  /*!
   * \brief A client connection to a search engine
   *
   * Central class for clients. It provides facilities for setting/retrieving
   * Xesam properties. It is also used for managing Xesam searches.
   */


  class Session : public QObject {
    Q_OBJECT

    Q_PROPERTY(QStringList hitfields READ hitFields WRITE setHitFields)
    Q_PROPERTY(QStringList hitFieldsExtended  READ hitFieldsExtended
                                          WRITE setHitFieldsExtended)
    Q_PROPERTY(int hitSnippletLength READ hitSnippletLength
                                    WRITE setHitSnippletLength)
    Q_PROPERTY(bool searchLive READ searchLive WRITE setSearchLive)
    Q_PROPERTY(SortOrder sortOrder READ sortOrder WRITE setSortOrder)
    Q_PROPERTY(SortOrder sortPrimary READ sortPrimary WRITE setSortPrimary)
    Q_PROPERTY(SortOrder sortSecondary  READ sortSecondary
                                        WRITE setSortSecondary)
    Q_PROPERTY(QString vendorDisplay  READ vendorDisplay)
    Q_PROPERTY(QString vendorExtensions READ vendorExtensions)
    Q_PROPERTY(QString vendorId READ vendorId)
    Q_PROPERTY(int vendorMaxHits READ vendorMaxHits)
    Q_PROPERTY(QString vendorOntologyContents READ vendorOntologyContents)
    Q_PROPERTY(QString vendorOntologyFields READ vendorOntologyFields)
    Q_PROPERTY(QString vendorOntologySources READ vendorOntologySources)
    Q_PROPERTY(int vendorVersion READ vendorVersion)
    Q_PROPERTY(int vendorXesam READ vendorXesam)

    public:
      Session (const QString& bus_name = XESAM_SERVER_DBUS_NAME,
                     const QString& object_path = XESAM_SERVER_DBUS_OBJECT);
      ~Session();

      //     DBusGProxy*         xesam_g_session_get_proxy           (XesamGSession *session);
      //     gchar*              xesam_g_session_get_id              (XesamGSession *session);

      //! \return true if the session is ready, false otherwise
      bool isReady();

      /*! \return true if the connection with the Xesam server has been
      *     established, false otherwise*/
      bool isClosed();

      //! closes the connection with the Xesam server
      void close();

      //*TODO: useless?*/ void syncProperty(const QString property);

      /*! Creates a new Xesam search starting from a #Query object.
       *  \return a new #Search instance, a null pointer if the session
       *  is not ready.
       *  \sa Query
       */
      Search* newSearch (Query& query);

      /*! Creates a new Xesam search starting from a string containing a
       *  Xesam user language query.
       *
       *  \return a new #Search instance, a null pointer if the session
       *  is not ready.
       */
      Search* newSearchFromText (const QString& searchText);

      // properties methods
      QStringList hitFields();
      void  setHitFields(QStringList&);

      QStringList hitFieldsExtended();
      void setHitFieldsExtended(QStringList&);

      int hitSnippletLength();
      void setHitSnippletLength(int);

      bool searchLive();
      void setSearchLive(bool);

      SortOrder sortOrder();
      void setSortOrder(SortOrder&);

      SortOrder sortPrimary();
      void setSortPrimary (SortOrder&);

      SortOrder sortSecondary();
      void setSortSecondary(SortOrder&);

      QString vendorDisplay();
      QString vendorExtensions();
      QString vendorId();
      int vendorMaxHits();
      QString vendorOntologyContents ();
      QString vendorOntologyFields();
      QString vendorOntologySources();
      int vendorVersion();
      int vendorXesam();

      bool vendorState(VendorState&, int&);

    Q_SIGNALS:
      //! emitted when the connection with the Xesam server is closed
      void closed();

      //! emitted when Session is ready
      void ready();

    private:
      SessionPrivate* const p;
    };
}
#endif

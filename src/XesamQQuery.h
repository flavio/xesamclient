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

#ifndef XESAMQQUERY_H
#define XESAMQQUERY_H

/**
  @author Flavio Castelli <flavio.castelli@gmail.com>
*/

#include <QString>

namespace Xesam {
  namespace Client {

    /*!
     * \brief Structured representation of a query
     *
     * In Xesam terminology a 'query' is formatted string prepared for the search
     *  engine. A 'search' is the opaque representation of a query that has been
     *   accepted and is executing on the search engine.
     */
  
    class Query{
      private:
        Query();
  
        QString m_query;
  
      public:
        ~Query();
  
        /*! \return a string containing the xml description of the query,
         * formulated according to 'Xesam Query Language' specifications
         *
        */
        QString& getXml();
  
        /*!
         * Creates a new instance of Query
         *
         * \param xesamQlQuery string containing a query formulated with 'Xesam
         * Query Language'
         * \return a new Query instance
         *
         */
        static Query* fromXml (const QString& xesamQlQuery);
  
        /*!
         * Creates a new instance of Query
         *
         * \param xesamUlQuery string containing a query formulated with 'Xesam
         * User Language'
         * \return a new Query instance
         *
         */
        static Query* fromText (const QString& xesamUlQuery);
    };
  }
}

#endif

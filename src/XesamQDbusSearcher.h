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

#ifndef XESAMQDBUSSEARCHER_H_
#define XESAMQDBUSSEARCHER_H_

#include "XesamQSearcher.h" 

namespace XesamQLib {
  class XesamQDbusInterface;
  
  class XesamQDbusSearcher : public XesamQSearcher 
  {
    Q_OBJECT
    
    public:
    	XesamQDbusSearcher(XesamQDbusInterface*);
    	virtual ~XesamQDbusSearcher();
    	
    	void startSearch ();
    	void closeSearch();
      
      void setSearchHandle(const QString& searchHandle) {
        m_searchHandle = searchHandle;
      }
      
      int getHitCount();
      QList < QVariantList> getHits (int);
      QList < QVariantList> getHitData (const QList<quint32>&,
                                        const QStringList&);
      
    private:
      XesamQDbusInterface* m_dbusInterface;
      QString m_searchHandle;
  };
}

#endif /*XESAMQDBUSSEARCHER_H_*/

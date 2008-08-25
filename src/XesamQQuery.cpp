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

#include "XesamQQuery.h"

using namespace XesamQLib;

XesamQQuery::XesamQQuery()
{
}

XesamQQuery::~XesamQQuery()
{
}

QString& XesamQQuery::getXml() {
  return m_query;
}

XesamQQuery* XesamQQuery::fromXml (const QString& query) {
  //TODO: code it!
  XesamQQuery* q = new XesamQQuery();
  q->m_query = query;
  
  return q;
}
XesamQQuery* XesamQQuery::fromText (const QString& text) {
  XesamQQuery* q = new XesamQQuery();
  
  QString xmlQuery;
  xmlQuery = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  xmlQuery += "<request xmlns=\"http://freedesktop.org/standards/xesam/1.0/query\">";
  xmlQuery += "<userQuery>";
  xmlQuery += text;
  xmlQuery += "</userQuery>";
  xmlQuery += "</request>";
  
  q->m_query = xmlQuery;
  
  return q;
}

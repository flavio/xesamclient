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

#include "XesamQSession.h"
#include "XesamQGlobals.h"

#include <QString>

#include "XesamQQuery.h"
#include "XesamQSearch.h"
#include "XesamQSession.h"
#include "XesamQSession_p.h"

using namespace XesamQLib;

XesamQSession::XesamQSession (const QString& bus_name,
                              const QString& object_path)
  : QObject(),
    p ( new XesamQSessionPrivate (bus_name, object_path))
{
}

XesamQSession::~XesamQSession()
{
  delete p;
}

bool XesamQSession::isReady() {
  return p->isReady();
}

bool XesamQSession::isClosed() {
  return p->isClosed();
}

void XesamQSession::close() {
  p->close();
}

//TODO; session_sync_property

XesamQSearch* XesamQSession::newSearch(XesamQQuery& query) {
  return p->newSearch (&query);
}

XesamQSearch* XesamQSession::newSearchFromText(const QString& searchText) {
  return p->newSearchFromText (searchText);
}

// properties methods
QStringList XesamQSession::hitFields() {
  QDBusVariant dbusVariant = p->getProperty("hit.fields");
  return dbusVariant.variant().toStringList();
}

void XesamQSession::setHitFields(QStringList& value) {
  p->setProperty("hit.fields", QDBusVariant (value));
}

QStringList XesamQSession::hitFieldsExtended() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty("hit.fields.extended");
  return dbusVariant.variant().toStringList();
}

void XesamQSession::setHitFieldsExtended(QStringList& value) {
  p->setProperty( "hit.fields.extended", QDBusVariant(value));
}

int XesamQSession::hitSnippletLength() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "hit.snippet.length");
  return dbusVariant.variant().toInt();
}
void XesamQSession::setHitSnippletLength(int value) {
  p->setProperty( "hit.snippet.length", QDBusVariant (value));
}

bool XesamQSession::searchLive() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "search.live");
  return dbusVariant.variant().toBool();
}

void XesamQSession::setSearchLive(bool value) {
  p->setProperty( "search.live", QDBusVariant (value));
}

SortOrder XesamQSession::sortOrder() {
  return p->sortOrder( "sort.order");
}

void XesamQSession::setSortOrder(SortOrder& order) {
  p->setSortOrder( "sort.order", order);
}

SortOrder XesamQSession::sortPrimary() {
  return p->sortOrder( "sort.primary");
}

void XesamQSession::setSortPrimary (SortOrder& order) {
  p->setSortOrder( "sort.primary", order);
}

SortOrder XesamQSession::sortSecondary() {
  return p->sortOrder( "sort.secondary");
}
void XesamQSession::setSortSecondary(SortOrder& order) {
  p->setSortOrder( "sort.secondary", order);
}

QString XesamQSession::vendorDisplay() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.display");
  return dbusVariant.variant().toString();
}

QString XesamQSession::vendorExtensions() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.extensions");
  return dbusVariant.variant().toString();
}

QString XesamQSession::vendorId() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.id");
  return dbusVariant.variant().toString();
}

int XesamQSession::vendorMaxHits() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.maxhits");
  return dbusVariant.variant().toInt();  
}

QString XesamQSession::vendorOntologyContents () {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.contents");
  return dbusVariant.variant().toString();
}

QString XesamQSession::vendorOntologyFields() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.fields");
  return dbusVariant.variant().toString();
}

QString XesamQSession::vendorOntologySources() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.sources");
  return dbusVariant.variant().toString();
}

int XesamQSession::vendorVersion() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.version");
  return dbusVariant.variant().toInt();  
}

int XesamQSession::vendorXesam() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.xesam");
  return dbusVariant.variant().toInt();
}

bool XesamQSession::vendorState(VendorState& state, int& done) {
  return p->vendorState (state, done);
}

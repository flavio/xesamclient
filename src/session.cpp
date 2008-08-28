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

#include "globals.h"
#include "query.h"
#include "search.h"
#include "session.h"
#include "session_p.h"

using namespace Xesam::Client;

Session::Session (const QString& bus_name,
                              const QString& object_path)
  : QObject(),
    p ( new SessionPrivate (bus_name, object_path))
{
}

Session::~Session()
{
  delete p;
}

bool Session::isReady() {
  return p->isReady();
}

bool Session::isClosed() {
  return p->isClosed();
}

void Session::close() {
  p->close();
}

//TODO; session_sync_property

Search* Session::newSearch(Query& query) {
  // have to pass hitFields to private class because otherwise this value cannot
  // be retrieved from SessionPrivate
  return p->newSearch (&query, this->hitFields());
}

Search* Session::newSearchFromText(const QString& searchText) {
  Query* query = Query::fromText(searchText);

  Search* search = this->newSearch (*query);
  delete query;
  
  return search;
}

// properties methods
QStringList Session::hitFields() {
  QDBusVariant dbusVariant = p->getProperty("hit.fields");
  return dbusVariant.variant().toStringList();
}

void Session::setHitFields(QStringList& value) {
  p->setProperty("hit.fields", QDBusVariant (value));
}

QStringList Session::hitFieldsExtended() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty("hit.fields.extended");
  return dbusVariant.variant().toStringList();
}

void Session::setHitFieldsExtended(QStringList& value) {
  p->setProperty( "hit.fields.extended", QDBusVariant(value));
}

int Session::hitSnippletLength() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "hit.snippet.length");
  return dbusVariant.variant().toInt();
}
void Session::setHitSnippletLength(int value) {
  p->setProperty( "hit.snippet.length", QDBusVariant (value));
}

bool Session::searchLive() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "search.live");
  return dbusVariant.variant().toBool();
}

void Session::setSearchLive(bool value) {
  p->setProperty( "search.live", QDBusVariant (value));
}

SortOrder Session::sortOrder() {
  return p->sortOrder( "sort.order");
}

void Session::setSortOrder(SortOrder& order) {
  p->setSortOrder( "sort.order", order);
}

SortOrder Session::sortPrimary() {
  return p->sortOrder( "sort.primary");
}

void Session::setSortPrimary (SortOrder& order) {
  p->setSortOrder( "sort.primary", order);
}

SortOrder Session::sortSecondary() {
  return p->sortOrder( "sort.secondary");
}
void Session::setSortSecondary(SortOrder& order) {
  p->setSortOrder( "sort.secondary", order);
}

QString Session::vendorDisplay() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.display");
  return dbusVariant.variant().toString();
}

QString Session::vendorExtensions() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.extensions");
  return dbusVariant.variant().toString();
}

QString Session::vendorId() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.id");
  return dbusVariant.variant().toString();
}

int Session::vendorMaxHits() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.maxhits");
  return dbusVariant.variant().toInt();  
}

QString Session::vendorOntologyContents () {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.contents");
  return dbusVariant.variant().toString();
}

QString Session::vendorOntologyFields() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.fields");
  return dbusVariant.variant().toString();
}

QString Session::vendorOntologySources() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.ontology.sources");
  return dbusVariant.variant().toString();
}

int Session::vendorVersion() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.version");
  return dbusVariant.variant().toInt();  
}

int Session::vendorXesam() {
  QDBusVariant dbusVariant;
  dbusVariant = p->getProperty( "vendor.xesam");
  return dbusVariant.variant().toInt();
}

bool Session::vendorState(VendorState& state, int& done) {
  return p->vendorState (state, done);
}

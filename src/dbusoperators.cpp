#include "dbusoperators.h"
/*
QDBusArgument& operator<<(QDBusArgument& arg, const XesamQLib::Hit::List& data) {
  arg.beginArray(qMetaTypeId<QVariantList>());
  foreach(const QVariantList& list, data) {
    arg << list;
  }

  arg.endArray();
  return arg;
}

const QDBusArgument& operator>>(const QDBusArgument& arg,
    XesamQLib::Hit::List& list) {
  arg.beginArray();
  while ( !arg.atEnd()) {
    QVariantList v;
    arg >> v;
    list.append(XesamQLib::Hit(v));
  }
  arg.endArray();
  return arg;
}
*/
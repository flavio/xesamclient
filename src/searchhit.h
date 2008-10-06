#ifndef SEARCHHIT_H_
#define SEARCHHIT_H_

#include <QtCore/QList>
#include <QtCore/QVariant>

namespace Xesam {
  namespace Client {
    class SearchHit
    {
      public:
        SearchHit(const uint& id, const QVariantList& results);
        virtual ~SearchHit();
        
        QVariantList results () { return m_results;}
        
        uint id() { return m_id; }
        
      private:
        const QVariantList m_results;
        const uint m_id;
        
    };
  }
}

#endif /*SEARCHHIT_H_*/

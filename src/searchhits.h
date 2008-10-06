#ifndef SEARCHHITS_H_
#define SEARCHHITS_H_

#include <QtCore/QList>
#include <QtCore/QStringList>

#include "globals.h"

namespace Xesam {
  namespace Client {
    
    class SearchHit;
    
    class SearchHits
    {
      public:
        SearchHits(const QStringList& hitFields,
                   const ListVariantList& hits);
        virtual ~SearchHits();
        
        uint size() { return m_hits.size(); }
        
        QList<SearchHit*> hits() { return m_hits; }
        QStringList hitFields() { return m_hitFields; }
        
      private:
        QList<SearchHit*> m_hits;
        const QStringList m_hitFields;
    }; 
  }
}

#endif /*SEARCHHITS_H_*/

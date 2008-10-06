#include "searchhits.h"

#include "searchhit.h"

using namespace Xesam::Client;

SearchHits::SearchHits(const QStringList& hitFields,const ListVariantList& hits)
  : m_hitFields (hitFields)
{
  // should be needed at all, but it's free ;)
  m_hits.clear();
  
  foreach (QVariantList hit, hits) {
    // create single SearchHit objects
    SearchHit* searchHit = new SearchHit (m_hits.size(), hit);
    m_hits.push_back(searchHit);
  }
}

SearchHits::~SearchHits()
{
  foreach (SearchHit* searchHit, m_hits)
    delete searchHit;
  
  m_hits.clear();
}

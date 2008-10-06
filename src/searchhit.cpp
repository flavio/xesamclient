#include "searchhit.h"

using namespace Xesam::Client;

SearchHit::SearchHit(const uint& id, const QVariantList& results)
  : m_id (id),
    m_results (results)
{
}

SearchHit::~SearchHit()
{
}

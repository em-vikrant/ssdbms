/* FILE: NoteBook.cpp
 * NoteBook class implementation.
 */

#include "gui/NoteBook.h"


void
NoteBook::addPage(const std::shared_ptr<Page> page) {
    m_pageMap.emplace(page, true);
}

void
NoteBook::addPage(const std::string& title) {
    m_pageMap.emplace(
            std::make_shared<Page>(title),
            true);
}

std::vector<std::weak_ptr<Page>>
NoteBook::getPages() {
    std::vector<std::weak_ptr<Page>> pageVec;
    for (const auto& [key, value] : m_pageMap) {
        pageVec.push_back(key);
    }
    return pageVec;
}

void
NoteBook::removePage(const std::weak_ptr<Page>& pPage) {
    if (!pPage.expired()) {
        std::shared_ptr<Page> spPage = pPage.lock();
        std::map<std::shared_ptr<Page>, bool>::const_iterator itr = m_pageMap.find(spPage);
        if (itr != m_pageMap.end()) {
            m_pageMap.erase(itr);
        }
    }
}



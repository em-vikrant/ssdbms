/* FILE: NoteBook.h
 * Header file for the NoteBook class.
 */

#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "logger.h"
#include "gui/Page.h"


class NoteBook {
    public:
        NoteBook() {}

        void addPage(const std::shared_ptr<Page> page);
        void addPage(const std::string& title);
        std::vector<std::weak_ptr<Page>> getPages();
        void removePage(const std::weak_ptr<Page>& pPage);

    private:
        std::map<std::shared_ptr<Page>, bool> m_pageMap;

        NoteBook(const NoteBook&) = delete;
        NoteBook operator=(const NoteBook&) = delete;
};

#endif

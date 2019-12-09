/*
 * Copyright 2019 Xavier Hosxe
 *
 * Author: Xavier Hosxe (xavier <dot> hosxe
 *                      (at) g m a i l <dot> com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ListProperty.h"



ListProperty::ListProperty(String listName, String suffix, NameAndId* initList) {

    PropertiesFile::Options options;
#if JUCE_MAC
    options.commonToAllUsers = false;
#else
    options.commonToAllUsers = true;
#endif
    options.applicationName = ProjectInfo::projectName;
    options.osxLibrarySubFolder = "Application Support/Ixox";
    options.filenameSuffix = suffix;
    options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
    options.doNotSave = true;
    PropertiesFile pfm2FilterListTest(options);
    if (!pfm2FilterListTest.getFile().exists()) {
        // we must create it !
        options.doNotSave = false;
        PropertiesFile pfm2FilterListInit(options);
        XmlElement allFiltersElem(listName);
        XmlElement* filterElem[NUMBER_MAX_OF_FILTER];
        int f = 0;
        while (initList[f].name != "") {
            filterElem[f] = new XmlElement("item");
            filterElem[f]->setAttribute("id", initList[f].id);
            filterElem[f]->setAttribute("name", initList[f].name);
            allFiltersElem.addChildElement(filterElem[f]);
            f++;
        }
        pfm2FilterListInit.setValue(listName, &allFiltersElem);
        if (pfm2FilterListInit.save()) {
            DBG("File saved: " + pfm2FilterListInit.getFile().getFullPathName());
        }
        else {
            DBG("ERROR: " + pfm2FilterListInit.getFile().getFullPathName());
        }
        f = 0;
    }

    // We initialize the filter list by reading the file
    options.doNotSave = true;
    PropertiesFile pfm2FilterList(options);
    DBG("Reading: " + pfm2FilterList.getFile().getFullPathName());
    for (int i = 0; i < NUMBER_MAX_OF_FILTER; i++) {
        myItems[i].name = "";
        myItems[i].id = 0;
    }
    if (pfm2FilterList.getFile().exists()) {
        std::unique_ptr<XmlElement > filtersValue = pfm2FilterList.getXmlValue(listName);
        int e = 0;
        XmlElement* filter;
        while ((filter = filtersValue->getChildElement(e)) != nullptr) {
            myItems[e].name = String(filter->getStringAttribute("name"));
            myItems[e].id = filter->getIntAttribute("id");
            e++;
        }
    }
    else {
        myItems[0].name = "ERROR Loading " + listName;
    }

}

NameAndId* ListProperty::getList() {
    return myItems;
}

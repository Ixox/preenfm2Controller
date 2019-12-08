/*
 * Copyright 2018 Xavier Hosxe
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

#ifndef LISTPROPERTY_H_INCLUDED
#define LISTPROPERTY_H_INCLUDED

#include "JuceHeader.h"

#define NUMBER_MAX_OF_FILTER 100

struct NameAndId {
    String name;
    int  id;
};

class ListProperty
{
public:
    ListProperty(String listName, String suffix, NameAndId* initList);
    NameAndId* ListProperty::getList();

private:
    NameAndId myItems[NUMBER_MAX_OF_FILTER];
};

#endif

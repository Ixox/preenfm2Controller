/*
 * Copyright 2014 Xavier Hosxe
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


#ifndef ENVELOPPEFREE2_H_INCLUDED
#define ENVELOPPEFREE2_H_INCLUDED


#include "JuceHeader.h"
#include "EnveloppeAbstract.h"
//==============================================================================
/*
*/
class EnveloppeFree2    : public  EnveloppeAbstract, public ComboBox::Listener
{
public:
    EnveloppeFree2(int nrpnBase);
    ~EnveloppeFree2();
    void resized();
    void paint (Graphics&);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    // Must be implemented to deal with point value modification
    void newXValue(int draggingPointIndex, float newX);
    const char ** getPointSuffix() const;
    const char *getPointSuffix(int pointNumber, bool isX) const;

private:

    int nrpnBase;
    EnveloppePoint* decayPoint;
    EnveloppePoint* sustainPoint;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnveloppeFree2)

};


#endif  // ENVELOPPEFREE2_H_INCLUDED

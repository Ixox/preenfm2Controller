/*
  ==============================================================================

    PanelOfParameters.cpp
    Created: 27 Apr 2014 6:10:17pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef PANELOFPARAMETERS_CPP_INCLUDED
#define PANELOFPARAMETERS_CPP_INCLUDED

#include "JuceHeader.h"
#include "../PluginParameters/include/PluginParameters.h"

class PanelOfParameters :public teragon::ParameterObserver
{
public:

    void setParameterSet(teragon::ConcurrentParameterSet& parameterSet) {
        this->parameterSet = &parameterSet;
    }

    virtual void buildParameters() = 0;

    void addSliderParameter(Slider* slider) {
        teragon::ParameterString pString = teragon::Parameter::makeSafeName(slider->getName().toRawUTF8());
        teragon::Parameter* newParam = new teragon::FloatParameter(pString, slider->getMinimum(), slider->getMaximum(), slider->getValue());
        parameterSet->add(newParam);
        componentMap.insert(std::pair<teragon::ParameterString ,Component *>(pString , slider));
        parameterMap.insert(std::pair<String ,teragon::Parameter *>(slider->getName() , newParam));
        // And last...
        newParam->addObserver(this);
    }

    void addComboBoxParameter(ComboBox* comboBox) {
        teragon::ParameterString pString = teragon::Parameter::makeSafeName(comboBox->getName().toRawUTF8());
        teragon::Parameter* newParam = new teragon::IntegerParameter(pString, 1, comboBox->getNumItems(), comboBox->getSelectedId());
        parameterSet->add(newParam);
        componentMap.insert(std::pair<teragon::ParameterString ,Component *>(pString , comboBox));
        parameterMap.insert(std::pair<String ,teragon::Parameter *>(comboBox->getName() , newParam));
        // And last...
        newParam->addObserver(this);
    }

    // parameter observer
    bool isRealtimePriority() const { return false; }

    // The following one mus be implemented by the panel itself
    //    void onParameterUpdated(const teragon::Parameter *parameter);

protected:
    std::map<teragon::ParameterString, Component *> componentMap;
    std::map<String, teragon::Parameter *> parameterMap;
    teragon::ConcurrentParameterSet* parameterSet;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

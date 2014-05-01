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

class PanelOfParameters
{
public:

	~PanelOfParameters() {
	}


    void setParameterSet(teragon::ConcurrentParameterSet& parameterSet) {
        this->parameterSet = &parameterSet;
		panelParameterMap.clear();
    }

    virtual void buildParameters() = 0;

    void addSliderParameter(Slider* slider) {
        teragon::ParameterString pString = slider->getName().toRawUTF8();
		teragon::Parameter* paramToMap =  parameterSet->get(pString);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (paramToMap == nullptr) {
			printf("WHAT %s does not exist...\r\n", pString.c_str());
			return;
		}
/*
		if (componentMap[pString] == nullptr) {
			componentMap.insert(std::pair<teragon::ParameterString ,Component *>(pString , slider));
		}
		*/
		if (panelParameterMap[slider->getName()] == nullptr) {
			panelParameterMap.set(slider->getName() ,paramToMap);
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		slider->setValue(paramToMap->getValue(), dontSendNotification);
	}

    void addComboBoxParameter(ComboBox* comboBox) {
        teragon::ParameterString pString = comboBox->getName().toRawUTF8();
        teragon::Parameter* newParam = new teragon::IntegerParameter(pString, 1, comboBox->getNumItems(), comboBox->getSelectedId());
        parameterSet->add(newParam);
        //componentMap.insert(std::pair<teragon::ParameterString ,Component *>(pString , comboBox));
        panelParameterMap.set(comboBox->getName() , newParam);
    }

protected:
//    std::map<teragon::ParameterString, Component *> componentMap;
    HashMap<String, teragon::Parameter *> panelParameterMap;
    teragon::ConcurrentParameterSet* parameterSet;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

/*
  ==============================================================================

    PanelOfParameters.cpp
    Created: 27 Apr 2014 6:10:17pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef PANELOFPARAMETERS_CPP_INCLUDED
#define PANELOFPARAMETERS_CPP_INCLUDED

#include <unordered_set>
#include "JuceHeader.h"
#include "../PluginParameters/include/PluginParameters.h"
#include "EnveloppeAbstract.h"
#include "EnveloppeListener.h"

class PanelOfParameters : public EnveloppeListener
{
public:
	~PanelOfParameters() {
	}


    void setParameterSet(teragon::ConcurrentParameterSet& parameterSet) {
        this->parameterSet = &parameterSet;
		panelParameterMap.clear();
    }

    virtual void buildParameters() = 0;

    void updateSliderParameter(Slider* slider) {
        teragon::ParameterString pString = slider->getName().toRawUTF8();
		teragon::Parameter* paramToMap =  parameterSet->get(pString);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (paramToMap == nullptr) {
			printf("Slider %s does not exist...\r\n", pString.c_str());
			return;
		}

		if (componentMap[pString.c_str()] == nullptr) {
			componentMap.set(String(pString.c_str()) , slider);
		}

		if (panelParameterMap[slider->getName()] == nullptr) {
			panelParameterMap.set(slider->getName() ,paramToMap);
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
        slider->setValue(paramToMap->getValue(), dontSendNotification);
        updateSliderParameter_hook(slider);
	}

    // Can be overriden by sub classes
    virtual void updateSliderParameter_hook(Slider* slider) { }

    void updateComboParameter(ComboBox* combo) {
        teragon::ParameterString pString = combo->getName().toRawUTF8();
		teragon::Parameter* paramToMap =  parameterSet->get(pString);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (paramToMap == nullptr) {
			printf("Combo box %s does not exist...\r\n", pString.c_str());
			return;
		}

		if (componentMap[pString.c_str()] == nullptr) {
			componentMap.set(String(pString.c_str()) , combo);
		}

		if (panelParameterMap[combo->getName()] == nullptr) {
			panelParameterMap.set(combo->getName() ,paramToMap);
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		if (combo->getSelectedId() != paramToMap->getValue()) {
			combo->setSelectedId(paramToMap->getValue(), dontSendNotification);
			updateComboParameter_hook(combo);
		}
	}

    // Can be overriden by sub classes
    virtual void updateComboParameter_hook(ComboBox* combo) { }

    // Enveloppe Listener
    void enveloppeValueChanged(const EnveloppeAbstract* enveloppeThatWasMoved, int pointNumber, bool isX)
    {
    	enveloppeValueChanged(enveloppeThatWasMoved, pointNumber, isX, true);
    }

    void enveloppeValueChanged(const EnveloppeAbstract* enveloppeThatWasMoved, int pointNumber, bool isX, bool fromPluginUI)
    {
        // Update the value if the change comes from the UI
        if (fromPluginUI) {
        	const char* suffix = enveloppeThatWasMoved->getPointSuffix()[(pointNumber - 1) *2 + (isX ? 0 : 1)];
    		teragon::Parameter * parameterReady = panelParameterMap[enveloppeThatWasMoved->getName() + suffix];
            if (parameterReady != nullptr) {
                teragon::ParameterValue value;
                if (isX) {
                	value = enveloppeThatWasMoved->getX(pointNumber);
                } else {
                	value = enveloppeThatWasMoved->getY(pointNumber);
                }
                printf("PanelOfParameter::enveloppeValueChanged %s : %f \r\n", parameterReady->getName().c_str(), value);
                parameterSet->set(parameterReady, value, nullptr);
            } else {
                printf("PanelOfParameter::enveloppeValueChanged %s name does not EXIST \r\n", String(enveloppeThatWasMoved->getName() + suffix).toRawUTF8());
            }
        }
    }

    void updateUI(std::unordered_set<const char*> &paramSet) {
    	for(std::unordered_set<const char*>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
    		Component* component = componentMap[String(*it)];

    		Slider* slider = dynamic_cast<Slider*>(component);
    		if (slider != nullptr) {
    			updateSliderParameter(slider);
    			return;
    		}

    		ComboBox* combo = dynamic_cast<ComboBox*>(component);
    		if (combo != nullptr) {
    			updateComboParameter(combo);
    			return;
    		}
    	}
    }


protected:
//    std::map<teragon::ParameterString, Component *> componentMap;
    HashMap<const String, teragon::Parameter *> panelParameterMap;
    HashMap<const String, Component*> componentMap;
    teragon::ConcurrentParameterSet* parameterSet;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

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

    void addSliderParameter(Slider* slider) {
        teragon::ParameterString pString = slider->getName().toRawUTF8();
		teragon::Parameter* paramToMap =  parameterSet->get(pString);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (paramToMap == nullptr) {
			printf("Slider %s does not exist...\r\n", pString.c_str());
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

		addSliderParameter_hook(slider);
	}

    // Can be overriden by sub classes
    virtual void addSliderParameter_hook(Slider* slider) { }

    void addComboParameter(ComboBox* combo) {
        teragon::ParameterString pString = combo->getName().toRawUTF8();
		teragon::Parameter* paramToMap =  parameterSet->get(pString);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (paramToMap == nullptr) {
			printf("Combo box %s does not exist...\r\n", pString.c_str());
			return;
		}
		if (panelParameterMap[combo->getName()] == nullptr) {
			panelParameterMap.set(combo->getName() ,paramToMap);
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		combo->setSelectedId(paramToMap->getValue(), dontSendNotification);

		addComboParameter_hook(combo);
	}

    // Can be overriden by sub classes
    virtual void addComboParameter_hook(ComboBox* combo) { }


    void addComboBoxParameter(ComboBox* comboBox) {
        teragon::ParameterString pString = comboBox->getName().toRawUTF8();
        teragon::Parameter* newParam = new teragon::IntegerParameter(pString, 1, comboBox->getNumItems(), comboBox->getSelectedId());
        parameterSet->add(newParam);
        //componentMap.insert(std::pair<teragon::ParameterString ,Component *>(pString , comboBox));
        panelParameterMap.set(comboBox->getName() , newParam);
    }

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


protected:
//    std::map<teragon::ParameterString, Component *> componentMap;
    HashMap<const String, teragon::Parameter *> panelParameterMap;
    teragon::ConcurrentParameterSet* parameterSet;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

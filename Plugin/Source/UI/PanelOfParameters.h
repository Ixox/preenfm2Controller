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
#include "StepSequencer.h"
#include "StepSequencerListener.h"

class PanelOfParameters : public EnveloppeListener, public StepSequencerListener
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

    void updateStepSeqParameter(StepSequencer* stepSeq) {

        for (int k=0; k<16; k++) {
            teragon::ParameterString pString = String(String(stepSeq->getName().toRawUTF8()) + " Step " + String(k+1)).toRawUTF8();
            String paramName = String(pString.c_str());
            teragon::Parameter* paramToMap =  parameterSet->get(pString );

            // Will remove that later but dont' BUG for the moment if that doesn't fit
            if (paramToMap == nullptr) {
                printf("step sequencer %s does not exist...\r\n", pString.c_str());
                return;
            }

            if (panelParameterMap[paramName] == nullptr) {
                panelParameterMap.set(paramName ,paramToMap);
                printf("updateStepSeqParameter added : '%s' to panelParameterMap \r\n", paramName.toRawUTF8());
            }

            // And let's update the value and update the UI Without sending modification !!!
            // No modification : we dont want sliderValueChanged to be called in the different panels
            if (stepSeq->getValue(k) != paramToMap->getValue()) {
                stepSeq->setValues(k, paramToMap->getValue());
            }
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
        	const char* suffix = enveloppeThatWasMoved->getPointSuffix(pointNumber, isX);
    		teragon::Parameter * parameterReady = panelParameterMap[enveloppeThatWasMoved->getName() + suffix];
            if (parameterReady != nullptr) {
                teragon::ParameterValue value;
                if (isX) {
                	value = enveloppeThatWasMoved->getX(pointNumber);
                } else {
                	value = enveloppeThatWasMoved->getY(pointNumber);
                }
                printf("PanelOfParameter::enveloppeValueChanged '%s' : %f \r\n", parameterReady->getName().c_str(), value);
                parameterSet->set(parameterReady, value, nullptr);
            } else {
                printf("PanelOfParameter::enveloppeValueChanged '%s' name does not EXIST \r\n", String(enveloppeThatWasMoved->getName() + suffix).toRawUTF8());
            }
        }
    }

    void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber) {
        stepSeqSequencerChanged(stepSeqThatChanged, stepNumber, true);
    }

    void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber, bool fromPluginUI) {
        // Update the value if the change comes from the UI
        if (fromPluginUI) {
            teragon::Parameter * parameterReady = panelParameterMap[stepSeqThatChanged->getName()+" Step "+ String(stepNumber +1)];
            if (parameterReady != nullptr) {
                teragon::ParameterValue value;
                value = stepSeqThatChanged->getValue(stepNumber);
                printf("PanelOfParameter::stepSeqSequencerChanged %s : %f \r\n", parameterReady->getName().c_str(), value);
                parameterSet->set(parameterReady, value, nullptr);
            } else {
                printf("PanelOfParameter::stepSeqSequencerChanged %s name does not EXIST \r\n", String(stepSeqThatChanged->getName() + " Step"+ String(stepNumber + 1)).toRawUTF8());
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

            StepSequencer* stepSeq = dynamic_cast<StepSequencer*>(component);
            if (stepSeq != nullptr) {
                updateStepSeqParameter(stepSeq);
                return;
            }

            printf("PanelOfParameters::component %s \r\n", (*it));

            if (String(*it).startsWith("Step Seq")) {
                updateUIStepSequencer(*it);
                return;
            }

    		printf("Can be an eveloppe : %s\r\n", (*it));
    		updateUIEnveloppe((*it));
    	}
    }

    virtual void updateUIEnveloppe(const char* paramName) { }
    virtual void updateUIStepSequencer(const char* paramName) {
        printf("PanelOfParameters::updateUIStepSequencer (NOT IMPLEMENTER): %s\r\n", paramName);

    }


protected:
//    std::map<teragon::ParameterString, Component *> componentMap;
    HashMap<const String, teragon::Parameter *> panelParameterMap;
    HashMap<const String, Component*> componentMap;
    teragon::ConcurrentParameterSet* parameterSet;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

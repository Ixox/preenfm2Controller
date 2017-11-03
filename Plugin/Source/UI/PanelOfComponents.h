/*
 * Copyright 2017 Xavier Hosxe
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


#ifndef PANELOFPARAMETERS_CPP_INCLUDED
#define PANELOFPARAMETERS_CPP_INCLUDED

#include <unordered_set>
#include "JuceHeader.h"
#include "EnveloppeAbstract.h"
#include "EnveloppeListener.h"
#include "StepSequencer.h"
#include "StepSequencerListener.h"
#include "../MidifiedFloatParameter.h"

class PanelOfComponents : public EnveloppeListener, 
						  public StepSequencerListener,
						  public Slider::Listener

{
public:
	~PanelOfComponents() {
	}


    void setParameterSet(AudioProcessor* audioProcessor) {
        this->audioProcessor = audioProcessor;
		parameterMap.clear();
    }

    virtual void buildParameters() = 0;

    void updateSliderFromParameter(Slider* slider) {

		String componentName = slider->getName();
		if (componentMap[componentName] == nullptr) {
			componentMap.set(componentName, slider);
		}

		MidifiedFloatParameter * parameter = checkParamExistence(componentName);

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
        slider->setValue(parameter->getRealValue(), dontSendNotification);

		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (parameter == nullptr) {
			return ;
		}

        updateSliderFromParameter_hook(slider);
	}

	MidifiedFloatParameter* checkParamExistence(String componentName) {

		MidifiedFloatParameter* parameter = parameterMap[componentName];
		if (parameter == nullptr) {
			const OwnedArray<AudioProcessorParameter>& parameters = audioProcessor->getParameters();
			for (int p = 0; p < parameters.size(); p++) {
				if (parameters[p]->getName(256) == componentName) {
					parameter = (MidifiedFloatParameter*)parameters[p];
					parameterMap.set(componentName, parameter);
				}
			}
		}
		return parameter;
	}

    // Can be overriden by sub classes
    virtual void updateSliderFromParameter_hook(Slider* slider) { }

    void updateComboFromParameter(ComboBox* combo) {

		String componentName = combo->getName();
		if (componentMap[componentName] == nullptr) {
			componentMap.set(componentName, combo);
		}

		MidifiedFloatParameter * parameter = checkParamExistence(componentName);

		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (parameter == nullptr) {
			return;
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		if (combo->getSelectedId() != parameter->getRealValue()) {
			combo->setSelectedId(parameter->getRealValue() + .0001f, dontSendNotification);
			updateComboFromParameter_hook(combo);
		}
    }

    void updateStepSeqParameter(StepSequencer* stepSeq) {

        for (int k=0; k<16; k++) {

            String stepName = String(String(stepSeq->getName().toRawUTF8()) + " Step " + String(k+1)).toRawUTF8();
			MidifiedFloatParameter * parameter = checkParamExistence(stepName);


            // Will remove that later but dont' BUG for the moment if that doesn't fit
            if (parameter == nullptr) {
                return;
            }

            // And let's update the value and update the UI Without sending modification !!!
            // No modification : we dont want sliderValueChanged to be called in the different panels
            if (stepSeq->getValue(k) != parameter->getRealValue()) {
                stepSeq->setValues(k, parameter->getRealValue());
            }
        }
    }

    // Can be overriden by sub classes
    virtual void updateComboFromParameter_hook(ComboBox* combo) { }


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
			MidifiedFloatParameter * parameterReady = parameterMap[enveloppeThatWasMoved->getName() + suffix];
            if (parameterReady != nullptr) {
                float value;
                if (isX) {
                	value = enveloppeThatWasMoved->getX(pointNumber);
                } else {
                	value = enveloppeThatWasMoved->getY(pointNumber);
                }
				parameterReady->setRealValue(value);
			}
        }
    }

    void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber) {
        stepSeqSequencerChanged(stepSeqThatChanged, stepNumber, true);
    }

    void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber, bool fromPluginUI) {
        // Update the value if the change comes from the UI
        if (fromPluginUI) {
			MidifiedFloatParameter * parameterReady = parameterMap[stepSeqThatChanged->getName()+" Step "+ String(stepNumber +1)];
            if (parameterReady != nullptr) {
                int value;
                value = stepSeqThatChanged->getValue(stepNumber);
				parameterReady->setRealValue(value);
            }
        }
    }

    void updateUI(std::unordered_set<String> &paramSet) {
    	for(std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
    		Component* component = componentMap[*it];

            if (component == nullptr) {
                if ((*it).startsWith("Step Seq")) {
                    updateUIStepSequencer(*it);
                    continue;
                } else {
                    updateUIEnveloppe((*it));
                }
			}

    		Slider* slider = dynamic_cast<Slider*>(component);
    		if (slider != nullptr) {
    			updateSliderFromParameter(slider);
                continue;
    		}

    		ComboBox* combo = dynamic_cast<ComboBox*>(component);
    		if (combo != nullptr) {
    			updateComboFromParameter(combo);
                continue;
    		}
    	}
    }

    virtual void updateUIEnveloppe(String paramName) { }
    virtual void updateUIStepSequencer(String paramName) {
    }


	void sliderDragStarted(Slider* slider)	override {
		AudioProcessorParameter * param = parameterMap[slider->getName()];
		if (param != nullptr) {
			param->beginChangeGesture();
		}
	}
	void sliderDragEnded(Slider* slider) override {
		AudioProcessorParameter * param = parameterMap[slider->getName()];
		if (param != nullptr) {
			param->endChangeGesture();
		}
	}

protected:
    HashMap<const String, MidifiedFloatParameter *> parameterMap;
    HashMap<const String, Component*> componentMap;
	AudioProcessor* audioProcessor;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

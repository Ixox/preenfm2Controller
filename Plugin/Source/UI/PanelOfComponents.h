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

#define TYPE_NOT_HERE  0
#define TYPE_COMBO     1
#define TYPE_SLIDER    2
#define TYPE_STEP_SEQ  3
#define TYPE_ENVELOPPE 4

#define TYPE_PREENFM2 1
#define TYPE_PREENFM3 2

class PanelOfComponents : public EnveloppeListener,
	public StepSequencerListener

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
			return;
		}

		updateSliderFromParameter_hook(slider);
	}

	MidifiedFloatParameter* checkParamExistence(String componentName) {

		MidifiedFloatParameter* parameter = parameterMap[componentName];
		if (parameter == nullptr) {
			Array<AudioProcessorParameter*> parameters = audioProcessor->getParameters();
			for (int p = 0; p < parameters.size(); p++) {
				parameter = (MidifiedFloatParameter*)parameters[p];
				if (parameter->getName() == componentName) {
					parameterMap.set(componentName, parameter);
					break;
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
			combo->setSelectedId((int)(parameter->getRealValue() + .0001f), dontSendNotification);
			updateComboFromParameter_hook(combo);
		}
	}

	void updateStepSeqParameter(StepSequencer* stepSeq) {

		for (int k = 0; k < 16; k++) {

			String stepName = String(String(stepSeq->getName().toRawUTF8()) + " Step " + String(k + 1)).toRawUTF8();
			MidifiedFloatParameter * parameter = checkParamExistence(stepName);

			// Will remove that later but dont' BUG for the moment if that doesn't fit
			if (parameter == nullptr) {
				return;
			}

			// And let's update the value and update the UI Without sending modification !!!
			// No modification : we dont want sliderValueChanged to be called in the different panels
			if (stepSeq->getValue(k) != parameter->getRealValue()) {
				stepSeq->setValuesNoNotify(k, (int)parameter->getRealValue());
			}
		}
		stepSeq->repaint();
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
				double value;
				if (isX) {
					value = enveloppeThatWasMoved->getX(pointNumber);
				}
				else {
					value = enveloppeThatWasMoved->getY(pointNumber);
				}
				parameterReady->setRealValue((float)value);
			}
		}
	}

	void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber) {
		stepSeqSequencerChanged(stepSeqThatChanged, stepNumber, true);
	}

	void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber, bool fromPluginUI) {
		// Update the value if the change comes from the UI
		if (fromPluginUI) {
			MidifiedFloatParameter * parameterReady = parameterMap[stepSeqThatChanged->getName() + " Step " + String(stepNumber + 1)];
			if (parameterReady != nullptr) {
				int value = stepSeqThatChanged->getValue(stepNumber);
				parameterReady->setRealValue((float)value);
			}
		}
	}

	void updateUI(std::unordered_set<String> &paramSet) {
		for (std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end();) {
			String name = *it;

			if (!componentType.contains(name)) {
				Component* component = componentMap[name];
				Slider* slider = dynamic_cast<Slider*>(component);
				ComboBox* combo = dynamic_cast<ComboBox*>(component);
				if (slider != nullptr) {
					componentType.set(*it, TYPE_SLIDER);
				}
				else if (combo != nullptr) {
					componentType.set(*it, TYPE_COMBO);
				}
				else if (containsThisParameterAsStepSequencer(name)) {
					componentType.set(*it, TYPE_STEP_SEQ);
				}
				else if (containsThisParameterAsEnveloppe(name)) {
					componentType.set(*it, TYPE_ENVELOPPE);
				}
				else {
					componentType.set(*it, TYPE_NOT_HERE);
				}
			}

			int otherType = componentType[name];
			switch (otherType) {
			case TYPE_SLIDER: {
				Component* component = componentMap[name];
				Slider* slider = dynamic_cast<Slider*>(component);
				updateSliderFromParameter(slider);
				it = paramSet.erase(it);
				break;
			}
			case TYPE_COMBO: {
				Component* component = componentMap[name];
				ComboBox* combo = dynamic_cast<ComboBox*>(component);
				updateComboFromParameter(combo);
				it = paramSet.erase(it);
				continue;
				break;
			}
			case TYPE_STEP_SEQ:
				updateUIStepSequencer(name);
				it = paramSet.erase(it);
				break;
			case TYPE_ENVELOPPE:
				updateUIEnveloppe(name);
				it = paramSet.erase(it);
				break;
			case TYPE_NOT_HERE:
				// Look next
				++it;
				break;
			}

		}
	}
	virtual bool containsThisParameterAsEnveloppe(String paramName) { return false; }
	virtual bool containsThisParameterAsStepSequencer(String paramName) { return false; }
	virtual void updateUIEnveloppe(String paramName) {
	}
	virtual void updateUIStepSequencer(String paramName) {
	}

	virtual void setPfmType(int type) {
		pfmType = type;
	}

protected:
	HashMap<const String, MidifiedFloatParameter *> parameterMap;
	HashMap<const String, Component*> componentMap;
	HashMap<const String, int> componentType;
	AudioProcessor* audioProcessor;
	int pfmType;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED

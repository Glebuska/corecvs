/**
 * \file outputFilterParametersControlWidget.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include "outputFilterParametersControlWidget.h"
#include "ui_outputFilterParametersControlWidget.h"
#include "qSettingsGetter.h"
#include "qSettingsSetter.h"


OutputFilterParametersControlWidget::OutputFilterParametersControlWidget(QWidget *parent, bool _autoInit, QString _rootPath)
    : FilterParametersControlWidgetBase(parent)
    , mUi(new Ui::OutputFilterParametersControlWidget)
    , autoInit(_autoInit)
    , rootPath(_rootPath)
{
    mUi->setupUi(this);

    QObject::connect(mUi->outputTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
}

OutputFilterParametersControlWidget::~OutputFilterParametersControlWidget()
{

    delete mUi;
}

void OutputFilterParametersControlWidget::loadParamWidget(WidgetLoader &loader)
{
    OutputFilterParameters *params = createParameters();
    loader.loadParameters(*params, rootPath);
    setParameters(*params);
    delete params;
}

void OutputFilterParametersControlWidget::saveParamWidget(WidgetSaver  &saver)
{
    OutputFilterParameters *params = createParameters();
    saver.saveParameters(*params, rootPath);
    delete params;
}

 /* Composite fields are NOT supported so far */
void OutputFilterParametersControlWidget::getParameters(OutputFilterParameters& params) const
{

    params.setOutputType       (static_cast<OutputType::OutputType>(mUi->outputTypeComboBox->currentIndex()));

}

OutputFilterParameters *OutputFilterParametersControlWidget::createParameters() const
{

    /**
     * We should think of returning parameters by value or saving them in a preallocated place
     **/


    OutputFilterParameters *result = new OutputFilterParameters(
          static_cast<OutputType::OutputType>(mUi->outputTypeComboBox->currentIndex())
    );
    return result;
}

void OutputFilterParametersControlWidget::setParameters(const OutputFilterParameters &input)
{
    // Block signals to send them all at once
    bool wasBlocked = blockSignals(true);
    mUi->outputTypeComboBox->setCurrentIndex(input.outputType());
    blockSignals(wasBlocked);
    emit paramsChanged();
}

void OutputFilterParametersControlWidget::setParametersVirtual(void *input)
{
    // Modify widget parameters from outside
    OutputFilterParameters *inputCasted = static_cast<OutputFilterParameters *>(input);
    setParameters(*inputCasted);
}

/**
 * \file parametersMapperCopter.cpp
 * \attention This file is automatically generated and should not be in general modifed manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include "parametersMapperCopter.h"

ParametersMapperCopter::ParametersMapperCopter() :
    mBaseParametersControlWidget(NULL)
  , mCopterControlWidget(NULL)
  , mPresentationParametersControlWidget(NULL)
{
    qRegisterMetaType<QSharedPointer<BaseParameters> >("QSharedPointer<BaseParameters>");
    qRegisterMetaType<QSharedPointer<Copter> >("QSharedPointer<Copter>");
    qRegisterMetaType<QSharedPointer<PresentationParameters> >("QSharedPointer<PresentationParameters>");
}

void ParametersMapperCopter::setBaseParametersControlWidget(BaseParametersControlWidget *widget)
{
    mBaseParametersControlWidget = widget;
    QObject::connect(mBaseParametersControlWidget, SIGNAL(paramsChanged()), this, SLOT(paramsChanged()));
}

void ParametersMapperCopter::setCopterControlWidget(CopterControlWidget *widget)
{
    mCopterControlWidget = widget;
    QObject::connect(mCopterControlWidget, SIGNAL(paramsChanged()), this, SLOT(paramsChanged()));
}

void ParametersMapperCopter::setPresentationParametersControlWidget(PresentationParametersControlWidget *widget)
{
    mPresentationParametersControlWidget = widget;
    QObject::connect(mPresentationParametersControlWidget, SIGNAL(paramsChanged()), this, SLOT(paramsChanged()));
}

void ParametersMapperCopter::paramsChanged()
{
    if (mBaseParametersControlWidget == NULL)
    {
          std::cout << "One of the fields for ParametersMapperCopter \n"
               "is still NULL but the mapper is already in use. This will cause crash.\n"
               "You should modify your <HostWidget>::createCalculator() function" << std::endl;
    }
    emit baseParametersParamsChanged(QSharedPointer<BaseParameters>(mBaseParametersControlWidget->createParameters()));


    if (mCopterControlWidget == NULL)
    {
          std::cout << "One of the fields for ParametersMapperCopter \n"
               "is still NULL but the mapper is already in use. This will cause crash.\n"
               "You should modify your <HostWidget>::createCalculator() function" << std::endl;
    }
    emit copterParamsChanged(QSharedPointer<Copter>(mCopterControlWidget->createParameters()));


    if (mPresentationParametersControlWidget == NULL)
    {
          std::cout << "One of the fields for ParametersMapperCopter \n"
               "is still NULL but the mapper is already in use. This will cause crash.\n"
               "You should modify your <HostWidget>::createCalculator() function" << std::endl;
    }
    emit presentationParametersParamsChanged(QSharedPointer<PresentationParameters>(mPresentationParametersControlWidget->createParameters()));


}


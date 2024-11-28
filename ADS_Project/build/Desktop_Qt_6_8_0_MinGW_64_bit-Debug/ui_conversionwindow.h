/********************************************************************************
** Form generated from reading UI file 'conversionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERSIONWINDOW_H
#define UI_CONVERSIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ConversionWindow
{
public:

    void setupUi(QDialog *ConversionWindow)
    {
        if (ConversionWindow->objectName().isEmpty())
            ConversionWindow->setObjectName("ConversionWindow");
        ConversionWindow->resize(400, 300);

        retranslateUi(ConversionWindow);

        QMetaObject::connectSlotsByName(ConversionWindow);
    } // setupUi

    void retranslateUi(QDialog *ConversionWindow)
    {
        ConversionWindow->setWindowTitle(QCoreApplication::translate("ConversionWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConversionWindow: public Ui_ConversionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERSIONWINDOW_H

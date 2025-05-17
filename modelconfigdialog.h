#ifndef MODELCONFIGDIALOG_H
#define MODELCONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "persistencemanager.h"

class ModelConfigDialog : public QDialog
{
    Q_OBJECT
    QLineEdit mModelEditorText;
    QLabel mModelLabel;
    QPushButton mSaveButton;
    QLabel mApiKeyLabel;
    QLineEdit mApiKeyEditorText;
    ModelConfig mModelConfig;

public:
    ModelConfigDialog(QWidget *parent, const ModelConfig &modelConfig);
    void onSaveClicked();

signals:
    void modelChanged(const QString &model);
    void apiKeyChanged(const QString &apiKey);
};

#endif // MODELCONFIGDIALOG_H

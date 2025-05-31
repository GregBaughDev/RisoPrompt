#ifndef MODELCONFIGDIALOG_H
#define MODELCONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "persistencemanager.h"

class ModelConfigDialog : public QDialog
{
    Q_OBJECT
    QLabel mModelLabel;
    QPushButton mSaveButton;
    QLabel mApiKeyLabel;
    QLineEdit mApiKeyEditorText;
    QComboBox mComboBox;
    ModelConfig mModelConfig;
    QStringList mAvailableModels;

public:
    ModelConfigDialog(QWidget *parent, const ModelConfig &modelConfig, QVector<QString> availableModels);
    void onSaveClicked();

signals:
    void modelChanged(const QString &model);
    void apiKeyChanged(const QString &apiKey);
};

#endif // MODELCONFIGDIALOG_H

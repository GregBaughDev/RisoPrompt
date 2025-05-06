#ifndef MODELCONFIGDIALOG_H
#define MODELCONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class ModelConfigDialog : public QDialog
{
    Q_OBJECT
    QLineEdit m_modelEditorText;
    QLabel m_modelLabel;
    QPushButton m_saveButton;
    QString m_promptModel;
    QLabel m_apiKeyLabel;
    QString m_apiKey;
    QLineEdit m_apiKeyEditorText;

public:
    ModelConfigDialog(QWidget *parent, const QString promptModel, const QString apiKey);
    void onSaveClicked();

signals:
    void modelChanged(const QString &model);
    void apiKeyChanged(const QString &apiKey);
};

#endif // MODELCONFIGDIALOG_H

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
    QLabel m_label;
    QPushButton m_saveButton;
    QString m_promptModel;

public:
    ModelConfigDialog(QWidget *parent, const QString promptModel);
    void onSaveClicked();

signals:
    void modelChanged(const QString &model);
};

#endif // MODELCONFIGDIALOG_H

#ifndef RISOPROMPT_H
#define RISOPROMPT_H

#include <QMainWindow>
#include "promptrequest.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class RisoPrompt;
}
QT_END_NAMESPACE

class RisoPrompt : public QMainWindow
{
    Q_OBJECT
    Ui::RisoPrompt *ui;
    PromptRequest promptRequest;
    QString m_promptModel;

public:
    RisoPrompt(QWidget *parent = nullptr);
    ~RisoPrompt();

private slots:
    void onSaveButtonClicked();
    void onCopyButtonClicked();
    void onNewButtonClicked();
    void toggleLoading();
    void toggleTextEntry();
    void setPromptModel(const QString &promptModel);
    void onModelButtonClicked();

signals:
    void newButtonClicked();

};
#endif // RISOPROMPT_H

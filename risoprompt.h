#ifndef RISOPROMPT_H
#define RISOPROMPT_H

#include <QMainWindow>
#include "promptrequest.h"
#include "persistencemanager.h"

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
    ModelConfig m_modelConfig;
    PersistenceManager m_persistenceManager;

public:
    RisoPrompt(QWidget *parent = nullptr);
    ~RisoPrompt();

private slots:
    void onSaveButtonClicked();
    void onCopyButtonClicked();
    void onNewButtonClicked();
    void toggleLoading();
    void toggleTextEntry();
    void onModelButtonClicked();
    void onLoadButtonClicked();
    void setNewModel(const QString &model);
    void setNewApiKey(const QString &key);

signals:
    void newButtonClicked();
    void copyButtonClicked();
};
#endif // RISOPROMPT_H

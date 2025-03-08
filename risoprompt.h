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

public:
    RisoPrompt(QWidget *parent = nullptr);
    ~RisoPrompt();

private slots:
    void on_saveButton_clicked();
    void on_copyButton_clicked();
    void on_newButton_clicked();

signals:
    void newButtonClicked();

};
#endif // RISOPROMPT_H

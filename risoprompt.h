#ifndef RISOPROMPT_H
#define RISOPROMPT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class RisoPrompt;
}
QT_END_NAMESPACE

class RisoPrompt : public QMainWindow
{
    Q_OBJECT

public:
    RisoPrompt(QWidget *parent = nullptr);
    ~RisoPrompt();

private slots:
    void on_saveButton_clicked();

    void on_copyButton_clicked();

    void on_newButton_clicked();

    void handleTextSubmit(const QString &newValue);

private:
    Ui::RisoPrompt *ui;
};
#endif // RISOPROMPT_H

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(const SettingsManager &settingsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    m_settingsManager(settingsManager)
{
    ui->setupUi(this);
    setup();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    emit applytodoDirectory(ui->todolistBinPathLineEdit->text());
    this->close();
}

void SettingsDialog::setup()
{
    ui->todolistBinPathLineEdit->clear();
    ui->usersListWidget->clear();
    ui->tagsListWidget->clear();
    ui->statusesListWidget->clear();

    QString todoListBinPath = "";
    QStringList users;
    QStringList tags;
    QStringList statuses;

    try
    {
        todoListBinPath = m_settingsManager.get("General", "TodoListBinPath").toString();

        int userCount = m_settingsManager.get("Users", "Count").toInt();
        if(userCount > 0)
        {
            for(size_t i = 0; i < (size_t) userCount; i++)
            {
                QString key = QStringLiteral("User") + QString::number(i);
                QString user = m_settingsManager.get("Users", key).toString();
                users.push_back(user);
            }
        }

        int tagsCount = m_settingsManager.get("Tags", "Count").toInt();
        if(tagsCount > 0)
        {
            for(size_t i = 0; i < (size_t) tagsCount; i++)
            {
                QString key = QStringLiteral("Tag") + QString::number(i);
                QString tag = m_settingsManager.get("Tags", key).toString();
                tags.push_back(tag);
            }
        }

        int statusesCount = m_settingsManager.get("Statuses", "Count").toInt();
        if(statusesCount > 0)
        {
            for(size_t i = 0; i < (size_t) statusesCount; i++)
            {
                QString key = QStringLiteral("Status") + QString::number(i);
                QString status = m_settingsManager.get("Statuses", key).toString();
                statuses.push_back(status);
            }
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SettingsError", e.what()).exec();
    }

    ui->todolistBinPathLineEdit->setText(todoListBinPath);
    ui->usersListWidget->addItems(users);
    ui->tagsListWidget->addItems(tags);
    ui->statusesListWidget->addItems(statuses);
}
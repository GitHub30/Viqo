﻿#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

class MainWindow;

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsWindow(MainWindow* mwin, QWidget* parent = 0);
  ~SettingsWindow();
  void init();
  void getUserSessionFinished();

  void newWakuListStateSave();
  void newWakuSetIndex(QString name, QString value);
  void newWakuSet(QString name, QString value);
  void newWakuListStateLoad();

  void setSelectedCommunity(const QString& value);
  void setSelectedCategory(const QString& value);

private slots:
  void on_login_way_combo_currentIndexChanged(int index);

  void on_buttonBox_accepted();

  void on_cookiesetting_file_open_button_clicked();

  void on_get_session_clicked();

  void on_newWaku_befWakuReuse_clicked();

private:
  Ui::SettingsWindow *ui;
  MainWindow* mwin;
  void saveSettings();
  QString selectedCommunity, selectedCategory;
};

#endif // SETTINGSWINDOW_H

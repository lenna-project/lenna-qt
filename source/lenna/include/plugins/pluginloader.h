/**
    This file is part of program Lenna
    Copyright (C) 2013-2016  FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "lenna/plugins/editplugin.h"
#include "lenna/plugins/inputplugin.h"
#include "lenna/plugins/outputplugin.h"

#include <vector>

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QObject>

namespace lenna {
namespace plugin {

class PluginLoader : public QObject {
  Q_OBJECT
 public:
  ~PluginLoader();

  static void destroyInstance();
  static PluginLoader &getInstance();

  void activatePlugin(QString uid, QString name);
  void activatePlugin(std::shared_ptr<Plugin> plugin);
  void activatePlugins(QStringList list);
  void deactivatePlugin(std::shared_ptr<Plugin> plugin);
  void deactivatePlugin(int index);
  bool isActivatedPlugin(std::shared_ptr<Plugin> plugin);
  std::shared_ptr<Plugin> getPlugin(QString name);
  std::shared_ptr<Plugin> getActivePlugin(QString uid);

  // InputPlugin
  std::vector<std::shared_ptr<InputPlugin>> getInputPlugins();
  QList<std::shared_ptr<InputPlugin>> getActiveInputPlugins();
  void moveInputPlugin(std::shared_ptr<InputPlugin> plugin, int index);

  // EditPlugin
  std::vector<std::shared_ptr<EditPlugin>> getEditPlugins();
  QList<std::shared_ptr<EditPlugin>> getActiveEditPlugins();
  void moveEditPlugin(std::shared_ptr<EditPlugin> plugin, int index);

  // OutputPlugin
  std::vector<std::shared_ptr<OutputPlugin>> getOutputPlugins();
  QList<std::shared_ptr<OutputPlugin>> getActiveOutputPlugins();
  void moveOutputPlugin(std::shared_ptr<OutputPlugin> plugin, int index);

 signals:

 public slots:

 private:
  explicit PluginLoader(QObject *parent = 0);
  static PluginLoader *instance;
  void loadPlugins();
  void loadConfig();
  void saveConfig();

  QMap<QString, std::shared_ptr<Plugin>> activatedPlugins;

  // InputPlugin
  std::vector<std::shared_ptr<InputPlugin>> inputPlugins;
  QList<QString> activeInputPlugins;
  void loadInputPlugins(QString dir);
  void addInputPlugin(std::shared_ptr<InputPlugin> plugin);

  // EditPlugin
  std::vector<std::shared_ptr<EditPlugin>> editPlugins;
  QList<QString> activeEditPlugins;
  void loadEditPlugins(QString dir);
  void addEditPlugin(std::shared_ptr<EditPlugin> plugin);

  // OutputPlugin
  std::vector<std::shared_ptr<OutputPlugin>> outputPlugins;
  QList<QString> activeOutputPlugins;
  void loadOutputPlugins(QString dir);
  void addOutputPlugin(std::shared_ptr<OutputPlugin> plugin);
};
}
}

#endif  // PLUGINLOADER_H

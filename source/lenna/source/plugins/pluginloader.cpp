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

#include "plugins/pluginloader.h"
#include <lenna/logger.h>
#include "lenna/lenna.h"
#include "translation.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QSettings>
#include <QtCore/QStringList>

using namespace lenna::plugin;

PluginLoader *PluginLoader::instance = 0;

PluginLoader::PluginLoader(QObject *parent) : QObject(parent) {
  loadPlugins();
  loadConfig();
}

PluginLoader::~PluginLoader() { saveConfig(); }

void PluginLoader::destroyInstance() {
  if (instance) delete instance;
  instance = 0;
}

PluginLoader &PluginLoader::getInstance() {
  if (!instance) instance = new PluginLoader(0);
  return *instance;
}

void PluginLoader::activatePlugin(QString uid, QString name) {
  if (uid == "{00000000-0000-0000-0000-000000000000}")
    uid = QUuid::createUuid().toString();
  assert(uid != "{00000000-0000-0000-0000-000000000000}");
  if (this->activatedPlugins.contains(uid)) return;
  Plugin *plugin = getPlugin(name);
  if (plugin == nullptr)
    Logger::warning("Plugin could not been loaded: " + name);
  Plugin *pluginInstance = plugin->getInstance(uid);
  activatePlugin(pluginInstance);
}

/**
 * @brief PluginLoader::loadConfig
 * load list of activated plugins from configuration and create instance for
 * them.
 */
void PluginLoader::loadConfig() {
  // load from settings.
  QSettings settings(Lenna::organizationName(), Lenna::applicationName());
  settings.beginGroup("plugins");
  QStringList keys = settings.childKeys();
  for (QString key : keys) {
    activatePlugin(key, settings.value(key).toString());
  }

  // load default plugins
  if (keys.size() < 1) {
    activatePlugin("{4b122e95-6fed-4627-8254-5925fab3178f}", "filechooser");
    activatePlugin("{85fc0624-c940-4720-afb6-e00fa3e0dd91}", "resize");
    activatePlugin("{9076d7c5-9822-4e9b-870b-f344a46368f2}", "savefile");
  }
}

void PluginLoader::saveConfig() {
  QSettings settings(Lenna::organizationName(), Lenna::applicationName());
  settings.beginGroup("plugins");
  // inputplugins
  for (QString uid : this->activeInputPlugins) {
    settings.setValue(uid, this->activatedPlugins.value(uid)->getName());
  }
  // editplugins
  for (QString uid : this->activeEditPlugins) {
    settings.setValue(uid, this->activatedPlugins.value(uid)->getName());
  }
  // outputplugins
  for (QString uid : this->activeOutputPlugins) {
    settings.setValue(uid, this->activatedPlugins.value(uid)->getName());
  }
}

void PluginLoader::activatePlugins(QStringList list) {
  for (int i = 0, in = 0, edit = 0, out = 0; i < list.size(); i++) {
    Plugin *plugin = getPlugin(list.at(i));
    activatePlugin(plugin);
    // sort inputplugins
    InputPlugin *inputPlugin = qobject_cast<InputPlugin *>(plugin);
    if (inputPlugin) {
      moveInputPlugin(inputPlugin, in);
      in++;
    }
    // sort editplugins
    EditPlugin *editPlugin = qobject_cast<EditPlugin *>(plugin);
    if (editPlugin) {
      moveEditPlugin(editPlugin, edit);
      edit++;
    }
    // sort outputplugins
    OutputPlugin *outputPlugin = qobject_cast<OutputPlugin *>(plugin);
    if (outputPlugin) {
      moveOutputPlugin(outputPlugin, out);
      out++;
    }
  }
}

void PluginLoader::activatePlugin(Plugin *plugin) {
  assert(plugin);
  assert(plugin->getUID() != "{00000000-0000-0000-0000-000000000000}");
  if (!activatedPlugins.values().contains(plugin)) {
    activatedPlugins.insert(plugin->getUID(), plugin);
    InputPlugin *inputPlugin = qobject_cast<InputPlugin *>(plugin);
    if (inputPlugin) {
      activeInputPlugins.append(plugin->getUID());
    }
    EditPlugin *editPlugin = qobject_cast<EditPlugin *>(plugin);
    if (editPlugin) {
      activeEditPlugins.append(plugin->getUID());
    }
    OutputPlugin *outputPlugin = qobject_cast<OutputPlugin *>(plugin);
    if (outputPlugin) {
      activeOutputPlugins.append(plugin->getUID());
    }
  }
}

void PluginLoader::deactivatePlugin(Plugin *plugin) {
  if (activatedPlugins.values().contains(plugin)) {
    InputPlugin *inputPlugin = qobject_cast<InputPlugin *>(plugin);
    if (inputPlugin) {
      activeInputPlugins.removeAll(plugin->getUID());
    }
    EditPlugin *editPlugin = qobject_cast<EditPlugin *>(plugin);
    if (editPlugin) {
      activeEditPlugins.removeAll(plugin->getUID());
    }
    OutputPlugin *outputPlugin = qobject_cast<OutputPlugin *>(plugin);
    if (outputPlugin) {
      activeOutputPlugins.removeAll(plugin->getUID());
    }
    activatedPlugins.remove(plugin->getUID());
  }
  assert(activatedPlugins.size() ==
         activeInputPlugins.size() + activeEditPlugins.size() +
             activeOutputPlugins.size());
}

void PluginLoader::deactivatePlugin(int index) {
  if (index >= 0 && index < this->activatedPlugins.size()) {
    deactivatePlugin(activatedPlugins.values().at(index));
  }
}

// returns plugin from string in format "name version"
Plugin *PluginLoader::getPlugin(QString name) {
  foreach (InputPlugin *plugin, this->inputPlugins) {
    if (QString(plugin->getName() + " " + plugin->getVersion()) == name ||
        QString(plugin->getName()) == name) {
      return plugin;
    }
  }
  foreach (EditPlugin *plugin, this->editPlugins) {
    if (QString(plugin->getName() + " " + plugin->getVersion()) == name ||
        QString(plugin->getName()) == name) {
      return plugin;
    }
  }
  foreach (OutputPlugin *plugin, this->outputPlugins) {
    if (QString(plugin->getName() + " " + plugin->getVersion()) == name ||
        QString(plugin->getName()) == name) {
      return plugin;
    }
  }
  return nullptr;
}

Plugin *PluginLoader::getActivePlugin(QString uid) {
  for (Plugin *plugin : this->activatedPlugins) {
    if (plugin->getUID() == uid) return plugin;
  }
  return nullptr;
}

/*
 Reads all files in plugin dir and loads containing plugins.
 */
void PluginLoader::loadPlugins() {
  // Loads Plugins in plugins dir
  QDir pluginsDir(Lenna::applicationDirPath());
  loadInputPlugins(pluginsDir.currentPath());
  loadEditPlugins(pluginsDir.currentPath());
  loadOutputPlugins(pluginsDir.currentPath());

  foreach (QString path, QCoreApplication::libraryPaths()) {
    loadInputPlugins(path);
    loadInputPlugins(path + Lenna::applicationName().toLower());
    loadEditPlugins(path);
    loadEditPlugins(path + Lenna::applicationName().toLower());
    loadOutputPlugins(path);
    loadOutputPlugins(path + Lenna::applicationName().toLower());
  }
#if defined(Q_OS_WIN)
  if (pluginsDir.dirName().toLower() == "debug" ||
      pluginsDir.dirName().toLower() == "release") {
    pluginsDir.cdUp();
    pluginsDir.cdUp();
  }
#elif defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS") {
    pluginsDir.cdUp();
    pluginsDir.cdUp();
    pluginsDir.cdUp();
  }
#elif defined(Q_OS_LINUX)
  loadInputPlugins("/usr/lib/" + QCoreApplication::applicationName().toLower());
  loadInputPlugins("/usr/lib64/" +
                   QCoreApplication::applicationName().toLower());
  loadEditPlugins("/usr/lib/" + QCoreApplication::applicationName().toLower());
  loadEditPlugins("/usr/lib64/" +
                  QCoreApplication::applicationName().toLower());
  loadOutputPlugins("/usr/lib/" +
                    QCoreApplication::applicationName().toLower());
  loadOutputPlugins("/usr/lib64/" +
                    QCoreApplication::applicationName().toLower());
#endif
  loadInputPlugins(pluginsDir.currentPath());
  loadEditPlugins(pluginsDir.currentPath());
  loadOutputPlugins(pluginsDir.currentPath());
}

/*
 * InputPlugin
 */

void PluginLoader::loadInputPlugins(QString dir) {
  QDir pluginsDir(dir);
  if (pluginsDir.exists(dir)) {
    if (!pluginsDir.cd("plugins")) return;
  }

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = pluginLoader.instance();

    if (plugin) {
      // loads Plugins
      InputPlugin *plugin_ = qobject_cast<InputPlugin *>(plugin);
      if (plugin_) {
        addInputPlugin(plugin_);
      } else {
        delete plugin_;
      }
    } else {
    }
  }
}

void PluginLoader::addInputPlugin(InputPlugin *plugin) {
  if (plugin) {
    foreach (InputPlugin *plugin_, inputPlugins) {
      if (plugin_->getName() == plugin->getName()) return;
    }
    inputPlugins.append(plugin);
    Translation::installPluginTranslation(plugin->getName());
  }
}

QList<InputPlugin *> PluginLoader::getInputPlugins() {
  return this->inputPlugins;
}

QList<InputPlugin *> PluginLoader::getActiveInputPlugins() {
  QList<InputPlugin *> plugins;
  for (QString uid : activeInputPlugins) {
    InputPlugin *plugin = (InputPlugin *)this->activatedPlugins.value(uid);
    assert(plugin);
    plugins.append(plugin);
  }
  return plugins;
}

void PluginLoader::moveInputPlugin(InputPlugin *plugin, int index) {
  assert(plugin);
  if (!plugin) return;
  if (index > activeInputPlugins.size() - 1) return;
  if (activeInputPlugins.contains(plugin->getUID())) {
    activeInputPlugins.move(activeInputPlugins.indexOf(plugin->getUID()),
                            index);
  }
}

/*
 * EditPlugin
 */

void PluginLoader::loadEditPlugins(QString dir) {
  QDir pluginsDir(dir);
  if (pluginsDir.exists(dir)) {
    if (!pluginsDir.cd("plugins")) return;
  }

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = pluginLoader.instance();
    if (plugin) {
      // loads Plugins
      EditPlugin *plugin_ = qobject_cast<EditPlugin *>(plugin);
      if (plugin_) {
        addEditPlugin(plugin_);
      } else {
        delete plugin_;
      }
    }
  }
}

void PluginLoader::addEditPlugin(EditPlugin *plugin) {
  if (plugin) {
    foreach (EditPlugin *plugin_, editPlugins) {
      if (plugin_->getName() == plugin->getName()) return;
    }
    editPlugins.append(plugin);
    Translation::installPluginTranslation(plugin->getName());
  }
}

QList<EditPlugin *> PluginLoader::getEditPlugins() { return this->editPlugins; }

QList<EditPlugin *> PluginLoader::getActiveEditPlugins() {
  QList<EditPlugin *> plugins;
  for (QString uid : activeEditPlugins) {
    EditPlugin *plugin = (EditPlugin *)this->activatedPlugins.value(uid);
    assert(plugin);
    plugins.append(plugin);
  }
  return plugins;
}

void PluginLoader::moveEditPlugin(EditPlugin *plugin, int index) {
  if (!plugin) return;
  if (index > activeEditPlugins.size() - 1) return;
  if (activeEditPlugins.contains(plugin->getUID())) {
    activeEditPlugins.move(activeEditPlugins.indexOf(plugin->getUID()), index);
  }
}

/*
 * OutputPlugin
 */

void PluginLoader::loadOutputPlugins(QString dir) {
  QDir pluginsDir(dir);
  if (pluginsDir.exists(dir)) {
    if (!pluginsDir.cd("plugins")) return;
  }

  foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = pluginLoader.instance();
    if (plugin) {
      // loads Plugins
      OutputPlugin *plugin_ = qobject_cast<OutputPlugin *>(plugin);
      if (plugin_) {
        addOutputPlugin(plugin_);
      } else {
        delete plugin_;
      }
    }
  }
}

void PluginLoader::addOutputPlugin(OutputPlugin *plugin) {
  if (plugin) {
    foreach (OutputPlugin *plugin_, outputPlugins) {
      if (plugin_->getName() == plugin->getName()) return;
    }
    outputPlugins.append(plugin);
    Translation::installPluginTranslation(plugin->getName());
  }
}

QList<OutputPlugin *> PluginLoader::getOutputPlugins() {
  return this->outputPlugins;
}

QList<OutputPlugin *> PluginLoader::getActiveOutputPlugins() {
  QList<OutputPlugin *> plugins;
  for (QString uid : activeOutputPlugins) {
    OutputPlugin *plugin = (OutputPlugin *)this->activatedPlugins.value(uid);
    assert(plugin);
    plugins.append(plugin);
  }
  return plugins;
}

void PluginLoader::moveOutputPlugin(OutputPlugin *plugin, int index) {
  if (!plugin) return;
  if (index > activeOutputPlugins.size() - 1) return;
  if (activeOutputPlugins.contains(plugin->getUID())) {
    activeOutputPlugins.move(activeOutputPlugins.indexOf(plugin->getUID()),
                             index);
  }
}

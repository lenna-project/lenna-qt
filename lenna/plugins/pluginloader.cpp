/**
    This file is part of program Lenna
    Copyright (C) 2013  FalseCAM

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

#include "pluginloader.h"
#include "../lenna.h"
#include "../translation.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QPluginLoader>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QStringList>

PluginLoader* PluginLoader::instance = 0;

PluginLoader::PluginLoader(QObject *parent) :
    QObject(parent)
{
    loadPlugins();
    loadConfig();
}

PluginLoader::~PluginLoader(){
    saveConfig();
}

void PluginLoader::destroyInstance(){
    if (instance)
        delete instance;
    instance = 0;
}

PluginLoader& PluginLoader::getInstance() {
    if (!instance)
        instance = new PluginLoader(0);
    return *instance;
}

void PluginLoader::loadConfig(){
    // load from settings.
    QSettings settings(Lenna::organizationName(), Lenna::applicationName());
    settings.beginGroup("plugins");

    QStringList list;
    list << "filechooser" << "resize" << "savefile";
    list = settings.value("ActivatedPlugins", list).toStringList();
    activatePlugins(list);
}

void PluginLoader::saveConfig(){
    QSettings settings(Lenna::organizationName(), Lenna::applicationName());
    settings.beginGroup("plugins");
    QStringList stringList;
    // inputplugins
    foreach(InputPlugin *plugin, inputPlugins){
        if(this->isActivatedPlugin(plugin)){
            stringList.append(plugin->getName() + " " + plugin->getVersion());
        }
    }
    // editplugins
    foreach(EditPlugin *plugin, editPlugins){
        if(this->isActivatedPlugin(plugin)){
            stringList.append(plugin->getName() + " " + plugin->getVersion());
        }
    }
    // outputplugins
    foreach(OutputPlugin *plugin, outputPlugins){
        if(this->isActivatedPlugin(plugin)){
            stringList.append(plugin->getName() + " " + plugin->getVersion());
        }
    }

    QVariant list;
    list.setValue(stringList);
    settings.setValue("ActivatedPlugins", list);
}

void PluginLoader::activatePlugins(QStringList list) {
    for (int i = 0, in = 0, edit = 0, out = 0; i < list.size(); i++) {
        Plugin* plugin = getPlugin(list.at(i));
        activatePlugin(plugin);
        // sort inputplugins
        InputPlugin *inputPlugin = qobject_cast<
                InputPlugin *> (plugin);
        if (inputPlugin) {
            moveInputPlugin(inputPlugin, in);
            in++;
        }
        // sort editplugins
        EditPlugin *editPlugin = qobject_cast<
                EditPlugin *> (plugin);
        if (editPlugin) {
            moveEditPlugin(editPlugin, edit);
            edit++;
        }
        // sort outputplugins
        OutputPlugin *outputPlugin = qobject_cast<
                OutputPlugin *> (plugin);
        if (outputPlugin) {
            moveOutputPlugin(outputPlugin, out);
            out++;
        }
    }
}

/*
 Activates plugin by name and version.
 Activated plugins are used.
 */
void PluginLoader::activatePlugin(QString name) {
    foreach(Plugin* plugin, inputPlugins)
    {
        if (!activatedPlugins.contains(plugin)) {
            if (QString(plugin->getName() + " " + plugin->getVersion())
                    == name || QString(plugin->getName()) == name) {
                activatedPlugins.append(plugin);
            }
        }
    }
}

void PluginLoader::activatePlugin(Plugin *plugin) {
    if(!activatedPlugins.contains(plugin)){
        activatedPlugins.append(plugin);
    }
}

bool PluginLoader::isActivatedPlugin(Plugin *plugin){
    return activatedPlugins.contains(plugin);
}

void PluginLoader::deactivatePlugin(Plugin *plugin){
    if(activatedPlugins.contains(plugin)){
        activatedPlugins.removeOne(plugin);
    }
}

void PluginLoader::deactivatePlugin(int index){
    if(index >= 0 && index < this->activatedPlugins.size()){
        deactivatePlugin(activatedPlugins.at(index));
    }
}

// returns plugin from string in format "name version"
Plugin *PluginLoader::getPlugin(QString name){
    foreach(InputPlugin * plugin, this->inputPlugins)
    {
        if (QString(plugin->getName() + " " + plugin->getVersion())
                == name || QString(plugin->getName()) == name) {
            return plugin;
        }
    }
    foreach(EditPlugin * plugin, this->editPlugins)
    {
        if (QString(plugin->getName() + " " + plugin->getVersion())
                == name || QString(plugin->getName()) == name) {
            return plugin;
        }
    }
    foreach(OutputPlugin * plugin, this->outputPlugins)
    {
        if (QString(plugin->getName() + " " + plugin->getVersion())
                == name || QString(plugin->getName()) == name) {
            return plugin;
        }
    }
    return 0;
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

    foreach (QString path, QCoreApplication::libraryPaths())
    {
        loadInputPlugins(path);
        loadInputPlugins(path + Lenna::applicationName().toLower());
        loadEditPlugins(path);
        loadEditPlugins(path + Lenna::applicationName().toLower());
        loadOutputPlugins(path);
        loadOutputPlugins(path + Lenna::applicationName().toLower());
    }
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug"
            || pluginsDir.dirName().toLower() == "release") {
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
    loadInputPlugins("/usr/lib64/" + QCoreApplication::applicationName().toLower());
    loadEditPlugins("/usr/lib/" + QCoreApplication::applicationName().toLower());
    loadEditPlugins("/usr/lib64/" + QCoreApplication::applicationName().toLower());
    loadOutputPlugins("/usr/lib/" + QCoreApplication::applicationName().toLower());
    loadOutputPlugins("/usr/lib64/" + QCoreApplication::applicationName().toLower());
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
        if (!pluginsDir.cd("plugins"))
            return;
    }

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();


        if (plugin) {
            // loads Plugins
            InputPlugin *plugin_ = qobject_cast<
                    InputPlugin *> (plugin);
            if (plugin_) {
                addInputPlugin(plugin_);
            } else {
                delete plugin_;
            }
        }else{
        }
    }
}

void PluginLoader::addInputPlugin(InputPlugin *plugin) {
    if (plugin) {
        foreach(InputPlugin * plugin_, inputPlugins)
        {
            if (plugin_->getName() == plugin->getName())
                return;
        }
        inputPlugins.append(plugin);
        Translation::installPluginTranslation(plugin->getName());
    }
}

QList<InputPlugin *> PluginLoader::getInputPlugins(){
    return this->inputPlugins;
}

void PluginLoader::moveInputPlugin(InputPlugin *plugin, int index){
    if(index > inputPlugins.size() -1) return;
    if(inputPlugins.contains(plugin)){
        inputPlugins.move(inputPlugins.indexOf(plugin), index);
    }
}

/*
 * EditPlugin
 */

void PluginLoader::loadEditPlugins(QString dir) {
    QDir pluginsDir(dir);
    if (pluginsDir.exists(dir)) {
        if (!pluginsDir.cd("plugins"))
            return;
    }

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {

            // loads Plugins
            EditPlugin *plugin_ = qobject_cast<
                    EditPlugin *> (plugin);
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
        foreach(EditPlugin * plugin_, editPlugins)
        {
            if (plugin_->getName() == plugin->getName())
                return;
        }
        editPlugins.append(plugin);
        Translation::installPluginTranslation(plugin->getName());
    }
}

QList<EditPlugin *> PluginLoader::getEditPlugins(){
    return this->editPlugins;
}

void PluginLoader::moveEditPlugin(EditPlugin *plugin, int index){
    if(index > editPlugins.size() -1) return;
    if(editPlugins.contains(plugin)){
        editPlugins.move(editPlugins.indexOf(plugin), index);
    }
}

/*
 * OutputPlugin
 */

void PluginLoader::loadOutputPlugins(QString dir) {
    QDir pluginsDir(dir);
    if (pluginsDir.exists(dir)) {
        if (!pluginsDir.cd("plugins"))
            return;
    }

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            // loads Plugins
            OutputPlugin *plugin_ = qobject_cast<
                    OutputPlugin *> (plugin);
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
        foreach(OutputPlugin * plugin_, outputPlugins)
        {
            if (plugin_->getName() == plugin->getName())
                return;
        }
        outputPlugins.append(plugin);
        Translation::installPluginTranslation(plugin->getName());
    }
}

QList<OutputPlugin *> PluginLoader::getOutputPlugins(){
    return this->outputPlugins;
}

void PluginLoader::moveOutputPlugin(OutputPlugin *plugin, int index){
    if(index > outputPlugins.size() -1) return;
    if(outputPlugins.contains(plugin)){
        outputPlugins.move(outputPlugins.indexOf(plugin), index);
    }
}

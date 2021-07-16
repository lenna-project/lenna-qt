# Plugins

Lenna is a program that can be easily extended with plugins to add more functionality.
These plugins are divided into three types.

* Input Plugins - Load images from sources like files on the device or download them from the web.
* Edit Plugins - Convert images and execute filter on them.
* Output Plugins - Save images to the device or uploads them to the web.

## Plugins developed in C++

Plugins which are developed in c++ must implement the following interfaces.

* [Input Plugins](source/lennaplugin/include/lenna/plugins/inputplugin.h)
* [Edit Plugins](source/lennaplugin/include/lenna/plugins/editplugin.h)
* [Output Plugins](source/lennaplugin/include/lenna/plugins/outputplugin.h)

An example for an input plugin is [filechooser](/home/chriamue/workspace/lenna-project/lenna/source/lennaplugins/filechooser).

An example for an edit plugin is [blur](/home/chriamue/workspace/lenna-project/lenna/source/lennaplugins/blur).

An example for an output plugin is [savefile](/home/chriamue/workspace/lenna-project/lenna/source/lennaplugins/savefile).

## Plugins developed in Rust

[lenna-core](https://github.com/lenna-project/lenna-core) and [lenna-plugins](https://github.com/lenna-project/lenna-plugins)
are developed in Rust. That allows to compile them to wasm and use them for plugins on [lenna.app](https://lenna.app).

The goal here is also to use them as plugin in for the [lenna desktop app](README.md).

An example is the [cartoonify-plugin](https://github.com/lenna-project/cartoonify-plugin).

# lenna-qt [![Build Status][travis-image]][travis] [![Documentation][codedocs-image]][codedocs] [![Release][release-image]][releases] [![License][license-image]][license] [![lenna](https://snapcraft.io/lenna/badge.svg)](https://snapcraft.io/lenna)
==============

*Open Source Image Processing Program*

Lenna is an app to process images.
Core functionality is to compress images in a batch,
resize or rename images.

As the successor of [easyimagesizer](https://sourceforge.net/projects/easyimagesizer/), Lenna contains most of the functionality of easyimagesizer.

Due to its modular structure, lenna can also be used as a webapp on [lenna.app](https://lenna.app).

[travis-image]: https://travis-ci.com/lenna-project/lenna-qt.svg?branch=main
[travis]: https://travis-ci.com/lenna-project/lenna-qt

[codedocs-image]: https://codedocs.xyz/lenna-project/lenna-qt.svg?branch=main
[codedocs]: https://codedocs.xyz/lenna-project/lenna-qt/

[release-image]: https://img.shields.io/github/v/release/lenna-project/lenna-qt?branch=main
[releases]: https://github.com/lenna-project/lenna-qt/releases

[license-image]: https://img.shields.io/github/license/lenna-project/lenna-qt?branch=main
[license]: LICENSE

![Preview of Lenna Desktop](docs/assets/preview.png "Preview of Lenna")

## Features

* Drag and drop images
* convert images to formats like png, bmp, tiff or jpeg
* batch convert folders

The App is extendable by plugins.

* resize
* rotate
* crop
* rename
* textoverlay
* folders

## Quick start

First install CMake, Qt5, OpenCV.

Then build and run.

```sh
git clone https://github.com/lenna-project/lenna-qt
cd lenna-qt
mkdir build
cd build
cmake ..
make
./bin/lenna-qt
```

### Packages

```sh
make pack
```

#### SNAP Package
```sh
snapcraft --enable-experimental-extensions
# publish
snapcraft login
snapcraft upload --release=edge lenna-qt_*_amd64.snap
```

## create new version

Change version in files VERSION and CMakeLists.txt.

```bash
 git tag -a vx.y.z -m "Version x.y.z"
 git push origin --tags
```

## Plugins

Lenna is extended by plugins. For more details see [Plugins Docs](PLUGINS.md).

## Contribute

Contributions are always welcome!

## 📜 License

This software is licensed under the [MIT](https://github.com/lenna-project/lenna-qt/blob/main/LICENSE) © [lenna-project](https://github.com/lenna-project).

/*
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "savefile.h"
#include <QProxyStyle>
#include <QDir>

SaveFile::SaveFile()
{
    this->widget = 0;
}

SaveFile::~SaveFile()
{
}

QString SaveFile::getName(){
    return QString("savefile");
}

QString SaveFile::getTitle(){
    return QString(tr("Save File"));
}

QString SaveFile::getVersion(){
    return QString("1.0");
}

QString SaveFile::getAuthor(){
    return QString("FalseCAM");
}

QString SaveFile::getDescription(){
    return QString(tr("Plugin to save images to desktop."));
}

QIcon SaveFile::getIcon(){
    QProxyStyle s;
    return s.standardIcon (QStyle::SP_FileDialogNewFolder);
}

QWidget *SaveFile::getWidget(){
    if(!widget){
        widget = new Widget();
    }
    return widget;
}

void SaveFile::out(Image *image){
    getWidget();
    QString folder = this->widget->getFolder();
    folder.append("/");
    folder.append(image->getAlbum());
    folder.append("/");
    QString file = folder + image->getName() + "." + widget->getImageFormat();
    if(!QDir(folder).exists()){
        QDir().mkdir(folder);
    }
    vector<int> params;

    if(widget->getImageQuality() != 0){
        if(widget->getImageFormat().toLower() == "png"){
            params.push_back(cv::IMWRITE_PNG_COMPRESSION);
            params.push_back(widget->getImageQuality()/100);
        }else if(widget->getImageFormat().toLower() == "jpg" ||widget->getImageFormat().toLower() == "jpeg"){
            params.push_back(cv::IMWRITE_JPEG_QUALITY);
            params.push_back(widget->getImageQuality());
        }
    }
    cv::imwrite(file.toStdString().c_str(), image->getImage(), params);
}

void SaveFile::finnish(){

}

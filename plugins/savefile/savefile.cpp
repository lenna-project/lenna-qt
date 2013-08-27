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

}

void SaveFile::finnish(){

}

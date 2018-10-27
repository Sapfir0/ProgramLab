#include "fotobase.h"

fotobase::fotobase()
{

}
void fotobase::ourBaseSetter(fotobase writing) {
    qDebug() << "sstop it";
//    writing.getNameOfModel();
//    writing.getGategory();
//    writing.getAnalogOrNot();
//    writing.getProducer();
//    writing.getMatrRes();
//    writing.getChangeLense();
//    writing.getSize();
//    writing.getWeight();
//    writing.getCost();
//    writing.getmyDate();
}
void fotobase::ourBaseGetter(fotobase writing) {
    writing.getNameOfModel();
    writing.getGategory();
    writing.getAnalogOrNot();
    writing.getProducer();
    writing.getMatrRes();
    writing.getChangeLense();
    writing.getSize();
    writing.getWeight();
    writing.getCost();
    writing.getmyDate();
}

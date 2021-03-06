#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

#include "kernel.h"
#include "raster.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisoperation.h"

#include "itemrange.h"
#include "domainitem.h"
#include "itemdomain.h"

#include "interval.h"
#include "numericdomain.h"
#include "intervalrange.h"

#include "testsuite.h"
#include "testutils.h"
#include "rasteroperationstest.h"


#define IMAGE_TO_STRETCH "tmb3.mpr"

REGISTER_TEST(RasterOperationsTest);

RasterOperationsTest::RasterOperationsTest(): IlwisTestCase("RasterOperationsTest", "RasterOperationsTest")
{
}

//void RasterOperationsTest::testLinearStretchWithValueLimits()
//{
//    try {
//        qDebug() << "stretch raster";
//        QString expr = QString("stretch_out=linearstretch(%1, 70, 120)").arg(IMAGE_TO_STRETCH);

//        Operation op(expr);
//        DOTEST2(op->execute(&_ctx,_symtbl), "stretching with value limits failed.");
//    }
//    catch(ErrorObject& err) {
//        qDebug() << err.message();
//        QVERIFY(false);
//    }
//}

//void RasterOperationsTest::testLinearStretchWithPercentLimits() {
//    try {
//        qDebug() << "stretch raster";
//        QString expr = QString("stretch_out=linearstretch(%1, 10)").arg(IMAGE_TO_STRETCH);

//        Operation op(expr);
//        DOTEST2(op->execute(&_ctx,_symtbl), "stretching with percent limits failed.");
//    }
//    catch(ErrorObject& err) {
//        qDebug() << err.message();
//        QVERIFY(false);
//    }
//}

void RasterOperationsTest::testResample() {
    QString expr = QString("aaresample1=resample(small.mpl,aeqsmall.grf,nearestneighbour)");
    Ilwis::ExecutionContext ctx;
    DOTEST(Ilwis::commandhandler()->execute(expr,&ctx), "resample blas.");

    Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aaresample1");
    raster->connectTo(QString("file:///%1/aaresample1.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    raster->createTime(Ilwis::Time::now());
    raster->store();
}

void RasterOperationsTest::testMirrorRotate() {
    try {
        qDebug() << "mirror raster";
        QString expr = QString("aamirvert=mirrorrotateraster(small.mpr,rotate180)");
        Ilwis::ExecutionContext ctx;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx), "mirror rotate mirrvert failed.");

        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aamirvert");
        raster->connectTo(QString("file:///%1/aamirvert.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




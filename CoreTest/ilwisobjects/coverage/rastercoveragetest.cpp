#include "kernel.h"
#include "testsuite.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "coverage.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "raster.h"
#include "pixeliterator.h"
#include "attributerecord.h"
#include "geometryhelper.h"
#include "numericdomain.h"
#include "juliantime.h"
#include "operationhelper.h"
#include "rastercoveragetest.h"


REGISTER_TEST(RasterCoverageTest);

RasterCoverageTest::RasterCoverageTest() : IlwisTestCase("RasterCoverageTest","CoreTest")
{
}


void RasterCoverageTest::bands(){

    Ilwis::IGeoReference grf("code=georef:type=corners,csy=vgt4ndvi.csy,envelope=11.019147 6.004464 33 40.914982 -34.938590,gridsize=840 1148,name=gorilla");
    DOTEST(grf.isValid(),"making georef by code");

    Ilwis::IRasterCoverage raster(makeInputPath("average_monthly_temperature.mpl"));
    DOTEST(raster.isValid(),"map list loaded");
    double origvalue1 = raster->pix2value(Ilwis::Pixel(500,500,3));
    double origvalue2 = raster->pix2value(Ilwis::Pixel(500,500,4));

    Ilwis::IRasterCoverage raster2;
    raster2.prepare();
    Ilwis::PixelIterator iter = raster->band(3);
    Ilwis::PixelIterator iter2 = raster->band(4);

    Ilwis::ITimeDomain dom;
    dom.prepare();
    dom->range(new Ilwis::TimeInterval("20090101", "20110101"));
    raster2->indexDomain(dom);


    QVariant tvar = qVariantFromValue(Ilwis::Time("20090131"));
    raster2->band(tvar,iter);
    raster2->band("20090602",iter2);

    DOTEST(raster2->pix2value(Ilwis::Pixel(500,500,0)) == origvalue1,"same value as original1");
    DOTEST(raster2->pix2value(Ilwis::Pixel(500,500,1)) == origvalue2,"same value as original2");



}
#include <QFileInfo>
#include <QUrl>
#include <QDir>

#include "geos/io/ParseException.h"
#include "geos/geom/GeometryFactory.h"
#include "geos/geom/LinearRing.h"
#include "geos/geom/Polygon.h"

#include "kernel.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "geometries.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "catalog.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "attributedefinition.h"
#include "table.h"
#include "connectorinterface.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "coordinatesystem.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "feature.h"
#include "featureiterator.h"
#include "feature.h"
#include "geometryhelper.h"

#include "wfsdemo.h"
#include "wfscatalogexplorer.h"
#include "wfstestconstants.h"

#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsDemo);

WfsDemo::WfsDemo():
    IlwisTestCase("WfsDemo", "Demo")
{
}

void WfsDemo::wfsCatalog_prepareAndSetAsWorkingCatalog_hasWfsResourcesRegistered()
{
    try {
        ICatalog cat;
        cat.prepare("http://ogi.state.ok.us/geoserver/wfs?service=WFS");

        std::vector<Resource> items = cat->items();
        Resource feature(items.front());
        feature.addProperty("forceXY", false);
        IFeatureCoverage coverage;
        if ( !coverage.prepare(feature)) {
            QFAIL("Could not prepare coverage.");
        }

        coverage->connectTo(makeOutputPath("ogi.shp"), "ESRI Shapefile", "gdal", IlwisObject::cmOUTPUT);
        coverage->store();
    } catch (std::exception& e) {
        QFAIL(QString("exception occured: %1").arg(e.what()).toLatin1().constData());
    }

}

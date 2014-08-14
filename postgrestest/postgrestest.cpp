#include <QUrl>

#include "ilwis.h"
#include "symboltable.h"
#include "testsuite.h"
#include "kernel.h"
#include "ilwiscontext.h"
#include "resource.h"
#include "ilwisdata.h"
#include "catalog.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "attributerecord.h"
#include "geometries.h"
#include "feature.h"
#include "coordinatesystem.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "featureiterator.h"

#include "postgrestest.h"

using namespace Ilwis;
using namespace Postgresql;

REGISTER_TEST(PostgresTest);

PostgresTest::PostgresTest() : IlwisTestCase("PostgresqlConnectorTest", "PostgresqlConnectorTest")
{
}

void PostgresTest::prepareDatabaseConnection(Resource &dbResource)
{
    dbResource.addProperty("pg.password", "postgres");
    dbResource.addProperty("pg.user", "postgres");
    //dbResource.addProperty("pg.schema", "public");
    dbResource.prepare();
}

void PostgresTest::initDatabaseItemsWithoutCatalog()
{
    QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/public/tl_2010_us_rails");

    ITable table;
    Resource tableResource(connectionString, itFLATTABLE);
    prepareDatabaseConnection(tableResource);
    if ( !table.prepare(tableResource)) {
        QFAIL("Could not prepare table.");
    }

    IFeatureCoverage coverage;
    Resource coverageResource(connectionString, itCOVERAGE);
    prepareDatabaseConnection(coverageResource);
    if ( !coverage.prepare(coverageResource)) {
        QFAIL("Could not prepare coverage.");
    }

    DOTEST2(coverage.isValid(), "Coverage is not valid.");
    DOTEST2(coverage->coordinateSystem().isValid(), "CRS is not valid.");
    QString actual = coverage->coordinateSystem()->code();
    DOTEST2(actual == "epsg:4269", QString("SRS was NOT expected to be '%1'").arg(actual));
}

void PostgresTest::loadDataFromPlainTable()
{
    QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/persons");

    ITable table;
    Resource tableResource(connectionString, itFLATTABLE);
    prepareDatabaseConnection(tableResource);
    if ( !table.prepare(tableResource)) {
        QFAIL("Could not prepare table.");
    }

    if ( !table.isValid()) {
        QFAIL("prepared table is not valid.");
    }

    DOCOMPARE(table->columnCount(), (unsigned int)5, "check number of columns in 'persons' table.");

    QString actual = table->cell("lastname",0).toString();
    DOTEST2(actual == "Simpson", QString("lastname was NOT expected to be '%1'").arg(actual));
}

void PostgresTest::loadDataFromFeatureWithMultipleGeometriesTable()
{
    QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/tl_2010_us_rails");

    IFeatureCoverage fcoverage;
    Resource coverageResource(connectionString, itCOVERAGE);
    prepareDatabaseConnection(coverageResource);
    if ( !fcoverage.prepare(coverageResource)) {
        QFAIL("Could not prepare feature coverage.");
    }

    if ( !fcoverage.isValid()) {
        QFAIL("prepared feature coverage is not valid.");
    }

    ITable table = fcoverage->attributeTable();
    DOCOMPARE(table->columnCount(), (unsigned int)5, "check number of columns in 'tl_2010_us_rails' table.");
    DOCOMPARE(fcoverage->featureCount(itLINE), (unsigned int)185971, "check number of polygons in 'tl_2010_us_rails' table.");

    QString actual = table->cell("fullname",3).toString();
    DOTEST2(actual == "Illinois Central RR", QString("fullname was NOT expected to be '%1'").arg(actual));

    FeatureIterator iter(fcoverage);
//    while (iter != iter.end()) {

//        // TODO test features content via iterator
//        // (*iter)->featureid();
//        ++iter;

//    }
}

void PostgresTest::loadDataFromFeatureWithSingleGeometryTable()
{
    QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/tl_2010_us_state10");

    IFeatureCoverage fcoverage;
    Resource coverageResource(connectionString, itCOVERAGE);
    prepareDatabaseConnection(coverageResource);
    if ( !fcoverage.prepare(coverageResource)) {
        QFAIL("Could not prepare feature coverage.");
    }

    if ( !fcoverage.isValid()) {
        QFAIL("prepared feature coverage is not valid.");
    }

    ITable table = fcoverage->attributeTable();
    DOCOMPARE(table->columnCount(), (unsigned int)16, "check number of columns in 'tl_2010_us_state10' table.");
    DOCOMPARE(fcoverage->featureCount(itPOLYGON), (unsigned int)52, "check number of polygons in 'tl_2010_us_state10' table.");


    QString actual = table->cell("name10",0).toString();
    DOTEST2(actual == "Wyoming", QString("name10 was NOT expected to be '%1'").arg(actual));

    FeatureIterator iter(fcoverage);
//    while (iter != iter.end()) {

//        // (*iter)->featureid();
//        ++iter;

//    }

}

void PostgresTest::initDatabaseItemsFromCatalog()
{
    try {
        QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test");
        Resource dbCatalog(connectionString, itCATALOG);
        prepareDatabaseConnection(dbCatalog);

        ICatalog cat(dbCatalog);
        std::vector<Resource> items = cat->items();
        if (items.size() == 0) {
            QFAIL("no catalog items found! Check if test db is initiated properly.");
        }

        std::for_each(items.begin(), items.end(),[](Resource &resource) {

            DOTEST2(resource.hasProperty("pg.user"), "pg resource does not contain db user");
            DOTEST2(resource.hasProperty("pg.password"), "pg resource does not contain db password");
            DOTEST2(resource.hasProperty("pg.schema"), "pg resource does not contain db schema");

            ITable table;
            //Resource tableResource(resource.url(), itFLATTABLE);
            if ( !table.prepare(resource)) {
                QFAIL("Could not prepare table.");
            }

            DOTEST2(resource.url().toString().endsWith(table->name()), QString("Table resource does not end with '%1'").arg(table->name()));

        });

    } catch (std::exception& e) {
        QFAIL(QString(e.what()).toLatin1().constData());
    }


}

void PostgresTest::initDatabaseItemByNameFromCatalog()
{
    try {
        QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test");
        Resource dbCatalog(connectionString, itCATALOG);
        prepareDatabaseConnection(dbCatalog);

        ICatalog cat;
        if ( !cat.prepare(dbCatalog)) {
            QFAIL("Could not prepare catalog!");
        }

        context()->setWorkingCatalog(cat);

        ITable table;
        QString item = cat->resolve("tl_2010_us_state10");
        if ( !table.prepare(item,itFLATTABLE)) {
            QFAIL("Could not prepare table.");
        }

        DOCOMPARE(table->columnCount(), (unsigned int)16, "check number of columns in 'tl_2010_us_state10' table.");

        QString actual = table->cell("name10",0).toString();
        DOTEST2(actual == "Wyoming", QString("name10 was NOT expected to be '%1'").arg(actual));


    } catch (std::exception& e) {
        QFAIL(QString(e.what()).toLatin1().constData());
    }
}


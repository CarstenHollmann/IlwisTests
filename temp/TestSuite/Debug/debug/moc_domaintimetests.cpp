/****************************************************************************
** Meta object code from reading C++ file 'domaintimetests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../TestSuites/core/ilwisobjects/domain/domaintimetests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'domaintimetests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DomainTimeTests_t {
    QByteArrayData data[3];
    char stringdata[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DomainTimeTests_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DomainTimeTests_t qt_meta_stringdata_DomainTimeTests = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 12),
QT_MOC_LITERAL(2, 29, 0)
    },
    "DomainTimeTests\0construction\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DomainTimeTests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DomainTimeTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DomainTimeTests *_t = static_cast<DomainTimeTests *>(_o);
        switch (_id) {
        case 0: _t->construction(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DomainTimeTests::staticMetaObject = {
    { &IlwisTestCase::staticMetaObject, qt_meta_stringdata_DomainTimeTests.data,
      qt_meta_data_DomainTimeTests,  qt_static_metacall, 0, 0}
};


const QMetaObject *DomainTimeTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DomainTimeTests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DomainTimeTests.stringdata))
        return static_cast<void*>(const_cast< DomainTimeTests*>(this));
    return IlwisTestCase::qt_metacast(_clname);
}

int DomainTimeTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IlwisTestCase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../guibin/gui.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_WordChainUI_t {
    uint offsetsAndSizes[14];
    char stringdata0[12];
    char stringdata1[31];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[32];
    char stringdata5[32];
    char stringdata6[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_WordChainUI_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_WordChainUI_t qt_meta_stringdata_WordChainUI = {
    {
        QT_MOC_LITERAL(0, 11),  // "WordChainUI"
        QT_MOC_LITERAL(12, 30),  // "onInputPathChooseButtonClicked"
        QT_MOC_LITERAL(43, 0),  // ""
        QT_MOC_LITERAL(44, 20),  // "onSolveButtonClicked"
        QT_MOC_LITERAL(65, 31),  // "onOutputPathChooseButtonClicked"
        QT_MOC_LITERAL(97, 31),  // "onFunctionalParamNButtonClicked"
        QT_MOC_LITERAL(129, 7)   // "checked"
    },
    "WordChainUI",
    "onInputPathChooseButtonClicked",
    "",
    "onSolveButtonClicked",
    "onOutputPathChooseButtonClicked",
    "onFunctionalParamNButtonClicked",
    "checked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_WordChainUI[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    0,   40,    2, 0x08,    3 /* Private */,
       5,    1,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject WordChainUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_WordChainUI.offsetsAndSizes,
    qt_meta_data_WordChainUI,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_WordChainUI_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WordChainUI, std::true_type>,
        // method 'onInputPathChooseButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSolveButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOutputPathChooseButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFunctionalParamNButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void WordChainUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WordChainUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onInputPathChooseButtonClicked(); break;
        case 1: _t->onSolveButtonClicked(); break;
        case 2: _t->onOutputPathChooseButtonClicked(); break;
        case 3: _t->onFunctionalParamNButtonClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *WordChainUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordChainUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WordChainUI.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WordChainUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

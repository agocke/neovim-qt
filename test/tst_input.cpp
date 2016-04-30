
#include <QtTest/QtTest>
#include <gui/input.h>

class TestInput: public QObject
{
    Q_OBJECT
private slots:
    void specialKeys();
private:
    NeovimQt::InputConv input;
};

void TestInput::specialKeys()
{
    foreach(int k, input.specialKeys.keys()) {
        QCOMPARE(input.convertKey("", k, Qt::NoModifier),
            QString("<%1>").arg(input.specialKeys.value(k)));


#ifdef Q_OS_MAC
            // On Mac Control is actually the Cmd key, which we
            // don't support yet
        auto ctrlMap = QString("<D-%1>").arg(input.specialKeys.value(k));
#else
        auto ctrlMap = QString("<C-%1>").arg(input.specialKeys.value(k));
#endif
        QCOMPARE(input.convertKey("", k, Qt::ControlModifier), ctrlMap);

        QCOMPARE(input.convertKey("", k, Qt::AltModifier),
            QString("<A-%1>").arg(input.specialKeys.value(k)));

#ifdef Q_OS_MAC
        // On Mac Meta is actually the Control key
        auto metaMap = QString("<C-%1>").arg(input.specialKeys.value(k));
#else
        // Meta is not handled right now
        auto metaMap = QString("<%1>").arg(input.specialKeys.value(k));
#endif
        QCOMPARE(input.convertKey("", k, Qt::MetaModifier), metaMap);
    }
}

QTEST_MAIN(TestInput)
#include "tst_input.moc"

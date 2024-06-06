#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "animatewidgets.h"
#include "anchormanager.h"
#include "tooltip.h"
#include <QTimer>
#include <QSignalMapper>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // AnimateWidgets::instance()->enableQssAnimation(ui->widget);
    // AnimateWidgets::instance()->disableQssAnimation(ui->widget);
    AnimateWidgets::instance()->enableQssAnimation(ui->pushButton);
    AnchorManager::instance()->installAnchor(ui->widget_9, AnchorManager::AnchorTypes(AnchorManager::AnchorCenter));
    AnchorManager::instance()->installAnchor(ui->widget,
                                             std::map<AnchorManager::AnchorType,
                                                      AnchorManager::AnchorType>({
                                                                                  {AnchorManager::AnchorVCenter, AnchorManager::AnchorVCenter},
                                                                                  {AnchorManager::AnchorLeft, AnchorManager::AnchorRight},
                                                                                  }), QMargins(12, 0, 0, 0), ui->widget_2, true);
    AnchorManager::instance()->installAnchor(ui->pushButton,
                                             std::map<AnchorManager::AnchorType,
                                                      AnchorManager::AnchorType>({
                                                                                  {AnchorManager::AnchorVCenter, AnchorManager::AnchorVCenter},
                                                                                  {AnchorManager::AnchorLeft, AnchorManager::AnchorRight},
                                                                                  }), QMargins(12, 0, 0, 0), ui->widget, true);

    AnchorManager::instance()->installAnchor(ui->label, AnchorManager::AnchorTypes(AnchorManager::AnchorCenter));
    ui->widget_3->setSourceWidget(ui->frame);


    QString startQss = R"(
        color:  purple;
        qproperty-rotation: 0;
    )";
    QString endQss = R"(
        qproperty-rotation: 360;
    )";

    //widget_8
    AnimateWidgets::instance()->startQssAnimation(ui->widget_8, startQss, endQss, 1000, true, QEasingCurve::Linear);

    auto mapper = new QSignalMapper(this);
    connect(mapper, &QSignalMapper::mappedObject, this, [this] (QObject *button) {
        auto b = static_cast<QAbstractButton*> (button);
        qDebug() << b->text() << "clicked";
        b->setText(b->text() + "(Disabled)");
        b->setEnabled(false);
        QTimer::singleShot(3000, this, [=](){
            b->setText(b->text().remove("(Disabled)"));
            b->setEnabled(true);
        });
        if (b->metaObject()->inherits(LinkButton().metaObject())) {
            qDebug() << b->property("link");
        }
        if (b->inherits("QRadioButton") || b->inherits("QCheckBox")) {
            b->setProperty("hasBorder", !b->property("hasBorder").toBool());
        }
    });
    auto temp = {ui->widget_10, ui->widget_11, ui->widget_12, ui->widget_13,
                 ui->widget_14, ui->widget_15, ui->widget_16, ui->widget_17,
                 ui->widget_18, ui->widget_19, ui->widget_20, ui->widget_21};
    for (auto w : temp) {
        auto children = w->children();
        for (auto c : children) {
            if (c->inherits("QAbstractButton")) {
                QPushButton *button = static_cast<QPushButton *>(c);
                connect(button, &QPushButton::clicked, mapper, qOverload<>(&QSignalMapper::map));
                mapper->setMapping(button, button);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ToolTip tip(nullptr, Qt::FramelessWindowHint);
    tip.show();
    // AnimateWidgets::instance()->stopQssAnimation(ui->widget_8);
    // ui->frame->resize(ui->frame->size() + QSize(10, 10));
}



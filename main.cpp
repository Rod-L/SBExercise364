#include <QApplication>
#include <QSlider>
#include <QBoxLayout>
#include <QPixmap>
#include <QLabel>

//// TrafficLight class

class TrafficLight: public QLabel {
    int CurrentColorCode;
    QPixmap red_pic;
    QPixmap yellow_pic;
    QPixmap green_pic;
public:
    TrafficLight(QString& _red, QString& _yellow, QString& _green, QWidget* parent);
    void set_color(int color_code);
};

TrafficLight::TrafficLight(QString& _red, QString& _yellow, QString& _green, QWidget* parent) {
    red_pic.load(_red);
    yellow_pic.load(_yellow);
    green_pic.load(_green);

    CurrentColorCode = 0;
    setPixmap(green_pic);

    if (parent) setParent(parent);
}

void TrafficLight::set_color(int color_code) {
    if (color_code == CurrentColorCode) return;
    switch (color_code) {
        case 0: setPixmap(green_pic); break;
        case 1: setPixmap(yellow_pic); break;
        default: setPixmap(red_pic);
    }
    CurrentColorCode = color_code;
}

//// main

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget window;

    // slider
    QSlider slider(Qt::Orientation::Horizontal, &window);
    slider.setMinimum(0);
    slider.setMaximum(100);

    // image
    QString red = "..//red.png", yellow = "..//yellow.png", green = "..//green.png";
    TrafficLight image(red, yellow, green, &window);
    image.setAlignment(Qt::AlignCenter);

    QSlider::connect(&slider, &QSlider::valueChanged, [&image](int value){
        auto code = value / 33;
        image.set_color(code);
    });

    // layout
    QVBoxLayout box(&window);
    box.addWidget(&image);
    box.addWidget(&slider);

    window.show();
    return QApplication::exec();
}

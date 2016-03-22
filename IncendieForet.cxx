#include<iostream>
#include <QApplication>

#include "CFenetre.h"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication app (argc, argv);
    CFenetre fenetre;
    fenetre.show();
    return app.exec();
}

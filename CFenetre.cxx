#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

#include "CFenetre.h"



CFenetre::CFenetre(unsigned Taille /* = 30 */, double Densite /* = 0 */) noexcept
    :m_Taille(Taille), m_Densite(Densite), QWidget()
{
    createZoneInfo();
    m_ZoneForet = new CForet(m_Taille, m_Densite);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(m_ZoneInfo);
    layout->addWidget(m_ZoneForet);
    setLayout(layout);
    setWindowTitle("IncendieForet");
}//CFenetre()






unsigned CFenetre::getTaille() const noexcept
{
    return m_Taille;
}

float CFenetre::getDensite() const noexcept
{
    return m_Densite;
}





void CFenetre::createZoneInfo() noexcept
{
    QGridLayout * infoLayout = new QGridLayout;

    m_ZoneInfo = new QGroupBox("Donnees");

    QLabel * LabelTaille = new QLabel("Taille de la matrice : ");
    m_SpinBoxTaille = new QSpinBox; // setGeometry
    m_SpinBoxTaille->setSingleStep(1);
    m_SpinBoxTaille->setRange(2, 50);
    m_SpinBoxTaille->setValue(this->getTaille());

    QLabel * LabelDensite = new QLabel("Densite de la foret : ");
    m_SpinBoxDensite = new QDoubleSpinBox;
    m_SpinBoxDensite->setRange(0.0, 1.0);
    m_SpinBoxDensite->setSingleStep(0.05);
    m_SpinBoxDensite->setValue(this->getDensite());

    m_BoutonGenerer = new QPushButton("Generer matrice", this);
    infoLayout->addWidget(LabelTaille, 0, 0);
    infoLayout->addWidget(m_SpinBoxTaille, 0, 1);
    infoLayout->addWidget(LabelDensite, 2, 0);
    infoLayout->addWidget(m_SpinBoxDensite, 2, 1);
    infoLayout->addWidget(m_BoutonGenerer, 3, 0, 1, 2);
    infoLayout->addWidget(NULL, 4, 0);
    m_ZoneInfo->setLayout(infoLayout);

    m_ZoneInfo->setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 9px; margin-top: 0.5em;} QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}");

    QObject::connect(m_BoutonGenerer, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(m_BoutonGenerer, SIGNAL(clicked(bool)), this, SLOT(nouvelleFenetre()));

    m_ZoneInfo->setMaximumWidth(250);

}// createZoneInfo()




void CFenetre::nouvelleFenetre() noexcept
{
    m_newWindow = new CFenetre(m_SpinBoxTaille->value(), m_SpinBoxDensite->value());
    m_newWindow->show();
}//nouvelleFenetre()

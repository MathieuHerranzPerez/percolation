#ifndef CFENETRE
#define CFENETRE

#include <QWidget>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "CForet.h"

class CFenetre : public QWidget
{
    Q_OBJECT
    private:
        CForet * m_ZoneForet;
        QGroupBox * m_ZoneInfo;
        QSpinBox * m_SpinBoxTaille;
        QDoubleSpinBox * m_SpinBoxDensite;
        unsigned m_Taille;
        float m_Densite;
        QPushButton * m_BoutonGenerer;
        CFenetre * m_newWindow;
        void createZoneInfo() noexcept;
    public:
        CFenetre(unsigned Taille = 30, double Densite = 0) noexcept;
        unsigned getTaille() const noexcept;
        float getDensite() const noexcept;
    public slots:
        void nouvelleFenetre() noexcept;
};

#endif // CFENETRE


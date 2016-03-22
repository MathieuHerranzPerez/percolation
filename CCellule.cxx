#include "CCellule.h"
CCellule::CCellule(QWidget * Parent) noexcept
    :m_Arbre(nullptr), QPushButton("",Parent), m_Parent(Parent)
{
    setFixedSize(15, 15);
    setStyleSheet("QPushButton { background-color: white; }");
}

CArbre * CCellule::getArbre() const noexcept
{
    return m_Arbre;
}

void CCellule::setArbre(CArbre * Arbre) noexcept
{
    m_Arbre = Arbre;
    QObject::connect(this, SIGNAL(clicked(bool)), m_Parent, SLOT(PropagerIncendie()));
    setStyleSheet("QPushButton { background-color: green; }");
}


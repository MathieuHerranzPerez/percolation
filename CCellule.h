#ifndef CCELLULE_H
#define CCELLULE_H
#include <utility>
#include <QWidget>
#include <QPushButton>
#include "CArbre.h"

class CCellule : public QPushButton
{
    private:
        CArbre * m_Arbre;
        QWidget * m_Parent;
    public:
        CCellule(QWidget * Parent) noexcept;

        CArbre * getArbre() const noexcept;
        void setArbre(CArbre * Arbre) noexcept;
        bool ContienArbre() const noexcept;
};



#endif // CCELLULE_H

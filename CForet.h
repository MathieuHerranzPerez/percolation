#ifndef CFORET_H
#define CFORET_H
#include <vector>
#include <utility>
#include <iostream>
#include <QWidget>
#include <QGroupBox>

#include "CCellule.h"
#include "CArbre.h"

class CForet : public QGroupBox
{
    Q_OBJECT
    typedef std::vector<std::vector<CCellule *>> MC;
    typedef std::pair<unsigned, unsigned> PairUnsigned;

    private:
        float m_Densite; // Densité de la forêt
        MC m_Foret; // Matrice representant la foret
        std::vector<CArbre> m_Arbres; // Tableau des Arbres de la forêt
        std::vector<CArbre *> m_ArbresEnFeu; //Tableau des Arbres enflammés
        unsigned m_Size;

    public:
        CForet(const unsigned & Size, const double & Densite) noexcept;
        void GenereForet(const unsigned & Size, const float & Densite) noexcept;
        void setDensite(const unsigned & Densite) noexcept;
        void setSize(const unsigned & Size) noexcept;
        unsigned getSize() const noexcept;
        CArbre * getArbre(unsigned Index);
        void Enflammer (CArbre * Arbre) noexcept;
        void TrouverVoisins(CArbre * Arbre) noexcept;

    public slots:
        void PropagerIncendie() noexcept;
};

#endif // CFORET_H


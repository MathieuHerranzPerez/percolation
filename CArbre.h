#ifndef CARBRE_H
#define CARBRE_H
#include <iostream>
#include <utility>
#include <QPushButton>


class CArbre
{
    private:
        unsigned m_Etat; // Etat de l'arbre
        CArbre * m_Voisins[4]; // Arbres voisins de l'arbre.
        std::pair<unsigned,unsigned> m_Pos; //Coordonnées de l'Arbre
        QPushButton * m_CelluleArbre; //La cellule sur laquelle se trouve l'Arbre
    public:
        static const unsigned m_KIntact = 0; // Etat de l'arbre qui n'est pas et n'a pas été brulé
        static const unsigned m_KEnflamme = 1;// Etat de l'arbre qui est en feu
        static const unsigned m_KBrule = 2;   // Etat de l'arbre qui a été brulé

        CArbre(const unsigned i, const unsigned j, QPushButton * CelluleArbre) noexcept;

        unsigned getEtat() const noexcept;
        bool EstIntact() const noexcept;
        bool EstEnflamme() const noexcept;
        bool EstBrule() const noexcept;
        CArbre * getVoisin(const unsigned & Num_Voisin /* entre 1 et 4*/) const noexcept;
        std::pair<unsigned,unsigned> getPos() const throw();
        QPushButton * getCellule() const noexcept;
        void setEtat(const unsigned Etat) noexcept;
        void setVoisin(const unsigned & Num_Voisin /* entre 1 et 4*/, CArbre * ArbreVoisin) noexcept;
};

#endif // CARBRE_H

#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <QGridLayout>
#include <QCoreApplication>

#include "CForet.h"
#include "nsUtil.h"


typedef std::pair<unsigned,unsigned> PairUns;


CForet::CForet(const unsigned & Size, const double & Densite) noexcept
    :QGroupBox("Foret")
{
    GenereForet(Size, Densite);

    QGridLayout * layoutMatrice = new QGridLayout;
    layoutMatrice->setContentsMargins(0, 0, 0, 0);
    layoutMatrice->setSpacing(0);

    for(unsigned i(0); i < m_Size; ++i)
        for(unsigned j(0); j < m_Size; ++j)
        {
            layoutMatrice->addWidget(m_Foret[i][j], i, j);
        }
    setLayout(layoutMatrice);
}// CForet(Size, Densite)

//___Getters/Setters________________

void CForet::setDensite(const unsigned & Densite) noexcept
{
    m_Densite = Densite;
}//setDensite()


void CForet::setSize(const unsigned & Size) noexcept
{
    m_Size = Size;
}//setSize()


unsigned CForet::getSize() const noexcept
{
    return m_Size;
}//getSize()

CArbre * CForet::getArbre(unsigned Index)
{
    return &m_Arbres[Index];
}
//___________________________________



void CForet::GenereForet(const unsigned & Size, const float & Densite) noexcept
{
    m_Size = Size;
    m_Densite = Densite;

    // Dimensionne la matrice
    m_Foret.resize(m_Size);
    for(unsigned i(0); i < m_Size; ++i)
    {
        m_Foret[i].resize(m_Size);
    }

    // Nombre d'arbres à mettre dans la matrice
    unsigned NbArbres = m_Densite * (m_Size * m_Size);

    //reserve de l'espace en memoire pour le vecteur
    m_Arbres.reserve(NbArbres);

    // Initialisation de la matrice
    for (unsigned i = 0; i < m_Size; ++i)
        for(unsigned j = 0; j < m_Size; ++j)
            m_Foret[i][j] = new CCellule(this);


    //Insertion des arbres dans la matrice

    unsigned i; //Positions de l'arbre
    unsigned j; //dans la matrice

    for (;NbArbres > 0;)
    {
        i = nsUtil::Random(0,m_Size);
        j = nsUtil::Random(0,m_Size);

        if (m_Foret[i][j]->getArbre() == nullptr)
        {
            //On rempli le tableau des Arbres de la Foret
            m_Arbres.push_back(CArbre(i, j, m_Foret[i][j]));
            //On ajoute à la foret un arbre aux coordonnées (i,j)
            m_Foret[i][j]->setArbre(&m_Arbres[m_Arbres.size()-1]);
            --NbArbres;
        }
    }
}// GenereForet()

void CForet::Enflammer (CArbre * Arbre) noexcept
{
    Arbre->setEtat(CArbre::m_KEnflamme);
    Arbre->getCellule()->setStyleSheet("QPushButton { background-color: red; }");
}//Enflammer()




void CForet::PropagerIncendie() noexcept
{
    CCellule * CelluleSender = (CCellule *)sender();
    CArbre * PremierArbre = CelluleSender->getArbre();
    Enflammer(PremierArbre);
    m_ArbresEnFeu.push_back(PremierArbre);

    unsigned Cpt = 1;

    //Tant qu'il y a un arbre en feu ...
    while(!m_ArbresEnFeu.empty())
    {
        std::vector<CArbre *> NewTab; //Tableau des prochains arbres en feu

        //Pour chaque arbre en feu...
        for(unsigned i(0); i < m_ArbresEnFeu.size(); ++i)
        {
            TrouverVoisins(m_ArbresEnFeu[i]);
            //Pour chaque voisin de cet arbre en feu...
            for(unsigned j(1); j < 5; ++j)
            {
                if(!m_ArbresEnFeu[i]->getVoisin(j)) continue;

                Enflammer(m_ArbresEnFeu[i]->getVoisin(j));

                Cpt += 1; //compteur d'arbre +1

                //On ajoute ce voisin au nouveau tableau des arbres en feu
                NewTab.push_back(m_ArbresEnFeu[i]->getVoisin(j));
                //On retire ce voisin du tableau des voisins
                m_ArbresEnFeu[i]->setVoisin(j, nullptr);
            }
            //On change l'état de l'arbre qui est maintenant brulé
            m_ArbresEnFeu[i]->setEtat(CArbre::m_KBrule);
            m_ArbresEnFeu[i]->getCellule()->setStyleSheet("QPushButton { background-color: rgb(50,50,50); }");
        }
        m_ArbresEnFeu = NewTab;
        QCoreApplication::processEvents();
        Sleep(100);
    }
    std::cout << Cpt << std::endl;
}//PropagerIncendie()



void CForet::TrouverVoisins(CArbre * Arbre) noexcept
{
    PairUns Coord = Arbre->getPos();
    if (((int)Coord.first - 1) >= 0 && m_Foret[Coord.first - 1][Coord.second]->getArbre()
        && m_Foret[Coord.first - 1][Coord.second]->getArbre()->EstIntact())
    {
        Arbre->setVoisin(1, m_Foret[Coord.first - 1][Coord.second]->getArbre());
    }
    if (((int)Coord.second - 1) >= 0 && m_Foret[Coord.first][Coord.second - 1]->getArbre()
         && (m_Foret[Coord.first][Coord.second - 1])->getArbre()->EstIntact())
    {
        Arbre->setVoisin(2, m_Foret[Coord.first][Coord.second - 1]->getArbre());
    }

    if ((Coord.first + 1) < getSize() && m_Foret[Coord.first + 1][Coord.second]->getArbre()
         && m_Foret[Coord.first + 1][Coord.second]->getArbre()->EstIntact())
    {
        Arbre->setVoisin(3, m_Foret[Coord.first + 1][Coord.second]->getArbre());
    }

    if ((Coord.second + 1) < getSize() && m_Foret[Coord.first][Coord.second + 1]->getArbre()
         && m_Foret[Coord.first][Coord.second + 1]->getArbre()->EstIntact())
    {
        Arbre->setVoisin(4, m_Foret[Coord.first][Coord.second + 1]->getArbre());
    }
}//TrouverVoisins()

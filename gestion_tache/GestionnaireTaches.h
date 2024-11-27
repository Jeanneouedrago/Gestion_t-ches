#ifndef GESTIONNAIRETACHES_H
#define GESTIONNAIRETACHES_H

#include "Tache.h"
#include <vector>
#include <fstream>

class GestionnaireTaches {
private:
    std::vector<Tache> taches;
    int prochainId = 1;
    std::string fichierTaches = "taches.txt";

public:
    GestionnaireTaches();
    void ajouterTache();
    void modifierTache(int id);
    void supprimerTache(int id);
    void marquerTache(int id, Statut statut);
    void afficherTaches() const;
    void rechercherTache(const std::string& motCle) const;
    void afficherTachesParStatut() const;
    void sauvegarderTaches() const;
    void chargerTaches();
};

#endif // GESTIONNAIRETACHES_H

#ifndef TACHE_H
#define TACHE_H

#include <string>
#include <ctime>

enum Priorite { FAIBLE, MOYENNE, ELEVEE };
enum Statut { EN_COURS, TERMINEE };

struct Tache {
    int id;
    std::string titre;
    std::string description;
    Priorite priorite;
    time_t echeance;
    Statut statut;

    std::string getPrioriteStr() const;
    std::string getStatutStr() const;
    std::string getDateEcheanceStr() const;
};

#endif // TACHE_H

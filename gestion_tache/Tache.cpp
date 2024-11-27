#include "Tache.h"
#include <sstream>
#include <iomanip>

std::string Tache::getPrioriteStr() const {
    switch (priorite) {
        case FAIBLE: return "Faible";
        case MOYENNE: return "Moyenne";
        case ELEVEE: return "Elevée";
        default: return "Inconnue";
    }
}

std::string Tache::getStatutStr() const {
    return (statut == EN_COURS) ? "En cours" : "Terminée";
}

std::string Tache::getDateEcheanceStr() const {
    char buffer[20];
    strftime(buffer, 20, "%d-%m-%Y", localtime(&echeance));
    return std::string(buffer);
}

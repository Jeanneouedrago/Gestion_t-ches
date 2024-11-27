#include "GestionnaireTaches.h"
#include <iostream>
#include <algorithm>
#include <sstream>

GestionnaireTaches::GestionnaireTaches() {
    chargerTaches();
}

void GestionnaireTaches::ajouterTache() {
    Tache nouvelleTache;
    nouvelleTache.id = prochainId++;
    nouvelleTache.statut = EN_COURS;

    std::cout << "Titre de la tâche : ";
    std::cin.ignore();
    std::getline(std::cin, nouvelleTache.titre);

    std::cout << "Description de la tâche : ";
    std::getline(std::cin, nouvelleTache.description);

    int niveauPriorite;
    std::cout << "Priorité (0: Faible, 1: Moyenne, 2: Elevée) : ";
    std::cin >> niveauPriorite;
    if (niveauPriorite < 0 || niveauPriorite > 2) {
        std::cout << "Priorité invalide. Tâche non ajoutée.\n";
        return;
    }
    nouvelleTache.priorite = static_cast<Priorite>(niveauPriorite);

    int jour, mois, annee;
    std::cout << "Echéance (jour mois année) : ";
    std::cin >> jour >> mois >> annee;
    tm echeance = {0};
    echeance.tm_mday = jour;
    echeance.tm_mon = mois - 1;
    echeance.tm_year = annee - 1900;
    nouvelleTache.echeance = mktime(&echeance);

    taches.push_back(nouvelleTache);
    sauvegarderTaches();
    std::cout << "Tâche ajoutée avec succès !\n";
}

void GestionnaireTaches::modifierTache(int id) {
    for (auto &tache : taches) {
        if (tache.id == id) {
            std::cout << "Modifier le titre (" << tache.titre << ") : ";
            std::cin.ignore();
            std::getline(std::cin, tache.titre);

            std::cout << "Modifier la description : ";
            std::getline(std::cin, tache.description);

            int niveauPriorite;
            std::cout << "Modifier la priorité (0: Faible, 1: Moyenne, 2: Elevée) : ";
            std::cin >> niveauPriorite;
            if (niveauPriorite < 0 || niveauPriorite > 2) {
                std::cout << "Priorité invalide. Tâche non modifiée.\n";
                return;
            }
            tache.priorite = static_cast<Priorite>(niveauPriorite);

            int jour, mois, annee;
            std::cout << "Modifier l'échéance (jour mois année) : ";
            std::cin >> jour >> mois >> annee;
            tm echeance = {0};
            echeance.tm_mday = jour;
            echeance.tm_mon = mois - 1;
            echeance.tm_year = annee - 1900;
            tache.echeance = mktime(&echeance);

            sauvegarderTaches();
            std::cout << "Tâche modifiée avec succès !\n";
            return;
        }
    }
    std::cout << "Tâche non trouvée.\n";
}

void GestionnaireTaches::supprimerTache(int id) {
    auto it = std::remove_if(taches.begin(), taches.end(), [id](const Tache& t) { return t.id == id; });
    if (it != taches.end()) {
        taches.erase(it, taches.end());
        sauvegarderTaches();
        std::cout << "Tâche supprimée avec succès !\n";
    } else {
        std::cout << "Tâche non trouvée.\n";
    }
}

void GestionnaireTaches::marquerTache(int id, Statut statut) {
    for (auto &tache : taches) {
        if (tache.id == id) {
            tache.statut = statut;
            sauvegarderTaches();
            std::cout << "Statut de la tâche mis à jour avec succès !\n";
            return;
        }
    }
    std::cout << "Tâche non trouvée.\n";
}

void GestionnaireTaches::afficherTaches() const {
    for (const auto &tache : taches) {
        std::cout << "ID: " << tache.id << " | Titre: " << tache.titre << " | Priorité: " << tache.getPrioriteStr()
                  << " | Echéance: " << tache.getDateEcheanceStr() << " | Statut: " << tache.getStatutStr() << "\n";
    }
}

void GestionnaireTaches::rechercherTache(const std::string& motCle) const {
    for (const auto &tache : taches) {
        if (tache.titre.find(motCle) != std::string::npos || tache.description.find(motCle) != std::string::npos) {
            std::cout << "ID: " << tache.id << " | Titre: " << tache.titre << " | Description: " << tache.description
                      << " | Priorité: " << tache.getPrioriteStr() << " | Echéance: " << tache.getDateEcheanceStr()
                      << " | Statut: " << tache.getStatutStr() << "\n";
        }
    }
}

void GestionnaireTaches::afficherTachesParStatut() const {
    std::cout << "=== Tâches en cours ===\n";
    for (const auto &tache : taches) {
        if (tache.statut == EN_COURS) {
            std::cout << "ID: " << tache.id << " | Titre: " << tache.titre << " | Priorité: " << tache.getPrioriteStr()
                      << " | Echéance: " << tache.getDateEcheanceStr() << "\n";
        }
    }

    std::cout << "\n=== Tâches terminées ===\n";
    for (const auto &tache : taches) {
        if (tache.statut == TERMINEE) {
            std::cout << "ID: " << tache.id << " | Titre: " << tache.titre << " | Priorité: " << tache.getPrioriteStr()
                      << " | Echéance: " << tache.getDateEcheanceStr() << "\n";
        }
    }
}

void GestionnaireTaches::sauvegarderTaches() const {
    std::ofstream fichier(fichierTaches);
    if (fichier.is_open()) {
        for (const auto &tache : taches) {
            fichier << tache.id << " " << tache.titre << " " << tache.description << " "
                    << static_cast<int>(tache.priorite) << " " << tache.echeance << " "
                    << static_cast<int>(tache.statut) << "\n";
        }
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier pour sauvegarder les tâches.\n";
    }
}

void GestionnaireTaches::chargerTaches() {
    std::ifstream fichier(fichierTaches);
    if (fichier.is_open()) {
        Tache tache;
        std::string ligne;
        while (std::getline(fichier, ligne)) {
            std::istringstream iss(ligne);
            iss >> tache.id >> tache.titre >> tache.description;
            int priorite, statut;
            time_t echeance;
            iss >> priorite >> echeance >> statut;
            tache.priorite = static_cast<Priorite>(priorite);
            tache.echeance = echeance;
            tache.statut = static_cast<Statut>(statut);
            taches.push_back(tache);
            prochainId = std::max(prochainId, tache.id + 1);
        }
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier pour charger les tâches.\n";
    }
}

#include "GestionnaireTaches.h"
#include <iostream>

int main() {
    GestionnaireTaches gestionnaire;
    int choix, id;
    std::string motCle;

    while (true) {
        std::cout << "\n--- Menu ---\n"
                  << "1. Ajouter une tâche\n"
                  << "2. Modifier une tâche\n"
                  << "3. Supprimer une tâche\n"
                  << "4. Marquer une tâche comme terminée/en cours\n"
                  << "5. Afficher toutes les tâches\n"
                  << "6. Rechercher une tâche\n"
                  << "7. Afficher les tâches en cours et terminées\n"
                  << "0. Quitter\n"
                  << "Choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1:
                gestionnaire.ajouterTache();
                break;
            case 2:
                std::cout << "ID de la tâche à modifier: ";
                std::cin >> id;
                gestionnaire.modifierTache(id);
                break;
            case 3:
                std::cout << "ID de la tâche à supprimer: ";
                std::cin >> id;
                gestionnaire.supprimerTache(id);
                break;
            case 4:
                std::cout << "ID de la tâche à marquer: ";
                std::cin >> id;
                int statut;
                std::cout << "Statut (0: En cours, 1: Terminée): ";
                std::cin >> statut;
                gestionnaire.marquerTache(id, static_cast<Statut>(statut));
                break;
            case 5:
                gestionnaire.afficherTaches();
                break;
            case 6:
                std::cout << "Mot clé pour la recherche: ";
                std::cin.ignore();
                std::getline(std::cin, motCle);
                gestionnaire.rechercherTache(motCle);
                break;
            case 7:
                gestionnaire.afficherTachesParStatut();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Choix invalide.\n";
        }
    }
}

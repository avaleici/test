#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <fstream>

namespace fs = std::filesystem;

struct FileInfo {
    fs::path path;
    std::uintmax_t size;
};

void afficherInfoFichier(const FileInfo& fichier) {
    std::cout << std::setw(12) << fichier.size << " octets | " << fichier.path << '\n';
}

void rechercherTousLesFichiers(const fs::path& racine, std::vector<FileInfo>& tousLesFichiers, std::vector<fs::path>& fichiersCaches) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(racine)) {
            if (entry.is_regular_file()) {
                tousLesFichiers.push_back({ entry.path(), entry.file_size() });
                if (entry.path().filename().string().starts_with(".")) {
                    fichiersCaches.push_back(entry.path());
                }
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Erreur : " << ex.what() << '\n';
    }
}

void afficherPlusGrosFichiers(const std::vector<FileInfo>& tousLesFichiers, size_t count = 10) {
    std::vector<FileInfo> trie = tousLesFichiers;
    std::sort(trie.begin(), trie.end(), [](const FileInfo& a, const FileInfo& b) {
        return a.size > b.size;
    });

    std::cout << "\n=== Plus gros fichiers ===\n";
    for (size_t i = 0; i < std::min(count, trie.size()); ++i) {
        afficherInfoFichier(trie[i]);
    }
}

void afficherTousLesCheminsAbsolus(const std::vector<FileInfo>& tousLesFichiers) {
    std::cout << "\n=== Tous les chemins absolus ===\n";
    for (const auto& fichier : tousLesFichiers) {
        std::cout << fs::absolute(fichier.path) << '\n';
    }
}

void supprimerFichiersCaches(std::vector<fs::path>& fichiersCaches) {
    if (fichiersCaches.empty()) {
        std::cout << "Aucun fichier caché trouvé.\n";
        return;
    }

    std::cout << "\n=== Fichiers cachés ===\n";
    for (const auto& chemin : fichiersCaches) {
        std::cout << chemin << '\n';
    }

    char choix;
    std::cout << "\nSupprimer ces fichiers cachés ? (y/n) : ";
    std::cin >> choix;

    if (choix == 'y' || choix == 'Y') {
        for (const auto& chemin : fichiersCaches) {
            try {
                fs::remove(chemin);
                std::cout << "Supprimé : " << chemin << '\n';
            } catch (...) {
                std::cerr << "Échec de la suppression : " << chemin << '\n';
            }
        }
    } else {
        std::cout << "Suppression annulée.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Utilisation : ./drive_util <chemin>\n";
        return 1;
    }

    fs::path racine(argv[1]);
    if (!fs::exists(racine) || !fs::is_directory(racine)) {
        std::cerr << "Chemin invalide.\n";
        return 1;
    }

    std::vector<FileInfo> tousLesFichiers;
    std::vector<fs::path> fichiersCaches;

    rechercherTousLesFichiers(racine, tousLesFichiers, fichiersCaches);
    afficherPlusGrosFichiers(tousLesFichiers);
    afficherTousLesCheminsAbsolus(tousLesFichiers);
    supprimerFichiersCaches(fichiersCaches);

    std::cout << "\nAnalyse du disque terminée.\n";
    return 0;
}

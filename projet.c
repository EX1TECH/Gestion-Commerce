#include <stdio.h>
#include <string.h>

//Constantes

#define MAX_PRODUCTS 100 // Définir le nombre maximal de produits pouvant être gérés
#define MAX_SALES 100    // Définir le nombre maximal de ventes pouvant être enregistrées
#define MAX_CLIENTS 100 // Définir le nombre maximal de clients pouvant être gérés
#define MAX_SUPPLIERS 100      // Définir le nombre maximal de fournisseurs pouvant être gérés
#define MAX_ORDERS_PER_SUPPLIER 50 // Définir le nombre maximal de commandes par fournisseur
#define MAX_FOURNISSEURS 100 // Définir le nombre maximal de fournisseurs pouvant être gérés

// Définition des structures pour chaque acteur du système

// Structure représentant un produit
typedef struct {
    int id;
    char nom[50];
    double prix;
    int quantite;
    int disponible; // Indicateur pour savoir si le produit est actif (1) ou supprimé (0)
} Produit;


typedef struct {
    int id;
    char nom[50];
    char adresse[100];
    int nbCommandes;  // Ajout du nombre de commandes
    // Tableau de commandes
    struct {
        int idProduit;
        int quantite;
        double montantTotal;
        int livree;
    } commandes[MAX_ORDERS_PER_SUPPLIER];
} Fournisseur;Fournisseur;

// Structure représentant un client
typedef struct {
    int id;
    char nom[50];
    char email[100];
    double totalAchats;
} Client;

// Structure représentant une commande passée à un fournisseur
typedef struct {
    int idFournisseur;
    int idProduit;
    int quantite;
    double montantTotal;
    int livree; // Indicateur pour savoir si la commande a été livrée (1) ou non (0)
} Commande;

// Structure représentant une vente
typedef struct {
    int idClient;
    int idProduit;
    int quantite;
    double montantTotal;
} Vente;

//Variables globales

Produit produits[MAX_PRODUCTS];
int nbProduits = 0;

Fournisseur fournisseurs[MAX_SUPPLIERS];
int nbFournisseurs = 0;

Client clients[MAX_CLIENTS];
int nbClients = 0;

Vente ventes[MAX_SALES];
int nbVentes = 0;

Commande commandes[MAX_ORDERS_PER_SUPPLIER * MAX_SUPPLIERS];
int nbCommandes = 0;

// Fonctions pour les actions des acteurs du système

// Fonction pour afficher les détails d'un produit
void afficherProduit(int idProduit) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == idProduit && produits[i].disponible) {
            printf("ID: %d\n", produits[i].id);
            printf("Nom: %s\n", produits[i].nom);
            printf("Prix: %.2f\n", produits[i].prix); //.2f : 2 chiffres apres la virgule
            printf("Quantité en stock: %d\n", produits[i].quantite);
            return;  // Sortir de la fonction après avoir affiché les détails du produit
        }
    }
    printf("Produit non trouvé ou indisponible.\n");
}


// Fonction pour afficher les détails d'un fournisseur
void afficherFournisseur(int idFournisseur) {
    for (int i = 0; i < nbFournisseurs; i++) {
        if (fournisseurs[i].id == idFournisseur) {
            printf("ID: %d\n", fournisseurs[i].id);
            printf("Nom: %s\n", fournisseurs[i].nom);
            printf("Adresse: %s\n", fournisseurs[i].adresse);
            return;  // Sortir de la fonction après avoir affiché les détails du fournisseur
        }
    }
    printf("Fournisseur non trouvé.\n");
}

// Fonction pour afficher tous les fournisseurs
void afficherFournisseurs() {
    printf("Liste des fournisseurs :\n");
    for (int i = 0; i < nbFournisseurs; i++) {
        printf("ID: %d | Nom: %s | Adresse: %s\n", fournisseurs[i].id, fournisseurs[i].nom, fournisseurs[i].adresse);
    }
}


// Fonction pour ajouter un nouveau produit
void ajouterProduit(Produit produits[], int *nbProduits) {
    if (*nbProduits < MAX_PRODUCTS) {
        Produit nouveauProduit;

        // Saisie des informations du nouveau produit
        printf("Entrez l'ID du produit : ");
        scanf("%d", &nouveauProduit.id);
        printf("Entrez le nom du produit : ");
        scanf(" %[^\n]", nouveauProduit.nom); //%[^\n] : scanf() lit jusqu'à a fin de ligne
        printf("Entrez le prix du produit : ");
        scanf("%lf", &nouveauProduit.prix);
        printf("Entrez la quantité en stock du produit : ");
        scanf("%d", &nouveauProduit.quantite);

        // Marquer le produit comme disponible
        nouveauProduit.disponible = 1;

        // Ajouter le nouveau produit au tableau
        produits[*nbProduits] = nouveauProduit;
        (*nbProduits)++;

        printf("Le produit a été ajouté avec succès.\n");
    } else {
        printf("Impossible d'ajouter un nouveau produit. Nombre maximal de produits atteint.\n");
    }
}

// Fonction pour afficher tous les produits disponibles
void afficherProduits(Produit produits[], int nbProduits) {
    printf("Liste des produits :\n");
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].disponible) {
            printf("ID: %d | Nom: %s | Prix: %.2f | Quantité en stock: %d\n",
                   produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite);
        }
    }
}

// Fonction pour afficher tous les clients enregistrés
void afficherClients(Client clients[], int nbClients) {
    printf("Liste des clients :\n");
    for (int i = 0; i < nbClients; i++) {
        printf("ID: %d | Nom: %s | Email: %s | Total des achats: %.2f\n",
               clients[i].id, clients[i].nom, clients[i].email, clients[i].totalAchats);
    }
}

// Fonction pour supprimer un produit par son ID
void supprimerProduit(Produit produits[], int *nbProduits, int id) {
    for (int i = 0; i < *nbProduits; i++) {
        if (produits[i].id == id && produits[i].disponible) {
            produits[i].disponible = 0; // Marquer le produit comme supprimé
            printf("Le produit avec l'ID %d a été supprimé avec succès.\n", id);
            return;
        }
    }
    printf("Produit non trouvé ou déjà supprimé.\n");
}



// Fonction pour enregistrer une vente avec l'ID du client
void enregistrerVente(int idProduit, int quantite, int idClient) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == idProduit && produits[i].disponible) {
            if (produits[i].quantite >= quantite) {
                // Mettre à jour la quantité en stock
                produits[i].quantite -= quantite;

                // Calculer le montant total de la vente
                double montantTotal = quantite * produits[i].prix;

                // Enregistrer la vente avec l'ID du client
                ventes[nbVentes].idClient = idClient; // Enregistrer l'ID du client
                ventes[nbVentes].idProduit = idProduit;
                ventes[nbVentes].quantite = quantite;
                ventes[nbVentes].montantTotal = montantTotal;
                nbVentes++;

                // Mettre à jour le total des achats du client
                mettreAJourTotalAchats(idClient, montantTotal);

                printf("Vente enregistrée avec succès pour le client %d.\n", idClient);
                return;
            } else {
                printf("Quantité insuffisante en stock pour effectuer la vente.\n");
                return;
            }
        }
    }
    printf("Produit non trouvé ou indisponible.\n");
}

// Fonction pour afficher l'historique des ventes pour un client spécifique
void afficherHistoriqueVentesParClient(int idClient) {
    printf("Historique des ventes pour le client %d :\n", idClient);
    for (int i = 0; i < nbVentes; i++) {
        if (ventes[i].idClient == idClient) {
            printf("ID Produit: %d | Quantité vendue: %d | Montant total: %.2f\n",
                   ventes[i].idProduit, ventes[i].quantite, ventes[i].montantTotal);
        }
    }
}




// Fonction pour enregistrer un nouveau client
void enregistrerNouveauClient() {
    if (nbClients < MAX_CLIENTS) {
        Client nouveauClient;

        // Saisie des informations du nouveau client
        printf("Entrez l'ID du client : ");
        scanf("%d", &nouveauClient.id);
        printf("Entrez le nom du client : ");
        scanf(" %[^\n]", nouveauClient.nom);
        printf("Entrez l'email du client : ");
        scanf(" %[^\n]", nouveauClient.email);

        // Initialiser le total des achats à 0 pour le nouveau client
        nouveauClient.totalAchats = 0.0;

        // Ajouter le nouveau client à la liste des clients
        clients[nbClients] = nouveauClient;
        nbClients++;

        printf("Le client a été enregistré avec succès.\n");
    } else {
        printf("Impossible d'ajouter un nouveau client. Nombre maximal de clients atteint.\n");
    }
}

// Fonction pour ajouter un nouveau fournisseur
void ajouterNouveauFournisseur() {
    if (nbFournisseurs < MAX_SUPPLIERS) {
        Fournisseur nouveauFournisseur;

        // Saisie des informations du nouveau fournisseur
        printf("Entrez l'ID du fournisseur : ");
        scanf("%d", &nouveauFournisseur.id);
        printf("Entrez le nom du fournisseur : ");
        scanf(" %[^\n]", nouveauFournisseur.nom);
        printf("Entrez l'adresse du fournisseur : ");
        scanf(" %[^\n]", nouveauFournisseur.adresse);

        // Initialiser le nombre de commandes à 0 pour le nouveau fournisseur
        nouveauFournisseur.nbCommandes = 0;

        // Ajouter le nouveau fournisseur à la liste des fournisseurs
        fournisseurs[nbFournisseurs] = nouveauFournisseur;
        nbFournisseurs++;

        printf("Le fournisseur a été ajouté avec succès.\n");
    } else {
        printf("Impossible d'ajouter un nouveau fournisseur. Nombre maximal de fournisseurs atteint.\n");
    }
}

// Fonction pour supprimer un fournisseur

void supprimerFournisseur(int idFournisseur) {
    for (int i = 0; i < nbFournisseurs; i++) {
        if (fournisseurs[i].id == idFournisseur) {
            for (int j = i; j < nbFournisseurs - 1; j++) {
                fournisseurs[j] = fournisseurs[j + 1];
            }
            nbFournisseurs--;
            printf("Fournisseur supprimé avec succès.\n");
            return;
        }
    }
    printf("Fournisseur non trouvé.\n");
}

void supprimerClient(int idClient) {
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].id == idClient) {
            for (int j = i; j < nbClients - 1; j++) {
                clients[j] = clients[j + 1];
            }
            nbClients--;
            printf("Client supprimé avec succès.\n");
            return;
        }
    }
    printf("Client non trouvé.\n");
}


// Fonction pour afficher les informations d'un client par son ID
void afficherInformationsClient(int idClient) {
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].id == idClient) {
            printf("Informations du client :\n");
            printf("ID: %d\n", clients[i].id);
            printf("Nom: %s\n", clients[i].nom);
            printf("Email: %s\n", clients[i].email);
            printf("Total des achats: %.2f\n", clients[i].totalAchats);
            afficherHistoriqueVentesParClient(idClient);
            return;
        }
    }
    printf("Client non trouvé.\n");
}

// Fonction pour mettre à jour le total des achats d'un client
void mettreAJourTotalAchats(int idClient, double montantAchat) {
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].id == idClient) {
            clients[i].totalAchats += montantAchat;
            printf("Total des achats mis à jour pour le client %d.\n", idClient);
            return;
        }
    }
    printf("Client non trouvé.\n");
}

// Fonction pour effectuer un réapprovisionnement (commande) auprès d'un fournisseur pour un produit donné
void effectuerReapprovisionnement(int idFournisseur, int idProduit, int quantite) {
    // Vérifier si le fournisseur existe
    int fournisseurExiste = 0;
    for (int i = 0; i < nbFournisseurs; i++) {
        if (fournisseurs[i].id == idFournisseur) {
            fournisseurExiste = 1;
            break;
        }
    }

    if (!fournisseurExiste) {
        printf("Fournisseur non trouvé.\n");
        return;
    }

    // Vérifier si le produit existe et est disponible
    Produit *produitReapprovisionne = NULL;
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == idProduit && produits[i].disponible) {
            produitReapprovisionne = &produits[i];
            break;
        }
    }

    if (produitReapprovisionne == NULL) {
        printf("Produit non trouvé ou indisponible.\n");
        return;
    }

    // Créer une nouvelle commande
    if (nbCommandes < MAX_ORDERS_PER_SUPPLIER * MAX_SUPPLIERS) {
        Commande nouvelleCommande;
        nouvelleCommande.idFournisseur = idFournisseur;
        nouvelleCommande.idProduit = idProduit;
        nouvelleCommande.quantite = quantite;
        nouvelleCommande.montantTotal = quantite * produitReapprovisionne->prix;
        nouvelleCommande.livree = 0; // La commande n'est pas encore livrée

        // Ajouter la commande à la liste des commandes
        commandes[nbCommandes] = nouvelleCommande;
        nbCommandes++;

        printf("Commande enregistrée avec succès auprès du fournisseur %d pour le produit %d.\n", idFournisseur, idProduit);

        // Mettre à jour la quantité en stock du produit
        produitReapprovisionne->quantite += quantite; // Ajouter la quantité à la quantité en stock
    } else {
        printf("Impossible d'effectuer la commande. Nombre maximal de commandes atteint.\n");
    }
}

// Fonction pour consulter les commandes par fournisseur
void consulterCommandesParFournisseur(int idFournisseur) {
    int commandeTrouvee = 0;

    printf("Liste des commandes pour le fournisseur avec l'ID %d :\n", idFournisseur);

    // Parcourir toutes les commandes pour trouver celles du fournisseur spécifié
    for (int i = 0; i < nbCommandes; i++) {
        if (commandes[i].idFournisseur == idFournisseur) {
            // Si c'est la première commande trouvée, afficher l'en-tête
            if (!commandeTrouvee) {
                printf("ID Fournisseur | ID Produit | Quantité | Montant Total | Livrée\n");
                printf("---------------------------------------------\n");
                commandeTrouvee = 1;
            }

            // Afficher les détails de la commande
            printf("%d | %d | %d | %.2f | %s\n", commandes[i].idFournisseur,
                   commandes[i].idProduit, commandes[i].quantite,
                   commandes[i].montantTotal, (commandes[i].livree == 1 ? "Oui" : "Non"));
        }
    }

    // Si aucune commande n'a été trouvée pour ce fournisseur, afficher un message approprié
    if (!commandeTrouvee) {
        printf("Aucune commande trouvée pour ce fournisseur.\n");
    }
}



//Fonctions de sauvegarde/chargement

void sauvegarderProduits(Produit produits[], int nbProduits) {
    FILE *fichierProduits = fopen("produits.dat", "w");
    if (fichierProduits == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt.\n");
        return;
    }

    for (int i = 0; i < nbProduits; i++) {
       fprintf(fichierProduits, "%d,%s,%.2f,%d,%d\n",
        produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].disponible);
    }

    fclose(fichierProduits);
}


void chargerProduits(Produit produits[], int *nbProduits) {
    FILE *fichierProduits = fopen("produits.dat", "r");
    if (fichierProduits == NULL) {
        printf("Le fichier produits.txt n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    *nbProduits = 0;
    while (fscanf(fichierProduits, "%d,%[^,],%lf,%d,%d\n",
                  &produits[*nbProduits].id, produits[*nbProduits].nom,
                  &produits[*nbProduits].prix, &produits[*nbProduits].quantite,
                  &produits[*nbProduits].disponible) == 5) {
        (*nbProduits)++;
    }

    fclose(fichierProduits);
}

void sauvegarderClients(Client clients[], int nbClients) {
    FILE *fichierClients = fopen("clients.dat", "w");
    if (fichierClients == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt.\n");
        return;
    }

    for (int i = 0; i < nbClients; i++) {
        fprintf(fichierClients, "%d,%s,%s,%.2f\n",
                clients[i].id, clients[i].nom, clients[i].email, clients[i].totalAchats);
    }

    fclose(fichierClients);
}

void chargerClients(Client clients[], int *nbClients) {
    FILE *fichierClients = fopen("clients.dat", "r");
    if (fichierClients == NULL) {
        printf("Le fichier clients.txt n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    *nbClients = 0;
    while (fscanf(fichierClients, "%d,%[^,],%[^,],%lf\n",
                  &clients[*nbClients].id, clients[*nbClients].nom,
                  clients[*nbClients].email, &clients[*nbClients].totalAchats) == 4) {
        (*nbClients)++;
    }

    fclose(fichierClients);
}

void sauvegarderVentes(Vente ventes[], int nbVentes) {
    FILE *fichierVentes = fopen("ventes.dat", "w");
    if (fichierVentes == NULL) {
        printf("Erreur lors de l'ouverture du fichier ventes.txt.\n");
        return;
    }

    for (int i = 0; i < nbVentes; i++) {
        fprintf(fichierVentes, "%d,%d,%d,%.2f\n",
                ventes[i].idClient, ventes[i].idProduit, ventes[i].quantite, ventes[i].montantTotal);
    }

    fclose(fichierVentes);
}

void chargerVentes(Vente ventes[], int *nbVentes) {
    FILE *fichierVentes = fopen("ventes.dat", "r");
    if (fichierVentes == NULL) {
        printf("Le fichier ventes.txt n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    *nbVentes = 0;
    while (fscanf(fichierVentes, "%d,%d,%d,%lf\n",
                &ventes[*nbVentes].idClient,&ventes[*nbVentes].idProduit, &ventes[*nbVentes].quantite,
                &ventes[*nbVentes].montantTotal) == 4) {
        (*nbVentes)++;
    }

    fclose(fichierVentes);
}

void sauvegarderFournisseurs(Fournisseur fournisseurs[], int nbFournisseurs) {
    FILE *fichierFournisseurs = fopen("fournisseurs.dat", "w");
    if (fichierFournisseurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier fournisseurs.txt.\n");
        return;
    }

    for (int i = 0; i < nbFournisseurs; i++) {
        fprintf(fichierFournisseurs, "%d,%s,%s\n",
                fournisseurs[i].id, fournisseurs[i].nom, fournisseurs[i].adresse);
    }

    fclose(fichierFournisseurs);
}

void chargerFournisseurs(Fournisseur fournisseurs[], int *nbFournisseurs) {
    FILE *fichierFournisseurs = fopen("fournisseurs.dat", "r");
    if (fichierFournisseurs == NULL) {
        printf("Le fichier fournisseurs.txt n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    *nbFournisseurs = 0;
    while (fscanf(fichierFournisseurs, "%d,%[^,],%[^\n]\n",
                  &fournisseurs[*nbFournisseurs].id, fournisseurs[*nbFournisseurs].nom,
                  fournisseurs[*nbFournisseurs].adresse) == 3) {
        (*nbFournisseurs)++;
    }

    fclose(fichierFournisseurs);
}

void sauvegarderCommandes(Commande commandes[], int nbCommandes) {
    FILE *fichierCommandes = fopen("commandes.dat", "w");
    if (fichierCommandes == NULL) {
        printf("Erreur lors de l'ouverture du fichier commandes.dat.\n");
        return;
    }

    for (int i = 0; i < nbCommandes; i++) {
        fprintf(fichierCommandes, "%d,%d,%.2f,%d,%d\n",
                commandes[i].idFournisseur, commandes[i].idProduit,
                commandes[i].quantite, commandes[i].montantTotal, commandes[i].livree);
    }

    fclose(fichierCommandes);
}

void chargerCommandes(Commande commandes[], int *nbCommandes) {
    FILE *fichierCommandes = fopen("commandes.dat", "r");
    if (fichierCommandes == NULL) {
        printf("Le fichier commandes.dat n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    *nbCommandes = 0;
    while (*nbCommandes < MAX_ORDERS_PER_SUPPLIER * MAX_SUPPLIERS && // Controler le nombre de commandes
           fscanf(fichierCommandes, "%d,%d,%lf,%d,%d\n",
                  &commandes[*nbCommandes].idFournisseur, &commandes[*nbCommandes].idProduit,
                  &commandes[*nbCommandes].quantite, &commandes[*nbCommandes].montantTotal,
                  &commandes[*nbCommandes].livree) == 5) {
        (*nbCommandes)++;
    }

    fclose(fichierCommandes);

}


// Programme principal
int main() {
    
    int choixPrincipal;
    int idasupp;
    int idProd, quant, idClientachat;

    //Chargement des données

    chargerProduits(produits, &nbProduits);
    chargerClients(clients, &nbClients);
    chargerVentes(ventes, &nbVentes);
    chargerFournisseurs(fournisseurs, &nbFournisseurs);
    chargerCommandes(commandes, &nbCommandes);


 do {
        printf("\nMenu Principal :\n");
        printf("1. Menu Gestionnaire\n");
        printf("2. Menu Client\n");
        printf("3. Menu Fournisseur\n");
        printf("4. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choixPrincipal);

        switch (choixPrincipal) {
            case 1:
                //Authentification pour acceder aux actions du gestionnaire : mot de passe
                char motdepasse[20];
                printf("Entrez le mot de passe : ");
                scanf("%s", motdepasse);
                if (strcmp(motdepasse, "gestionnaire") != 0) { //
                    printf("Mot de passe incorrect.\n");
                    break;
                }
                // Sous menu de gestion gestionnaire
                int choixProduits;
                int idfourniiseursupp;
                int idClientasupp;
                do {
                    printf("\nMenu Gestionnaire :\n");
                    printf("1. Ajouter un produit\n");
                    printf("2. Afficher les produits\n");
                    printf("3. Supprimer un produit\n");
                    printf("4. Ajouter un fournisseur\n");
                    printf("5. Supprimer un fournisseur\n");
                    printf("6. Supprimer un client \n");
                    printf("7. Retour au menu principal\n");
                    printf("Choix : ");
                    scanf("%d", &choixProduits);

                    switch (choixProduits) {
                        case 1:
                            ajouterProduit(produits, &nbProduits);
                            break;
                        case 2:
                            afficherProduits(produits, nbProduits);
                            break;
                        case 3:
                            afficherProduits(produits, nbProduits);
                            printf("Id du produit a supprimer ?\n");
                            scanf("%d", &idasupp);
                            supprimerProduit(produits, &nbProduits, idasupp);
                            break;
                        case 4:
                            ajouterNouveauFournisseur();
                            break;

                        case 5:
                            afficherFournisseurs();
                            printf("Id du fournisseur a supprimer ?\n");
                            scanf("%d", &idfourniiseursupp);
                            supprimerFournisseur(idfourniiseursupp);
                            break;
                        case 6:
                            printf("Id du client a supprimer\n");
                            scanf("%d", &idClientasupp);
                            supprimerClient(idClientasupp); 
                            break;
                        case 7:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }
                } while (choixProduits != 7);
                break;

            case 2:
                // Sous-menu pour la gestion des clients
                int choixClients;
                int idinfo;
                do {
                    printf("\nMenu clients :\n");
                    printf("1. Ajouter un client\n");
                    printf("2. Afficher les clients\n");
                    printf("3. Acheter un produit\n");
                    printf("4. Infos de profil\n");
                    printf("5. Retour au menu principal\n");
                    printf("Choix : ");
                    scanf("%d", &choixClients);

                    switch (choixClients) {
                        case 1:
                            enregistrerNouveauClient();
                            break;
                        case 2:
                            afficherClients(clients, nbClients);
                            break;
                        case 3:
                            afficherProduits(produits, nbProduits);
                            printf("Entrez l'ID du produit : \n");
                            scanf("%d", &idProd);
                            printf("Entrez la quantité à vendre : \n");
                            scanf("%d", &quant);
                            printf("Entrez l'ID du client : \n");
                            scanf("%d", &idClientachat);
                            enregistrerVente(idProd, quant, idClientachat);
                            break;
                        case 4:
                            printf("Entrez l'ID du client : \n");
                            scanf("%d", &idinfo);
                            afficherInformationsClient(idinfo);
                            break;
                        case 5:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }
                } while (choixClients != 5);
                break;

            case 3:
                // Sous-menu pour la gestion des fournisseurs
                int choixFournisseurs;
                int idaffichfournisseur;
                int idFournisseurstock, idProduitstock, quantitestock;

                do {
                    printf("\nMenu fournisseurs :\n");
                    printf("1. Afficher les fournisseurs\n");
                    printf("2. Remise en stock\n");
                    printf("3. Voir les commandes par fournisseur\n");
                    printf("4. Retour au menu principal\n");
                    printf("Choix : ");
                    scanf("%d", &choixFournisseurs);

                    switch (choixFournisseurs) {
                        case 1:
                            afficherFournisseurs();
                            break;
                        case 2:
                            afficherFournisseurs();
                            printf("Entrez l'ID du fournisseur pour le réapprovisionnement : \n");
                            scanf("%d", &idFournisseurstock);
                            afficherProduits(produits, nbProduits);
                            printf("Entrez l'ID du produit à réapprovisionner : \n");
                            scanf("%d", &idProduitstock);
                            printf("Entrez la quantité à réapprovisionner : \n");
                            scanf("%d", &quantitestock);
                            effectuerReapprovisionnement(idFournisseurstock, idProduitstock, quantitestock);
                            break;
                        case 3:
                            afficherFournisseurs();
                            printf("Entrez l'ID du fournisseur pour consulter les commandes : ");
                            scanf("%d", &idaffichfournisseur);
                            consulterCommandesParFournisseur(idaffichfournisseur);
                            break;
                        case 4:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }
                } while (choixFournisseurs != 4);
                break;

            case 4:
                printf("Au revoir !\n");
                sauvegarderProduits(produits, nbProduits);
                sauvegarderClients(clients, nbClients);
                sauvegarderVentes(ventes, nbVentes);
                sauvegarderFournisseurs(fournisseurs, nbFournisseurs);
                sauvegarderCommandes(commandes, nbCommandes);
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choixPrincipal != 4);

    return 0;
}

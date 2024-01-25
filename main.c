#include<stdio.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
int  nbl ;
int N=5 ;
char * SaisirLigneFichier(FILE * pf){
    int c ;
    nbl = 0 ;
    char * ch = NULL ;
    while(((c = fgetc(pf)) != '\n') && (c != EOF)){
        ch = realloc(ch, (nbl + 1) * sizeof(char));
        ch[nbl++] =(char)c ;//
    }
    if((nbl > 0) || (c == '\n')){
        ch = realloc(ch, (nbl + 1) * sizeof(char));
        ch[nbl] = '\0' ;
        return ch ;
    }
    return NULL ;
}
char ** CreerVecteur(char *nf , int * taille){
    FILE * pf = fopen(nf, "r") ;
    char * str = NULL ;
    unsigned int i = 0 ;
    char ** VN = NULL ;
    if(pf == NULL){
        printf("\n probleme lors de l ouverture du fichier %s\n", nf) ;
        fclose(pf) ;
        *taille = 0 ;
        exit(-1);
        return NULL ;
    }
    while((str = SaisirLigneFichier(pf)) != NULL) {
        VN = realloc(VN, (i+1)*sizeof(char*)) ;
        VN[i++] = str ;
    }
    fclose(pf) ;
    *taille = i ;//
    return VN ;
}
char **str_split (char *s, const char *ct){
    char **tab = NULL;
    if (s != NULL && ct != NULL){
        int i;
        char *cs = NULL;
        size_t size = 1;
        for (i = 0; (cs = strtok (s, ct)); i++){
            if (size <= i + 1){
                void *tmp = NULL;
                size <<= 1;
                tmp = realloc (tab, sizeof (*tab) * size);
                if (tmp != NULL)tab = tmp;
                else{
                    fprintf (stderr, "Memoire insuffisante\n");
                    free (tab);
                    tab = NULL;
                    exit (1);
                }
            }
            tab[i] = cs;
            s = NULL;
        }
        tab[i] = NULL;
    }
    return tab;
}
struct element {
    char* Cle_primaire ;
    char *Colonne1 ;
    char *colonne2;
    char * colonne3 ;
    char * colonne4;
    struct element *suivant ;  } ;
typedef struct element Table ;
Table *inserer_tete(Table *Ligne_ini, char * Z[N]){
    Table *nv_ligne=NULL;
    nv_ligne=(Table*)malloc(sizeof(Table));
    nv_ligne-> Cle_primaire =Z[0];
    nv_ligne->Colonne1=Z[1];
    nv_ligne->colonne2=Z[2];
    nv_ligne->colonne3=Z[3];
    nv_ligne->colonne4=Z[4];
    nv_ligne->suivant=Ligne_ini;
    Ligne_ini=nv_ligne;
    return Ligne_ini;                    }
void  afficher_liste(Table *Ligne_ini){
    Table *Ligne= Ligne_ini;
    if(Ligne == NULL){
        printf("la liste est vide\n");
        exit(-1);
    }
    int k=0;
    while(Ligne != NULL){
        printf("\t %s", Ligne->Cle_primaire);
        printf("\t %s", Ligne->Colonne1);
        printf("\t \t %s", Ligne->colonne2);
        printf("\t \t %s", Ligne->colonne3);
        if(Ligne->colonne4==NULL)k++;
        if(k==0)printf("\t \t %s", Ligne->colonne4);
        Ligne=Ligne->suivant;
        printf("\n");
    }
}
int rechercher_cl(char *File_name,int cle){
    char ** TL = CreerVecteur(File_name, &nbl) ;
    char **tab,*ptr;
    int cle_primaire,j;
    for (j = 1; j <nbl ; j++) {
        tab = str_split(TL[j], ",");
        cle_primaire=strtol(tab[0],&ptr,10) ;
        if(cle==cle_primaire)return j ;
    }
    return 0 ;
}
void FICHIER_addLigne( char* nom,int ligne){
    FILE* fichier = fopen(nom,"a");
    char ** TL = CreerVecteur(nom, &nbl) ;
    char **tab = str_split(TL[0], ",");
    char colonne0[20],colonne1[20],colonne2[20],colonne3[20],colonne4[20];
    int cle_primaire ,etat,i=-1;
    char *ptr;
    printf("\n\n\t\tDonner %s :  ",tab[0]);
    do {
        i++;
        if(i!=0)printf("ce cle existe deja !\nEntrer un Cle primaire Valable !\n");
        scanf("%s", colonne0);
        cle_primaire = strtol(colonne0, &ptr, 10);
        etat= rechercher_cl(nom,cle_primaire);
        if (etat ==0)break;
    } while (1);
    printf("\n\n\t\tDonner %s :  ",tab[1]);
    scanf("%s",colonne1);
    printf("\n\n\t\tDonner %s :  ",tab[2]);
    scanf("%s",colonne2);
    printf("\n\n\t\tDonner %s :  ",tab[3]);
    scanf("%s",colonne3);
    if((strcmp(nom,"Tappartement.txt")==0)||strcmp(nom,"Trecu.txt")==0){
        printf("\nDonner %s:  ",tab[4]);
        scanf("%s",colonne4);}
    fprintf(fichier,"\n%s,%s,%s,%s,%s",colonne0,colonne1,colonne2,colonne3,colonne4);
    fclose(fichier);
}
void afficher_Table(char *Filename){
    char ** TL = CreerVecteur(Filename, &nbl) ;
    char **tab;
    Table *tete = NULL;
    int i;
    for ( i = nbl-1; i >=0 ; i--) {
        tab = str_split(TL[i], ",");
        tete = inserer_tete(tete,tab); }
    printf("\n\n\t\tVoici la table %s \n",Filename);
    afficher_liste(tete);
}
void SupprimerLigne(char *File_name)
{
    FILE *TF;
    TF= fopen("new_file.txt","a") ;
    if(TF == NULL)
    {
        printf("Impossible d'ouvrire le fihier\n") ;
        exit(1) ;
    }
    printf("\n\n\t\tDonner le cle primaire de ligne a supprimer \n") ;
    int id,j,i=0, cle_primaire = 0;
    scanf("%d",&id) ;
    char ** TL = CreerVecteur(File_name, &nbl) ;
    char **tab ;char *ptr;
    printf("%d\n",nbl);
    int pos= rechercher_cl(File_name,id); ;
    for (j = 0; j <nbl ; j++)
    {
        tab= str_split(TL[j], ",");
        if(tab[4]==NULL)tab[4]="";
        if(j!=0) cle_primaire=strtol(tab[0],&ptr,10) ;
        if(cle_primaire!=id)
        {
            if((j==pos-1)&&(pos==nbl-1) )
            {
                fprintf(TF,"%s,%s,%s,%s,%s",tab[0],tab[1],tab[2],tab[3],tab[4]);
                break;
            }
            else
            {
                fprintf(TF,"%s,%s,%s,%s,%s",tab[0],tab[1],tab[2],tab[3],tab[4]);
                if((j!=(nbl-1)))fprintf(TF,"\n");
            }
        }
        else i++;
    }
    fclose(TF) ;
    remove(File_name) ;
    rename("new_file.txt",File_name) ;
    if(i == 0)
    {
        printf("Le cle primaire  n'existe pas \n ") ;
    }
    else
    {
        printf("le ligne du cle primaire %d a ete supprimer \n",id);
    }

}
void modifierLigne(char *File_name)
{
    int choix;
    FILE *TF;
    TF= fopen("new_file.txt","a") ;
    if(TF == NULL){     printf("Impossible d'ouvrire le fihier\n") ;
        exit(1) ;
    }
    printf("Donner le cle primaire de ligne a modifier \n") ;
    int id , cle_primaire = 0,k=0;
    scanf("%d",&id) ;
    char ** TL = CreerVecteur(File_name, &nbl) ;
    char *ptr;
    char *virgule=",";
    char *nc_0,*n_c1,*n_c2,*n_c3,*n_c4;int j;
    for (j = 0; j <nbl ; j++){
        char **tab= str_split(TL[j], ",");
        if(tab[4]==NULL){
            tab[4]="";
            virgule="";
            k++;
        }
        if(j!=0) cle_primaire=strtol(tab[0],&ptr,10) ;
        else{
            nc_0=tab[0];n_c1=tab[1]; n_c2=tab[2]; n_c3=tab[3]; n_c4=tab[4];
        }
        if(cle_primaire==id){
            printf("Entrer quelle colonne voudrez vous modifier\n"
                   "0 ) pour modifier tout la ligne\n"
                   "1 ) pour %s\n"
                   "2 ) pour %s\n"
                   "3 ) pour %s\n",n_c1,n_c2,n_c3);
            if(k==0)printf("4 ) pour %s\n",n_c4);
            scanf("%d", &choix);
            if(choix!=0){
                printf("Entrer le nouveau valeur\n");
                char nv[20];
                scanf("%s", nv);
                if (choix == 1)fprintf(TF, "%s,%s,%s,%s%s%s",tab[0], nv, tab[2],tab[3],virgule,tab[4]);
                else if (choix == 2)fprintf(TF, "%s,%s,%s,%s%s%s", tab[0],tab[1] , nv, tab[3],virgule,tab[4]);
                else if (choix == 3)fprintf(TF, "%s,%s,%s,%s%s%s", tab[0],tab[1] ,tab[2], nv,virgule,tab[4]);
                else if (choix == 4)fprintf(TF, "%s,%s,%s,%s%s%s", tab[0], tab[1], tab[2],tab[3], virgule,nv);
            }
            else if(choix==0){
                char colonne1[20],colonne2[20],colonne3[20],colonne4[20];
                printf("\nDonner %s :  ",n_c1);
                scanf("%s",colonne1);
                printf("\nDonner %s :  ",n_c2);
                scanf("%s",colonne2);
                printf("\nDonner %s :  ",n_c3);
                scanf("%s",colonne3);
                if((strcmp(File_name,"Tappartement.txt")==0)||strcmp(File_name,"Trecu.txt")==0){
                    printf("\nDonner %s:  ",n_c4);
                    scanf("%s",colonne4);
                }
                fprintf(TF, "%d,%s,%s,%s%s%s",id,colonne1,colonne2,colonne3, virgule,colonne4);
            }
        }
        else  fprintf(TF,"%s,%s,%s,%s%s%s ",tab[0],tab[1],tab[2],tab[3],virgule,tab[4]);
        if((j!=(nbl-1)))fprintf(TF,"\n");
    }
    fclose(TF) ;
    remove(File_name) ;
    rename("new_file.txt",File_name) ;
    afficher_Table(File_name);
}
void gestion_File(char* Filename)
{
    system("cls");
    int  choix ;
    do {
        printf("\n\n\n\t\t\t\t\t\t MENU DU TRAITEMENT \n\n\n");
        printf("\t\t\t\t\tQuelle opperation souhaitez_vous appliquer \n"
               "\t\t\t\t\t1 ) Ajouter un ligne\n"
               "\t\t\t\t\t2 ) Supprimer un ligne\n"
               "\t\t\t\t\t3 ) Afficher un ligne specifique\n"
               "\t\t\t\t\t4 ) Modifier un ligne\n"
               "\t\t\t\t\t5 ) afficher tous les lignes \n"
               "\t\t\t\t\t6 ) retour aux Menuprincipale\n"
               "\t\t\t\t\t7 ) fin de traitement \n");
        printf("\n\n\t\tdonner votre choix  : ");
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
            {
                system("cls");
                FICHIER_addLigne(Filename,nbl+1);
                printf("\n\n\t\tmise a jour reussie\n");
                printf("\n\n\t\t clique entre pour revenire aux Menu");
                getch();
                system("cls");
                break;
            }
            case 2:
            {
                system("cls");
                SupprimerLigne(Filename);
                printf("\n\n\t\t clique entre pour revenire aux Menu");
                getch();
                system("cls");
                break;
            }
            case 3:
            {
                system("cls");
                printf("\n\n\t\tDonner la cle primaire du ligne  : ");
                int cl ;
                scanf("%d",&cl);
                char ** TL = CreerVecteur(Filename, &nbl) ;
                char **tab = str_split(TL[cl], ",");
                Table *tete=inserer_tete(tete,tab);
                afficher_liste(tete);
                printf("\n\n\t\t clique entre pour revenire aux Menu");
                getch();
                system("cls");
                break;
            }
            case 4:
            {
                system("cls");
                modifierLigne(Filename);
                printf("\n\n\t\tla modufication efectuee avec succes !!");
                printf("\n\n\t\t clique entre pour revenire aux Menu");
                getch();
                system("cls");
                break;
            }
            case 5:
            {
                system("cls");
                afficher_Table(Filename);
                printf("\n\n\t\t clique entre pour revenire aux Menu");
                getch();
                system("cls");
                break;
            }
            case 6:
            {
                system("cls");
                MenuPrincipale();
                break;
            }
            case 7:
            {
                system("cls");
                printf("Fin du programme");
                break;
            }

            default:
            {
                printf(" les choix possible est compris entre 1 et 7\n") ;
                system("cls");
            }
        }
    } while (choix!=7);
}
void MenuPrincipale()
{
    system("cls");
    int i,j,k ;
    char *File_name ;
    do {
        printf("\n\t\t\t\t");
        for(j=0;j<=40;j++)
        {
            printf("*");
        }
        printf("\n\t\t\t\t");
        printf("*");
        for(j=0;j<=38;j++)
        {
            printf(" ");
        }
        printf("*");
        printf("\n\t\t\t\t");
        printf("*");
        printf("           GESTION SYNDICAT            ");
        printf("*");
        printf("\n\t\t\t\t");
        printf("*");
        for(j=0;j<=38;j++)
        {
            printf(" ");
        }
        printf("*");
        printf("\n\t\t\t\t");
        for(j=0;j<=40;j++)
        {
            printf("*");
        }

        printf("\n\n\n\t\t\t\t\tMENU PRINCIPALE\t\t\t\t\t\n\n\n");

        printf("\t\t\t\tQuelle table voulez-vous gerer \n"
               "\t\t\t\tTp: pour Tproprietaire\n"
               "\t\t\t\tTa: pour Tappartement\n"
               "\t\t\t\tTi: pour Timmeuble\n"
               "\t\t\t\tTs: pour Tsyndic\n"
               "\t\t\t\tTc: pour Tcharge\n"
               "\t\t\t\tTr: pour Trecue\n"
               "\t\t\t\tTf: pour Tfacture\n\n\n\n");
        char choix[2]; i=0 ;
        printf("\t\tdonner votre choix  : ");
        scanf("%s", choix);
        if (strcmp(choix, "Tp") == 0)File_name="Tproprietaire.txt";
        else if (strcmp(choix, "Ta") == 0)File_name="Tappartement.txt";
        else if (strcmp(choix, "Ti") == 0)File_name="Timmeuble.txt";
        else if (strcmp(choix, "Ts") == 0)File_name="Tsyndic.txt";
        else if (strcmp(choix, "Tr") == 0)File_name="Trecu.txt";
        else if (strcmp(choix, "Tf") == 0)File_name="Tfacture.txt";
        else if (strcmp(choix, "Tc") == 0)File_name="Tcharge.txt";
        else { printf("\t\t !!!! input non valable Try again...... \n");
            getch();
            system("cls");
            i++;}
    } while (i!=0);
    gestion_File(File_name) ;
    getch();
}
int main()
{
    MenuPrincipale();
    getch();
}


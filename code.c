//Algorithms and data structure project
//Main data structures applied : Red-Black Binary Trees
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 35

//RB TREES, 3 different types:

struct entrel{   //Entity Tree type n.3
    char *nomirel; //list of names of the entities in relation with the main entity of the rb tree of type 1 
    struct entrel *sx, *dx, *padre; //it's a binary research tree
    int colrel; //color: 0 if black 1 if red
};
typedef struct entrel* treerel;

struct nomre{   // Relationships' Name Tree of type n.2 (used also for the report function)
    int relcont; //number of entities related
    char *relanome; // name of the relationship
    struct nomre* si, *de, *padre;
    treerel rent; //tree of relationships' names correlated
    int colnom; //color: 0 if black 1 if red
};

typedef struct nomre* treenomr;

struct nodorb{   //Entity Tree type n.1
    treenomr arrayent;//tree with each relationship in which there are correlated entities 
    //levo i nomi relazioni per ogni nodo ne ho tanti ( ti serve matrice merchè hai nomi lunghi 1000 per ogni 1000 rel;
    char *value; //Entity name in the tree
    struct nodorb *left, *right, *padre;
    int colore; //color: 0 if black 1 if red
};

typedef struct nodorb* rbtree;

rbtree t0; //Global declarations
rbtree nil;
treerel nilrel;
treenomr nilnomr;

void addent(char ent1[MAX], rbtree *t1);
void delent (char ent2[MAX], rbtree *t2, treenomr rep2);
void delrel (char rel2[MAX],rbtree t4, char primaent1[MAX], char secondaent1[MAX], treenomr rep4);
void report (treenomr rep5);

//Support functions
rbtree ricercaent(char enta[MAX], rbtree ta);
rbtree trovasuccessore(rbtree tb);
void aggiungiinrel(treenomr tc,char entc[MAX],treerel *albc);
void eliminadallarel(treenomr te, char ente[MAX], treerel *albe );
void delentsupport1(rbtree tg,char entelim[MAX], treenomr repg,rbtree base);

//Functions for tree of type n.2
void svuotanomrel (treenomr reln1);
treenomr ricercanomre(treenomr reln2, char *nomer);
void aggiunginomre(treenomr *reln3, char *renome);
void elimmetarel(treenomr *reln4, char *entiel,treenomr repn4,rbtree tn4,char *ental);

//Functions for tree of type n.3
treerel ricercaentrel(char entm[MAX], treerel tm);
treerel trovasuccessorerel(treerel tn);
void svuotarel(treerel repy);


//Functions for tree of type n.2 but related to report
void scorrirelrep (char *relmod, rbtree albero,treenomr reph);
void addentrep(char *entc,treerel *albc);
void aggiunginomrrep(treenomr *repl,char *nuovarelrep, int nuovocont, char *primaent);
void inordertreewalk(treerel tboh);
void inordertrewalkprinc( treenomr reln5, char **c);
void toglioccorrenzerep(treenomr repp,rbtree albp, char *elimrepp);
void eliminadallarelrep(treerel *repq, char *elimrepq);

//Functions for fixing in order to order nodes to make the rb tree of type n.1 
void leftrotate(rbtree *rb1,rbtree rot1);
void rightrotate(rbtree *rb2,rbtree rot2);
void addentfixup(rbtree *rb3, rbtree fix3);
void delentfixup(rbtree *rb4, rbtree fix4);

//Functions for basic manipulation of tree of type n.2
void leftnomrot(treenomr *rb8,treenomr rot8);
void rightnomrot(treenomr *rb9, treenomr rot9);
void addentnomfixup(treenomr *rb10, treenomr fix10);

//Functions for basic manipulation and reordering of tree of type n.3
void leftrelrot(treerel *rb5,treerel rot5 );
void rightrelrot(treerel *rb6, treerel rot6);
void addentrelfixup(treerel *rb7, treerel fix7);

int main () {
    char stringa[200], *token1;
    char op[20], enti1[MAX], enti2[MAX], rel[MAX];

    nil= malloc(sizeof(struct nodorb)); //allocate memory space
    nil->colore=0;
    nil->left=nil;
    nil->right=nil;
    nil->padre=nil;
    t0=nil;

    nilrel=malloc(sizeof(struct entrel));
    nilrel->colrel=0;
    nilrel->padre=nilrel;
    nilrel->sx=nilrel;
    nilrel->dx=nilrel;

    nilnomr=malloc(sizeof(struct nomre));
    nilnomr->colnom=0;
    nilnomr->padre=nilnomr;
    nilnomr->si=nilnomr;
    nilnomr->de=nilnomr;

    treenomr repaggiornata=nilnomr; //Tree for the report function


    static char *add1 = "addent";
    static char *del1 = "delent";
    static char *add2 = "addrel";
    static char *del2 = "delrel";
    static char *rep = "report";
    //static char *end = "end";


    while (fgets(stringa, 150, stdin) != NULL) { //While cycle to read from input the command string with the request that has to be computed

        stringa[strlen(stringa) - 1] = 0; //final /n has to be deleted from the string
        token1 = strtok(stringa, " ");
        strcpy(op, token1);

        token1 = strtok(NULL, " "); //strtok is used to improve speed of read and manipulation of the strings -> to speed up the execution time 
        if (token1 != NULL) {
            strcpy(enti1, token1);
            token1 = strtok(NULL, " ");

            if (token1 != NULL) {
                strcpy(enti2, token1);
                token1 = strtok(NULL, " ");

                if (token1 != NULL) {
                    strcpy(rel, token1);
                }
            }

        }
        if (strcmp(op, add1) == 0) {
            addent(enti1, &t0);
        } else if (strcmp(op, del1) == 0) {
            delent(enti1, &t0, repaggiornata);
        } else if (strcmp(op, add2) == 0) {  //ADDREL
            int j = 1;

            rbtree trel = ricercaent(enti2, t0); //trovo la seconda entità (ricevente)
            if( trel != nil){      //verifico di averla trovata
                if (ricercaent(enti1, t0) != nil) { //verifico che la prima ent esista (origine)
                    treenomr nr0 = ricercanomre(trel->arrayent, rel);

                    if (nr0 != nilnomr) { //se trovo il nome della relazione devo aggiungere l'entità correlata nell'albero
                        aggiungiinrel(nr0, enti1, &(nr0->rent)); //aggiungo nell'albero' delle entità correlate con quel tipo di rel all'entita dell'albero

                        ///parte Report
                        treenomr nr1 = ricercanomre(repaggiornata, rel);

                        if (nr1->relcont == nr0->relcont && nr0->relcont > 0) {
                            addentrep(trel->value, &(nr1->rent));
                        } else if (nr1->relcont < nr0->relcont) {
                            if (nr1->rent !=nilrel)
                                svuotarel(nr1->rent);
                            nr1->relcont = nr0->relcont;
                            nr1->rent = nilrel;
                            addentrep(trel->value, &(nr1->rent));
                        }
                        j = 0;

                    } else if (nr0 ==nilnomr) //se non trovo il nome della relazione
                        j = 2;


                    if (j == 2) {
                        //caso base della addrel e della report

                        aggiunginomre(&(trel->arrayent), rel);// metto il nome della rel nuova nell'albero della relazione di quella entità
                        nr0 = ricercanomre(trel->arrayent, rel);
                        aggiungiinrel(nr0, enti1, &(nr0->rent)); //aggiungo la rel con la ent nella lista della nuova rel

                        //parte Report
                        treenomr nr1 = ricercanomre(repaggiornata, rel);

                        if (nr1 == nilnomr)
                            aggiunginomrrep(&repaggiornata, rel, nr0->relcont, trel->value);
                        else {
                            if (nr1->relcont == nr0->relcont && nr0->relcont > 0) {
                                addentrep(trel->value, &(nr1->rent));
                            } else if (nr1->relcont < nr0->relcont) {
                                if (nr1->rent != nilrel)
                                    svuotarel(nr1->rent);
                                nr1->relcont = nr0->relcont;
                                nr1->rent = nilrel;
                                addentrep(trel->value, &(nr1->rent));
                            }
                        }

                    }


                }
            }
        } else if (strcmp(op, del2) == 0) {

            delrel(rel, t0, enti1, enti2, repaggiornata);
        } else if (strcmp(op, rep) == 0) {

            report(repaggiornata);
        } else { // end

            return 0;
        }
    }

    return 0;
}

//1
void addent(char ent1[MAX], rbtree *t1) {
    rbtree add1=nil,supp1=(*t1);
    while(supp1!=nil && strcmp(ent1,supp1->value)!=0){ //scorro per arrivare alle foglie
        add1=supp1;
        if(strcmp(ent1,supp1->value) < 0)
            supp1=supp1->left;
        else supp1=supp1->right;
    }
    if(supp1==nil) { //inserisco come foglia
        rbtree nodo1 = malloc(sizeof(struct nodorb));
        nodo1->value = malloc(strlen(ent1) + 1);
        strcpy(nodo1->value, ent1);
        nodo1->left = nil;
        nodo1->right = nil;
        nodo1->padre = add1;
        nodo1->colore = 1;
        nodo1->arrayent = nilnomr;
        if (add1 == nil)
            (*t1) = nodo1;
        else if (strcmp(nodo1->value, add1->value) < 0)
            add1->left = nodo1;
        else add1->right = nodo1;

        addentfixup(t1, nodo1);
    }


}

//2
void delent (char ent2[MAX], rbtree *t2, treenomr rep2){
    rbtree new=nil,fixiamo=nil;
    new = ricercaent(ent2, *t2);//faccio ricerca dell'entità nell'albero
    int coldel;

    if (new!=nil){     //se ho trovato l'entità continuo
        if(((new)->left)==nil && ((new)->right)==nil){    //caso1 è una foglia
            if(new->padre!=nil) {
                if (new->padre->left == new)
                    new->padre->left = nil;
                else if (new->padre->right == new)
                    new->padre->right = nil;
            } else{
                (*t2)=nil;
            }
            new->left=nil;
            new->right=nil;
            new->padre=nil;
            free(new->value);
            svuotanomrel(new->arrayent);
            toglioccorrenzerep(rep2,*t2,ent2);

            free(new);
        }
        else if((new)->left==nil){ //caso 2: non ha sottoalbero sinistro
            fixiamo=new->right;
            coldel=new->colore;
            if (new->padre != nil) {
                if (new->padre->left == new)
                    new->padre->left = new->right;
                else if (new->padre->right == new)
                    new->padre->right = new->right;
                new->right->padre=new->padre;

            }else {
                (*t2) = new->right;
                new->right->padre =nil;
            }
            new->left = nil;
            new->right = nil;
            new->padre = nil;
            free(new->value);
            svuotanomrel(new->arrayent);
            toglioccorrenzerep(rep2,*t2,ent2);  // elimina ,tutte le volte che compare ,il nome dell'entità dall'albero della report

            free(new);

            if(coldel==0) //faccio fix up solo quando il nodo eliminato era nero, ci sarà uno sbilanciamento
                delentfixup(t2,fixiamo); // aggiustamento per rb
        }

        else if(((new)->right)==nil){  //caso 3: non ha sottoalbero destro
            fixiamo=new->left;
            coldel=new->colore;
            if (new->padre != nil) {
                if(new->padre->left==new)
                    new->padre->left=new->left;
                else if(new->padre->right==new)
                    new->padre->right=new->left;

                new->left->padre = new->padre;

            } else {
                (*t2) = new->left;
                new->left->padre=nil;
            }
            new->left = nil;
            new->right = nil;
            new->padre = nil;
            free(new->value);
            svuotanomrel(new->arrayent);
            toglioccorrenzerep(rep2,*t2,ent2);

            free(new);

            if(coldel==0)
                delentfixup(t2,fixiamo);

        }

        else if(((new)->left!=nil) && ((new)->right)!=nil){//caso 4: ha albero si e de
            rbtree new2 = trovasuccessore(new); // trovo il succ
            fixiamo=new2;
            coldel=new->colore;
            if(new->right!=new2) {
                if (new2->right != nil)
                    new2->right->padre = new2->padre;

                if (new2->padre->left == new2 && new2->right!=nil)
                    new2->padre->left = new2->right;
                else if (new2->padre->right == new2 && new2->right!=nil)
                    new2->padre->right = new2->right;
                else if(new2->right==nil && new2->padre->left ==new2 )
                    new2->padre->left = nil;
                else if (new2->padre->right == new2 && new2->right==nil)
                    new2->padre->right =nil;

                new2->right = new->right;
                new->right->padre = new2;

                new->left->padre = new2;
                new2->left = new->left;


                if (new->padre != nil) {
                    new2->padre = new->padre;
                    if (new->padre->left == new)
                        new->padre->left = new2;
                    else if (new->padre->right == new)
                        new->padre->right = new2;
                } else {
                    (*t2) = new2;
                    new2->padre=nil;
                }
                new->left = nil;
                new->right = nil;
                new->padre = nil;
                free(new->value);
                svuotanomrel(new->arrayent);
                toglioccorrenzerep(rep2,*t2,ent2);

                free(new);
            }
            else if (new->right==new2){

                new->left->padre=new2;
                new2->left=new->left;

                if (new->padre != nil) {
                    new2->padre = new->padre;
                    if (new->padre->left == new)
                        new->padre->left = new2;
                    else if (new->padre->right == new)
                        new->padre->right = new2;
                } else {
                    (*t2) = new2;
                    new2->padre=nil;
                }
                new->left = nil;
                new->right = nil;
                new->padre = nil;
                free(new->value);
                svuotanomrel(new->arrayent);
                toglioccorrenzerep(rep2,*t2,ent2);

                free(new);
            }

            if(coldel==0)
                delentfixup(t2,fixiamo);
        }
        // funzione ricorsiva per eliminare il nome dell'entità dalle relazioni di tutte le altre entità
        delentsupport1( *t2 ,ent2, rep2, *t2);

    }



}



//4
void delrel (char rel2[MAX],rbtree t4, char primaent1[MAX], char secondaent1[MAX], treenomr rep4) {
    rbtree trel = ricercaent(secondaent1, t4); //trovo la seconda entità ricevente della rel

    if(trel!=nil) {    // se esiste la seconda
        if (ricercaent(primaent1, t4) != nil) { //verifico che la prima ent esista
            treenomr nr2 = ricercanomre(trel->arrayent, rel2);
            if (nr2 != nilnomr) {  //se trovo il nome della relazione devo eliminare l'entità correlata nell'albero di tipo3
                int pre = nr2->relcont;
                eliminadallarel(nr2, primaent1,&(nr2->rent)); //elimino dall'albero delle entità correlate con quel tipo di rel all'entita dell'albero

                //Parte report
                if (pre != nr2->relcont) {
                    treenomr np2 = ricercanomre(rep4, rel2);
                    if (np2 != nilnomr) {
                        treerel ricrep = ricercaentrel(trel->value, np2->rent);
                        if (ricrep != nilrel) {
                            eliminadallarelrep(&(np2->rent), trel->value);
                            if (np2->rent == nilrel && np2->relcont>1) {
                                np2->relcont = 0;
                                scorrirelrep(rel2, t4, np2); // modifica nell'albero report
                            }else if (np2->rent==nilrel && np2->relcont==1)
                                np2->relcont=0;
                        }
                    }
                }

            }

        }
    }

}


//5
void report (treenomr rep5){

    char *ver=NULL; // per none
    char vuoto[6];
    strcpy(vuoto, "none");

    if(rep5!=nilnomr){
        inordertrewalkprinc(rep5,&ver); // stampa ordinato
    }

    if(ver==NULL)
        fputs(vuoto,stdout);

    fputc('\n',stdout);

}


// funzioni supplementari

//a
rbtree ricercaent (char enta[MAX], rbtree ta){

    while ( ta!=nil && strcmp(enta,ta->value)!=0 ){
        if(strcmp(enta,ta->value)<0)
            ta=ta->left;
        else
            ta=ta->right;
    }
    return ta;

}

//b
rbtree trovasuccessore(rbtree tb){
    tb=tb->right;
    while(tb->left!=nil)
        tb=tb->left;

    return tb;
}

//c
void aggiungiinrel(treenomr tc,char entc[MAX],treerel *albc) {
    treerel addc=nilrel,suppc=(*albc);

    while(suppc!=nilrel && strcmp(entc,suppc->nomirel)!=0){
        addc=suppc;
        if(strcmp(entc,suppc->nomirel) < 0)
            suppc=suppc->sx;
        else suppc=suppc->dx;
    }
    if(suppc==nilrel) { //verifico di non aver già l'entità, altrimenti non devo aggiungerla
        tc->relcont++; //aumento il contatore del albero tipo 2 perchè è stata aggiunta un'entità in quella rel
        treerel nodo1 = malloc(sizeof(struct entrel));
        nodo1->nomirel=malloc(strlen(entc)+1);
        strcpy(nodo1->nomirel, entc);
        nodo1->colrel=1;
        nodo1->sx = nilrel;
        nodo1->dx = nilrel;
        nodo1->padre = addc;
        if (addc == nilrel)
            (*albc) = nodo1;
        else if (strcmp(nodo1->nomirel, addc->nomirel) < 0)
            addc->sx = nodo1;
        else addc->dx = nodo1;

        addentrelfixup(albc,nodo1);
    }
}

//e
void eliminadallarel(treenomr te, char ente[MAX], treerel *albe ){
    treerel new= nilrel ;
    new=ricercaentrel(ente,*albe);  //ricerca dell'entità


    if (new!=nilrel){
        if(((new)->sx)==nilrel && ((new)->dx)==nilrel){     //caso1 è una foglia
            te->relcont--; // diminuisco il contatore che indica quante ent sono correlate a quell'ent con quella relazione
            if(new->padre!=nilrel) {
                if (new->padre->sx == new)
                    new->padre->sx = nilrel;
                else if (new->padre->dx == new)
                    new->padre->dx = nilrel;
            } else{
                (*albe)=nilrel;
            }
            new->sx=nilrel;
            new->dx=nilrel;
            new->padre=nilrel;
            free(new->nomirel);
            free(new);
        }
        else if((new)->sx==nilrel){   //caso 2: non ha sottoalbero si
            te->relcont--;
            if (new->padre != nilrel) {
                if (new->padre->sx == new)
                    new->padre->sx = new->dx;
                else if (new->padre->dx == new)
                    new->padre->dx = new->dx;
                new->dx->padre=new->padre;

            }else {
                (*albe) = new->dx;
                new->dx->padre =nilrel;
            }
            new->sx = nilrel;
            new->dx = nilrel;
            new->padre = nilrel;
            free(new->nomirel);
            free(new);

        }

        else if(((new)->dx)==nilrel){  //caso 3: non ha sottoalbero de
            te->relcont--;
            if (new->padre != nilrel) {
                if(new->padre->sx==new)
                    new->padre->sx=new->sx;
                else if(new->padre->dx==new)
                    new->padre->dx=new->sx;

                new->sx->padre = new->padre;

            } else {
                (*albe) = new->sx;
                new->sx->padre=nilrel;
            }
            new->sx = nilrel;
            new->dx = nilrel;
            new->padre = nilrel;
            free(new->nomirel);
            free(new);



        }

        else if(((new)->sx!=nilrel) && ((new)->dx)!=nilrel){    //caso 4: ha entrambi
            treerel new2 = trovasuccessorerel(new);  //devo sostituirlo con il successore
            te->relcont--;
            if(new->dx!=new2) {
                if (new2->dx != nilrel)
                    new2->dx->padre = new2->padre;

                if (new2->padre->sx == new2 && new2->dx!=nilrel)
                    new2->padre->sx = new2->dx;
                else if (new2->padre->dx == new2 && new2->dx!=nilrel)
                    new2->padre->dx = new2->dx;
                else if(new2->dx==nilrel && new2->padre->sx ==new2 )
                    new2->padre->sx = nilrel;
                else if (new2->padre->dx == new2 && new2->dx==nilrel)
                    new2->padre->dx = nilrel;

                new2->dx = new->dx;
                new->dx->padre = new2;

                new->sx->padre = new2;
                new2->sx = new->sx;


                if (new->padre != nilrel) {
                    new2->padre = new->padre;
                    if (new->padre->sx == new)
                        new->padre->sx = new2;
                    else if (new->padre->dx == new)
                        new->padre->dx = new2;
                } else {
                    (*albe) = new2;
                    new2->padre=nilrel;
                }
                new->sx= nilrel;
                new->dx = nilrel;
                new->padre = nilrel;
                free(new->nomirel);
                free(new);
            }
            else if (new->dx==new2){

                new->sx->padre=new2;
                new2->sx=new->sx;

                if (new->padre !=nilrel) {
                    new2->padre = new->padre;
                    if (new->padre->sx == new)
                        new->padre->sx = new2;
                    else if (new->padre->dx == new)
                        new->padre->dx = new2;
                } else {
                    (*albe) = new2;
                    new2->padre=nilrel;
                }
                new->sx = nilrel;
                new->dx = nilrel;
                new->padre = nilrel;
                free(new->nomirel);
                free(new);
            }
        }
    }

}


//g
void delentsupport1(rbtree tg,char entelim[MAX],treenomr repg, rbtree base){ //funzione ricorsiva
    // elimina l'entità eliminata dalla delent
    // da tutti i nodi delle altre entità
    if((tg)!=nil){
        elimmetarel(&(tg->arrayent),entelim, repg,base,tg->value);


        delentsupport1(((tg)->left), entelim,repg,base);
        delentsupport1(((tg)->right), entelim, repg, base);
    }
}



//h
void scorrirelrep (char *relmod, rbtree albero, treenomr reph){ //funzione ricorsiva per scorrere le entità nel rbtree e confrontare con la rel modificata del reptree alla ricerca di
    if(albero!=nil){ //1 per ogni nodo dell'albero report       //successori da sostituire

        treenomr trovarel=ricercanomre(albero->arrayent,relmod);
        if(trovarel!=nilnomr){     //se trovo il nome della relazione

            if(trovarel->relcont==reph->relcont && trovarel->relcont>0) //aggiungo solamente se lo ha uguale
                addentrep(albero->value,&(reph->rent));
            else if(trovarel->relcont>reph->relcont){ //se è maggiore sostituisco
                if(reph->rent!=nilrel)
                    svuotarel(reph->rent); // svuoto quella relazione nella report, togliendo tutte le entità, per poi rimettere solo quella con con maggiore
                reph->relcont=trovarel->relcont;
                reph->rent=nilrel;
                addentrep(albero->value,&(reph->rent));
            }
        }

        scorrirelrep(relmod, albero->left, reph);   //vai avanti a tutti i nodi
        scorrirelrep(relmod,albero->right, reph);
    }
}


//j
void addentrep(char *entc,treerel *albc){ //aggiungi nome entità con il maggior numero di entità correlate nell'albero report

    treerel addj=nilrel,suppj=(*albc);
    while(suppj!=nilrel && strcmp(entc,suppj->nomirel)!=0){
        addj=suppj;
        if(strcmp(entc,suppj->nomirel) < 0)
            suppj=suppj->sx;
        else suppj=suppj->dx;
    }
    if(suppj==nilrel) {
        treerel nodo1 = malloc(sizeof(struct entrel));
        nodo1->nomirel=malloc(strlen(entc)+1);
        strcpy(nodo1->nomirel, entc);

        nodo1->sx = nilrel;
        nodo1->dx = nilrel;
        nodo1->padre = addj;

        if (addj == nilrel)
            (*albc) = nodo1;
        else if (strcmp(nodo1->nomirel, addj->nomirel) < 0)
            addj->sx = nodo1;
        else addj->dx = nodo1;
        nodo1->colrel=1;

        addentrelfixup(albc,nodo1);
    }

}


//stampa 1
void inordertrewalkprinc( treenomr reln5, char **c){

    if ( reln5!=nilnomr) {
        inordertrewalkprinc(reln5->si,c);
        if( reln5->relcont>0) {
            *c="a"; // necessario per capire se almeno una volta trovo una rel nell'albero con contatore>0
            fputs(reln5->relanome, stdout); //stampo il nome della relazione
            fputc(' ', stdout);
            inordertreewalk(reln5->rent);
            printf("%d; ", reln5->relcont);
        }
        inordertrewalkprinc(reln5->de,c);
    }


}

//stampa 2
void inordertreewalk(treerel tboh){
    if(tboh!=nilrel) { //stampo i nomi delle entità
        inordertreewalk(tboh->sx);
        fputs(tboh->nomirel, stdout);
        fputc(' ',stdout);
        inordertreewalk(tboh->dx);
    }

}

//m
treerel ricercaentrel(char entm[MAX], treerel tm){
    while ( tm!=nilrel && strcmp(entm,tm->nomirel)!=0 ){
        if(strcmp(entm,tm->nomirel)<0)
            tm=tm->sx;
        else
            tm=tm->dx;
    }
    return tm;
}

//n
treerel trovasuccessorerel(treerel tn){
    tn=tn->dx;
    while(tn->sx!=nilrel)
        tn=tn->sx;

    return tn;
}

//add1
void svuotarel(treerel repy) {
    if (repy ==nilrel)
        return;

    svuotarel(repy->sx);
    svuotarel(repy->dx);

    free(repy->nomirel);
    free(repy);
}

//reln1
void svuotanomrel (treenomr reln1){
    if (reln1 == nilnomr)
        return;

    svuotanomrel(reln1->si);
    svuotanomrel(reln1->de);

    svuotarel(reln1->rent);
    free(reln1->relanome);

    free(reln1);
}

//reln2
treenomr ricercanomre(treenomr reln2, char *nomer){
    while ( reln2!=nilnomr && strcmp(nomer,reln2->relanome)!=0 ){
        if(strcmp(nomer,reln2->relanome)<0)
            reln2=reln2->si;
        else
            reln2=reln2->de;
    }
    return reln2;
}

//reln3
void aggiunginomre(treenomr *reln3, char *renome){ // aggiunge nome relazione nell'albero di tipo 2
    treenomr addn3=nilnomr,suppn3=(*reln3);

    while(suppn3!=nilnomr && strcmp(renome,suppn3->relanome)!=0){ //scorro perchè inserisco sempre come foglia il nodo
        addn3=suppn3;
        if(strcmp(renome,suppn3->relanome) < 0)
            suppn3=suppn3->si;
        else suppn3=suppn3->de;
    }
    if(suppn3==nilnomr) { // devo aggiungere il nome solo se non c'è già

        treenomr nodo1 = malloc(sizeof(struct nomre));
        nodo1->relanome=malloc(strlen(renome)+1);
        strcpy(nodo1->relanome, renome);

        nodo1->colnom=1; // foglia quindi colore rosso
        nodo1->si = nilnomr;
        nodo1->de= nilnomr;
        nodo1->padre = addn3;
        if (addn3 == nilnomr)
            (*reln3) = nodo1;
        else if (strcmp(nodo1->relanome, addn3->relanome) < 0)
            addn3->si = nodo1;
        else addn3->de = nodo1;
        nodo1->rent=nilrel;

        nodo1->relcont=0; //metto il contatore delle entità inizialmente a 0

        addentnomfixup(reln3,nodo1);

    }

}

//reln4
void elimmetarel(treenomr *reln4, char *entiel, treenomr repn4,rbtree tn4,char *entalb){
    if((*reln4)!=nilnomr) {
        int mod=(*reln4)->relcont;
        eliminadallarel(*reln4, entiel, &((*reln4)->rent));
        if(mod!=(*reln4)->relcont){
            treenomr aggrep =ricercanomre(repn4,(*reln4)->relanome);
            eliminadallarelrep(&(aggrep->rent),entalb);
            if(aggrep->rent==nilrel) { //se non ci sono nodi metto il cont a 0
                aggrep->relcont = 0;
            }
            scorrirelrep((*reln4)->relanome,tn4,aggrep); //devo cercare se ci sono altre entità con qualche entità
        }
        elimmetarel(&(*reln4)->si, entiel,repn4,tn4,entalb);
        elimmetarel(&(*reln4)->de, entiel,repn4,tn4,entalb);
    }
}

//l per Report
void aggiunginomrrep(treenomr *repl,char *nuovarelrep, int nuovocont, char *primaent){

    treenomr addl=nilnomr,suppl=(*repl);
    while(suppl!=nilnomr && strcmp(nuovarelrep,suppl->relanome)!=0){
        addl=suppl;
        if(strcmp(nuovarelrep,suppl->relanome) < 0)
            suppl=suppl->si;
        else suppl=suppl->de;
    }
    if(suppl==nilnomr) {
        treenomr nodo1 = malloc(sizeof(struct nomre));
        nodo1->relanome=malloc(strlen(nuovarelrep)+1);
        strcpy(nodo1->relanome, nuovarelrep);

        nodo1->colnom=1;
        nodo1->si = nilnomr;
        nodo1->de= nilnomr;
        nodo1->padre = addl;
        if (addl == nilnomr)
            (*repl) = nodo1;
        else if (strcmp(nodo1->relanome, addl->relanome) < 0)
            addl->si = nodo1;
        else addl->de = nodo1;
        nodo1->rent=nilrel; // imposto l'albero dei nomi delle entità correlate vuoto
        addentrep(primaent,&(nodo1->rent));
        nodo1->relcont=nuovocont;

        addentnomfixup(repl,nodo1);

    }

}

//p
void toglioccorrenzerep(treenomr repp, rbtree albp, char *elimrepp){
    if(repp!=nilnomr){
        eliminadallarelrep(&(repp->rent),elimrepp);
        if(repp->rent==nilrel && repp->relcont>1) {
            repp->relcont=0;
            scorrirelrep(repp->relanome, albp, repp); // vado a vedere in tutto l'albero se ci sono dei sostituti
        }else if(repp->rent==nilrel && repp->relcont==1) // se era l'ultimo rimasto e c'era una sola entità correlata vuol dire che tutte le altre ne hanno 0
            repp->relcont=0;                            //non serve cercare altre entità da mettere nell'albero report
        toglioccorrenzerep(repp->si,albp,elimrepp);
        toglioccorrenzerep(repp->de,albp, elimrepp);
    }
}

//q
void eliminadallarelrep(treerel *repq, char *elimrepq){
    treerel new= nilrel ;

    new=ricercaentrel(elimrepq,*repq);  //ricerca dell'entità


    if (new!=nilrel){
        if(((new)->sx)==nilrel && ((new)->dx)==nilrel){     //caso1: è una foglia

            if(new->padre!=nilrel) {
                if (new->padre->sx == new)
                    new->padre->sx = nilrel;
                else if (new->padre->dx == new)
                    new->padre->dx = nilrel;
            } else{
                (*repq)=nilrel;
            }
            new->sx=nilrel;
            new->dx=nilrel;
            new->padre=nilrel;
            free(new->nomirel);
            free(new);
        }
        else if((new)->sx==nilrel){   //caso 2: non ha sottoalbero si

            if (new->padre != nilrel) {
                if (new->padre->sx == new)
                    new->padre->sx = new->dx;
                else if (new->padre->dx == new)
                    new->padre->dx = new->dx;
                new->dx->padre=new->padre;

            }else {
                (*repq) = new->dx;
                new->dx->padre =nilrel;
            }
            new->sx = nilrel;
            new->dx = nilrel;
            new->padre = nilrel;
            free(new->nomirel);
            free(new);

        }

        else if(((new)->dx)==nilrel){  //caso 3: non ha sottoalbero de

            if (new->padre != nilrel) {
                if(new->padre->sx==new)
                    new->padre->sx=new->sx;
                else if(new->padre->dx==new)
                    new->padre->dx=new->sx;

                new->sx->padre = new->padre;

            } else {
                (*repq) = new->sx;
                new->sx->padre=nilrel;
            }
            new->sx = nilrel;
            new->dx = nilrel;
            new->padre = nilrel;
            free(new->nomirel);
            free(new);
        }

        else if(((new)->sx!=nilrel) && ((new)->dx)!=nilrel){    //caso 4: ha entrambi
            treerel new2 = trovasuccessorerel(new);  // successore per albero delle relazioni

            if(new->dx!=new2) {
                if (new2->dx != nilrel)
                    new2->dx->padre = new2->padre;

                if (new2->padre->sx == new2 && new2->dx!=nilrel)
                    new2->padre->sx = new2->dx;
                else if (new2->padre->dx == new2 && new2->dx!=nilrel)
                    new2->padre->dx = new2->dx;
                else if(new2->dx==nilrel && new2->padre->sx ==new2 )
                    new2->padre->sx = nilrel;
                else if (new2->padre->dx == new2 && new2->dx==nilrel)
                    new2->padre->dx = nilrel;

                new2->dx = new->dx;
                new->dx->padre = new2;

                new->sx->padre = new2;
                new2->sx = new->sx;


                if (new->padre != nilrel) {
                    new2->padre = new->padre;
                    if (new->padre->sx == new)
                        new->padre->sx = new2;
                    else if (new->padre->dx == new)
                        new->padre->dx = new2;
                } else {
                    (*repq) = new2;
                    new2->padre=nilrel;
                }
                new->sx= nilrel;
                new->dx = nilrel;
                new->padre = nilrel;
                free(new->nomirel);
                free(new);
            }
            else if (new->dx==new2){

                new->sx->padre=new2;
                new2->sx=new->sx;

                if (new->padre !=nilrel) {
                    new2->padre = new->padre;
                    if (new->padre->sx == new)
                        new->padre->sx = new2;
                    else if (new->padre->dx == new)
                        new->padre->dx = new2;
                } else {
                    (*repq) = new2;
                    new2->padre=nilrel;
                }
                new->sx = nilrel;
                new->dx = nilrel;
                new->padre = nilrel;
                free(new->nomirel);
                free(new);
            }
        }
    }

}

//rb1
void leftrotate(rbtree *rb1,rbtree rot1){
    rbtree l1=rot1->right;

    if(l1!=nil && rot1!=nil) { //non posso entrare e fare rotazione tra un nodo e nil

        rot1->right = l1->left; // il sottoalbero sin di rot1 diventa quello de di l1

        if (l1->left != nil)
            l1->left->padre = rot1;

        l1->padre = rot1->padre;

        if (rot1->padre == nil) //nel caso sia la radice
            (*rb1) = l1;
        else if (rot1 == rot1->padre->left)
            rot1->padre->left = l1;
        else if (rot1 == rot1->padre->right)
            rot1->padre->right = l1;

        l1->left = rot1;
        rot1->padre = l1;
    }

}

//rb2
void rightrotate(rbtree *rb2,rbtree rot2){


    rbtree r2=rot2->left;
    if(r2!=nil && rot2!=nil) { //non posso entrare e fare rotazione tra un nodo e nil
        rot2->left = r2->right;

        if (r2->right != nil)
            r2->right->padre = rot2;

        r2->padre = rot2->padre;

        if (rot2->padre == nil)
            (*rb2) = r2;
        else if (rot2->padre->left == rot2)
            rot2->padre->left = r2;
        else if (rot2 == rot2->padre->right)
            rot2->padre->right = r2;

        r2->right = rot2;
        rot2->padre = r2;
    }
}

//rb3
void addentfixup(rbtree *rb3, rbtree fix3){ //ricorsiva
    rbtree fixa=nil;
    if(fix3==(*rb3))
        (*rb3)->colore=0; //la radice deve essere sempre nera
    else fixa=fix3->padre;

    if(fixa->colore==1) {
        //if(fixa->padre!=NULL) {
        if (fixa == fixa->padre->left) {
            rbtree fixb = fixa->padre->right;
            if (fixb->colore == 1) {
                fixa->colore = 0;
                fixb->colore = 0;
                fixa->padre->colore = 1;
                addentfixup(rb3, fixa->padre); //salgo ricorsivamente mettendo il colore rosso sempre al nodo sopra
            } else {
                if (fix3 == fixa->right) {
                    fix3 = fixa;
                    leftrotate(rb3, fix3);
                    fixa = fix3->padre;
                }
                fixa->colore = 0;
                fixa->padre->colore = 1;
                rightrotate(rb3, fixa->padre);
            }
        } else { //fixa==fixa->padre->de    //casi speculari
            rbtree fixb = fixa->padre->left;
            if ( fixb->colore ==1){
                fixa->colore=0;
                fixb->colore=0;
                fixa->padre->colore=1;
                addentfixup(rb3, fixa->padre);
            }
            else{
                if(fix3==fixa->left){
                    fix3=fixa;
                    rightrotate(rb3,fix3);
                    fixa=fix3->padre;
                }
                fixa->colore=0;
                fixa->padre->colore=1;
                leftrotate(rb3,fixa->padre);

            }
        }
        // }
    }
}


//rb4
void delentfixup(rbtree *rb4, rbtree fix4){ // metto la delent fixup solo per l'albero grande con tutti i nomi delle entità
                                            //per gli alberi con i nomi delle relazioni e le ent correlate, essendo con meno nodi, faccio la fixup solo quando inserisco un nodo
    if(fix4->colore==1 || fix4->padre==nil )//la chiamo solo quando il nodo eliminato è di colore nero
        fix4->colore=0;
    else if(fix4==fix4->padre->left){
        rbtree fixc=fix4->padre->right;
        if( fixc->colore==1){
            fixc->colore=0;
            fix4->padre->colore=1;
            leftrotate(rb4,fix4->padre);
            fixc=fix4->padre->right;
        }
        if(fixc->left->colore==0 && fixc->right->colore==0){
            fixc->colore=1;
            delentfixup(rb4,fix4->padre);
        }
        else{
            if(fixc->right->colore==0 ){
                fixc->left->colore=0;
                fixc->colore=1;
                rightrotate(rb4,fixc);
                fixc=fix4->padre->right;
            }
            fixc->colore=fix4->padre->colore;
            fix4->padre->colore=0;
            fixc->right->colore=0;
            leftrotate(rb4,fix4->padre);
        }
    }
    else{ //fix8=fix8->padre->de
        rbtree fixc=fix4->padre->left;
        if(fixc->colore==1){
            fixc->colore=0;
            fix4->padre->colore=1;
            rightrotate(rb4,fix4->padre);
            fixc=fix4->padre->left;
        }
        if(fixc->right->colore==0 && fixc->left->colore==0 && fixc!=nil){
            fixc->colore=1;
            delentfixup(rb4, fix4->padre);
        }
        else{
            if(fixc->left->colore==0 && fixc!=nil){
                fixc->right->colore=0;
                fixc->colore=1;
                leftrotate(rb4,fixc);
                fixc=fix4->padre->left;
            }
            fixc->colore=fix4->padre->colore;
            fixc->left->colore=0;
            fix4->padre->colore=0;
            rightrotate(rb4,fix4->padre);
        }
    }


}



//aggiustamenti per albero tipo 3
//rb5
void leftrelrot(treerel *rb5,treerel rot5 ){
    treerel l5=rot5->dx;

    if(l5!=nilrel && rot5!=nilrel) {
        rot5->dx = l5->sx; // il sottoalbero si di l5 diventa quello de di rot5

        if (l5->sx != nilrel)
            l5->sx->padre = rot5;

        l5->padre = rot5->padre;

        if (rot5->padre == nilrel)
            (*rb5) = l5;
        else if (rot5 == rot5->padre->sx)
            rot5->padre->sx = l5;
        else if (rot5 == rot5->padre->dx)
            rot5->padre->dx = l5;

        l5->sx = rot5;
        rot5->padre = l5;
    }

}

//rb6
void rightrelrot(treerel *rb6, treerel rot6){

    treerel r6=rot6->sx;

    if(r6!=nilrel && rot6!=nilrel) {
        rot6->sx = r6->dx;

        if (r6->dx != nilrel)
            r6->dx->padre = rot6;

        r6->padre = rot6->padre;

        if (rot6->padre == nilrel)
            (*rb6) = r6;
        else if (rot6->padre->sx == rot6)
            rot6->padre->sx = r6;
        else if (rot6 == rot6->padre->dx)
            rot6->padre->dx = r6;

        r6->dx = rot6;
        rot6->padre = r6;
    }
}

//rb7
void addentrelfixup(treerel *rb7, treerel fix7){
    treerel fixa=nilrel;
    if(fix7==(*rb7))  //radice nera
        (*rb7)->colrel=0;
    else fixa=fix7->padre;

    if(fixa->colrel==1) {  //faccio sempre modifiche solo se il fixa è rosso
        if (fixa == fixa->padre->sx) {
            treerel fixb = fixa->padre->dx;
            if (fixb->colrel == 1) {
                fixa->padre->colrel = 1;
                fixa->colrel = 0;
                fixb->colrel = 0;
                addentrelfixup(rb7, fixa->padre); //ricorsione
            } else {
                if (fix7 == fixa->dx) {
                    fix7 = fixa;
                    leftrelrot(rb7, fix7);
                    fixa = fix7->padre;
                }
                fixa->colrel = 0;
                fixa->padre->colrel = 1;
                rightrelrot(rb7, fixa->padre);
            }
        } else {            //fixa==fixa->padre->de
            treerel fixb = fixa->padre->sx;
            if ( fixb->colrel ==1){
                fixa->padre->colrel=1;
                fixa->colrel=0;
                fixb->colrel=0;
                addentrelfixup(rb7, fixa->padre);
            }
            else{
                if(fix7==fixa->sx){
                    fix7=fixa;
                    rightrelrot(rb7,fix7);
                    fixa=fix7->padre;
                }
                fixa->colrel=0;
                if(fixa->padre!=nilrel)
                    fixa->padre->colrel=1;
                leftrelrot(rb7,fixa->padre);

            }
        }

    }
}


//aggiustamenti albero tipo 2
//rb8
void leftnomrot(treenomr *rb8,treenomr rot8){

    treenomr l8=rot8->de;
    if(l8!=nilnomr && rot8!=nilnomr) {
        rot8->de = l8->si; // il sottoalbero si di l8 diventa quello de di rot8

        if (l8->si != nilnomr)
            l8->si->padre = rot8;

        l8->padre = rot8->padre;

        if (rot8->padre == nilnomr)
            (*rb8) = l8;
        else if (rot8 == rot8->padre->si)
            rot8->padre->si = l8;
        else if (rot8 == rot8->padre->de)
            rot8->padre->de = l8;

        l8->si = rot8;
        rot8->padre = l8;
    }
}

//rb9
void rightnomrot(treenomr *rb9, treenomr rot9){
    treenomr r9=rot9->si;
    if(r9!=nilnomr && rot9!=nilnomr) {
        rot9->si = r9->de;

        if (r9->de != nilnomr)
            r9->de->padre = rot9;

        r9->padre = rot9->padre;

        if (rot9->padre == nilnomr)
            (*rb9) = r9;
        else if (rot9->padre->si == rot9)
            rot9->padre->si = r9;
        else if (rot9 == rot9->padre->de)
            rot9->padre->de = r9;

        r9->de = rot9;
        rot9->padre = r9;
    }
}

//rb10
void addentnomfixup(treenomr *rb10, treenomr fix10){
    treenomr fixa=nilnomr;
    if(fix10==(*rb10))
        (*rb10)->colnom=0; //radice nera
    else fixa=fix10->padre;

    if(fixa->colnom==1) { //faccio sempre modifiche solo se il fixa è rosso
        if (fixa == fixa->padre->si) {
            treenomr fixb = fixa->padre->de;
            if (fixb->colnom == 1) {
                fixa->padre->colnom = 1;
                fixa->colnom = 0;
                fixb->colnom = 0;
                addentnomfixup(rb10, fixa->padre);
            } else {
                if (fix10 == fixa->de) {
                    fix10 = fixa;
                    leftnomrot(rb10, fix10);
                    fixa = fix10->padre;
                }
                fixa->colnom = 0;
                fixa->padre->colnom = 1;
                rightnomrot(rb10, fixa->padre);
            }
        } else { //fixa==fixa->padre->de
            treenomr fixb = fixa->padre->si;
            if ( fixb->colnom ==1){
                fixa->padre->colnom=1;
                fixa->colnom=0;
                fixb->colnom=0;
                addentnomfixup(rb10, fixa->padre);
            }
            else{
                if(fix10==fixa->si){
                    fix10=fixa;
                    rightnomrot(rb10,fix10);
                    fixa=fix10->padre;
                }
                fixa->colnom=0;
                if(fixa->padre!=nilnomr)
                    fixa->padre->colnom=1;
                leftnomrot(rb10,fixa->padre);

            }
        }

    }
}




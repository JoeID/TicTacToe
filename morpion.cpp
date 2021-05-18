#include <iostream>
using namespace std;

//JOUEUR 0 : AI, 'x' ; JOUEUR 1 : HUMAIN, 'o'
char square[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
void drawBoard(); //affiche la grille de jeu courante
void play(int player, int pos); //la joueur player joue un coup à la position pos
int etatJeu(char board[]); //renvoie -1 s'il y a égalité, 0 si le joueur 0 a gagné, 1 si le joueur 1 a gagné, -2 si le jeu est toujours en cours
int minimax(int depth, char board[], bool maximizingPlayer); //renvoie le coup que l'algo va jouer

int main()
{
    bool algo = true; //indique si c'est au tour de l'algo
    while (etatJeu(square)==-2){
        if (algo){ //c'est l'algo qui joue
            char new_square[9]; //on copie le tableau
            for (int i=0;i<9;i++){
                new_square[i]=square[i];
            }

            drawBoard();
            int coup = minimax(0,new_square,true);
            play(0,coup);
            algo=false;
        }
        else{ //c'est l'humain qui joue
            drawBoard();
            cout << "Veuillez entrez votre coup : ";
            int coup;
            cin >> coup;
            cout << endl;
            play(1,coup);
            algo=true;
        }        
    }
    int f=etatJeu(square); //le jeu est fini, on affiche le résultat
    drawBoard();
    if (f==1){
        cout << "L'HUMAIN A GAGNÉ" << endl;
    }
    else if (f==0){
        cout << "LE PROGRAMME A GAGNÉ" << endl;
    }
    else{
        cout << "ÉGALITÉ" << endl;
    }
    return 0;
}
void drawBoard(){
    cout << square[0] << " | " << square[1] << " | " << square[2] << endl;
    cout << "----------" << endl;
    cout << square[3] << " | " << square[4] << " | " << square[5] << endl;
    cout << "----------" << endl;
    cout << square[6] << " | " << square[7] << " | " << square[8] << endl;
}
void play(int player, int pos){
    if (pos>=9 || pos <0){
        cout << "Valeur trop grande ou trop petite. Réessayez" << endl;
    }
    else if (square[pos] != ' '){
        cout << "La case n'est pas vide. Réessayez" << endl;
    }
    else if (player==0){
        square[pos]='x';
        cout << "_______________TOUR SUIVANT_______________" << endl << endl;
    }
    else{
        square[pos]='o';
        cout << "_______________TOUR SUIVANT_______________" << endl << endl;
    }
}
int etatJeu(char board[]){
    //on vérifie d'abord si un des deux joueurs a gagné

    //les lignes
    if ('o'==board[0] && board[0]==board[1] && board[1]==board[2]){
        return 1;
    }
    else if ('o'==board[3] && board[3]==board[4] && board[4]==board[5]){
        return 1;
    }
    else if ('o'==board[6] && board[6]==board[7] && board[7]==board[8]){
        return 1;
    }
    else if ('x'==board[0] && board[0]==board[1] && board[1]==board[2]){
        return 0;
    }
    else if ('x'==board[3] && board[3]==board[4] && board[4]==board[5]){
        return 0;
    }
    else if ('x'==board[6] && board[6]==board[7] && board[7]==board[8]){
        return 0;
    }

    //les colonnes
    if ('o'==board[0] && board[0]==board[3] && board[3]==board[6]){
        return 1;
    }
    else if ('o'==board[1] && board[1]==board[4] && board[4]==board[7]){
        return 1;
    }
    else if ('o'==board[2] && board[2]==board[5] && board[5]==board[8]){
        return 1;
    }
    else if ('x'==board[0] && board[0]==board[3] && board[3]==board[6]){
        return 0;
    }
    else if ('x'==board[1] && board[1]==board[4] && board[4]==board[7]){
        return 0;
    }
    else if ('x'==board[2] && board[2]==board[5] && board[5]==board[8]){
        return 0;
    }

    //les diagonales
    if ('o'==board[0] && board[0]==board[4] && board[4]==board[8]){
        return 1;
    }
    else if ('o'==board[2] && board[2]==board[4] && board[4]==board[6]){
        return 1;
    }
    else if ('x'==board[0] && board[0]==board[4] && board[4]==board[8]){
        return 0;
    }
    else if ('x'==board[2] && board[2]==board[4] && board[4]==board[6]){
        return 0;
    }

    //on vérifie ensuite s'il existe une case vide
    bool c_vide = false;
    for (int i=0;i<9;i++){
        if (board[i] == ' '){
            c_vide = true;
            break;
        }
    }
    if (c_vide){
        return -2; //au moins une case est libre, on peut encore jouer
    }
    else{
        return -1; //toutes les cases sont pleines et aucun joueur n'a gagné, il y a égalité
    }
}
int minimax(int depth, char board[],bool maximizingPlayer){
    int f=etatJeu(board);
    int valeur;
    switch (f){
        case 1:
            valeur=-1;
            break;
        case 0:
            valeur=1;
            break;
        default:
            valeur=0;
            break;
    }
    if (f != -2){ //si le jeu est terminé
        return valeur;
    }
    if (maximizingPlayer){ //c'est l'algo qui joue
        valeur=-1;
        int coup;
        for (int i=0;i<9;i++){
            if (board[i]==' '){ //si on peut jouer là

                char new_board[9]; //on copie le tableau
                for (int j=0;j<9;j++){
                    new_board[j] = board[j];
                }
                new_board[i] = 'x'; //on effectue le play

                int new_v = minimax(depth+1,new_board,false);
                if (depth==0){
                    if (new_v >= valeur){//si on doit décider quoi jouer, on n'override coup que si on la nouvelle valeur est meilleure que l'ancienne
                        coup=i;
                        valeur=new_v;
                    }
                }
                else{
                    valeur = max(valeur,new_v);
                }
            }
        }
        if (depth==0){
            return coup; //on décide quel coup jouer
        }
        else{
            return valeur;
        }
    }
    else{ //c'est l'humain qui joue
        valeur=1;
        for (int i=0;i<9;i++){
            if (board[i]==' '){

                char new_board[9]; //on copie le tableau
                for (int j=0;j<9;j++){
                    new_board[j] = board[j];
                }
                new_board[i] = 'o'; //on effectue le play

                int new_v = minimax(depth+1,new_board,true);
                valeur = min(valeur,new_v);
            }
        }
        return valeur;
    }
}
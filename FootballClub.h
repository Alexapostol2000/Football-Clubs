#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// List node which contains information about one football player.
typedef struct Player {
	char *name;					// player's name
	char *position;				// player's game position
	int score;					// player's score
	int injured;				// indicator for injury (1 true, 0 false)
	struct Player *next;		// next list node
	struct Player *prev;		// previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
	char *name;					// club's name
	Player *players;			// list with players in good shape
	Player *injured_players;	// list with injured players
	struct FootballClub *next;	// next list node
} FootballClub;


FootballClub *initialize_clubs(int clubs_no, char **names) {
	
	int i;
	if(clubs_no == 0)
		return NULL;
	FootballClub *club , *first;
	club = (FootballClub*)calloc(1,sizeof(FootballClub));
	 club -> players = NULL;
	if(club == NULL){
		printf("calloc fail\n");
		
	}
	club -> name = (char*)calloc(30,sizeof(char));
	if(club -> name == NULL){
		printf("calloc fail\n");
		return NULL;
	}
	strcpy(club -> name , names[0]);
	first = club;
	for ( i = 1 ; i < clubs_no ; i++)
	{FootballClub *aux;
		aux = (FootballClub*)calloc(1,sizeof(FootballClub));
		if(aux == NULL){
			printf("calloc fail\n");
			return NULL;
		}
		aux -> players = NULL;
		aux -> name = (char*)calloc(30,sizeof(char));
		if(aux -> name == NULL){
			printf("calloc fail\n");
			return NULL;
		}
		strcpy(aux -> name,names[i]);
		club -> next = aux;
		club = club -> next;
		
	}
			
return first;	

}

FootballClub *add_club(FootballClub *clubs, char *name) {
	FootballClub *aux,*nou;
	nou = (FootballClub*)calloc(1,sizeof(FootballClub));
	if(nou == NULL){
		printf("calloc fail\n");
		return NULL;
	}
	nou -> players = NULL;
	nou -> name = (char*)calloc(strlen(name)+1,sizeof(char));
	if(nou -> name == NULL){
		printf("calloc fail\n");
		return NULL;
	}
	strcpy(nou -> name,name);
	if(nou == NULL){
		printf("calloc fail\n");
		return NULL;
	}
	if(clubs == NULL){
		clubs = nou;
		return clubs;
	}
	aux = clubs;
	while(aux -> next != NULL)
		aux = aux -> next;
aux -> next = nou;

return clubs;
}
///////////Verifica daca exista clubul cu acel nume///
	int exclub(FootballClub *club, char* name){
		FootballClub* aux;
		aux = club ;
		while(aux !=   NULL && strcmp(aux -> name,name) != 0)
			aux = aux-> next;
		if(aux != NULL)
			return 1;
		else
			return 0;
	}
///////////////////////////////////////////////////
///verifica daca exista acea pozitie in club
	int expos(FootballClub *club,char *position){
		Player* aux;
		aux = club -> players;
		while(aux != NULL){
			if(strcmp(aux -> position,position) ==0)
				return 1;
			aux = aux -> next;
		}
	return 0 ;
	}
////////ex pos accidentati//////////////////////
		int exposac(FootballClub *club,char *position){
		Player* aux;
		aux = club -> injured_players;
		while(aux != NULL){
			if(strcmp(aux -> position,position) ==0)
				return 1;
			aux = aux -> next;
		}
	return 0 ;
	}
	////////////////

///verifica daca exsita un player cu un anumit nume////////////////
	int explayer(FootballClub *club,char *name){
		Player *aux;
		aux = club -> players;
		while(aux){
			if (strcmp(aux -> name,name) == 0)
				return 1;
			aux = aux -> next;
		}
	return 0 ;
	}
	//////////
	/////verifica daca exista player cu un nume in lista de accidentati////
	int explayerac(FootballClub *club,char *name){
		Player *aux;
		aux = club -> injured_players;
		while(aux){
			if (strcmp(aux -> name,name) == 0)
				return 1;
			aux = aux -> next;
		}
	return 0 ;
	}
	//////////////////////

void add_player(FootballClub *clubs, char *club_name, 
				char *player_name, char *position, int score) {




if(clubs == NULL)
	return;
if(exclub(clubs,club_name) == 0)
	return;

FootballClub *club;
Player *jucator,*parcurge,*prec;

jucator = (Player*)calloc(1,sizeof(Player));
	if(jucator == NULL){
		printf("calloc fail\n");
		return;
	}
jucator -> name = (char*)calloc(strlen(player_name+1),sizeof(char));
if(jucator -> name == NULL){
	printf("calloc fail\n");
	return;
}
strcpy(jucator -> name,player_name);


jucator -> position = (char*)calloc(9,sizeof(char));
if(jucator -> position == NULL){
	printf("calloc fail\n");
	return;
}
strcpy(jucator -> position , position);


jucator -> score = score;
jucator -> injured = 0;

club =clubs;



while(strcmp(club -> name,club_name) != 0 )
	club = club -> next;


if(club -> players == NULL){
club -> players = jucator;
jucator -> next = NULL;
jucator -> prev = NULL;
return;
}


else{
		parcurge =  club -> players;
		if(expos(club,position) == 0){
			
			if(strcmp(club -> players -> position,position) > 0){	
				jucator -> next = club -> players;
				jucator -> prev = NULL;
				club -> players = jucator;
				return;
			}
			
			while(strcmp(parcurge -> position,position) < 0 && parcurge != NULL){
				prec = parcurge;
				parcurge = parcurge -> next;	
				if(parcurge == NULL){
					break;
				}
			}
			if(parcurge == NULL){
				prec -> next = jucator;
				jucator -> prev =  prec;
				jucator -> next = NULL;
				return;
				}
			
			else{
				prec -> next = jucator;
				jucator -> prev = prec;
				jucator -> next = parcurge;
				parcurge -> prev = jucator;
				return;
			}
	
		}	
		else{
				
			if(jucator -> score > club -> players -> score && strcmp(jucator -> position,club -> players -> position) == 0){
					jucator -> next = club -> players;
					club -> players -> prev = jucator;
					club -> players = jucator;
					return;
				}
			while(strcmp(parcurge -> position  , position) != 0 ){
				prec = parcurge;
				parcurge = parcurge -> next;
			}
			

			while(parcurge -> score > score && parcurge -> next != NULL && strcmp(parcurge -> position,position) == 0){
				prec = parcurge;
				parcurge = parcurge -> next;
			}


			
			if(score != parcurge -> score){
				if(parcurge -> next == NULL){
					
					parcurge -> next = jucator;
					jucator -> prev = parcurge;
					jucator -> next = NULL;
					return;
				}
				prec -> next = jucator;
				jucator -> prev = prec;
				jucator -> next = parcurge;
				parcurge -> prev = jucator;
				return;
			}
			
			else{

				if(strcmp(jucator -> name , club -> players -> name) < 0 && strcmp(parcurge -> name , club -> players -> name) == 0){
					jucator -> next = club -> players;
					club -> players -> prev = jucator;
					jucator -> prev = NULL;
					club -> players = jucator;
					return;
				}



				while(strcmp(jucator -> name , parcurge -> name) > 0 && strcmp(parcurge -> position,position) == 0 && parcurge -> next != NULL && jucator -> score == parcurge -> score){
					prec = parcurge;
					parcurge = parcurge -> next;
				}

				if(jucator -> score != parcurge -> score){
					prec -> next = jucator;
					jucator -> prev = prec;
					jucator -> next = parcurge;
					parcurge -> prev = jucator;
					return;
				}
				if(strcmp(parcurge -> position, position) != 0){
					
					prec -> next = jucator;
					jucator -> prev = prec;
					jucator -> next = parcurge;
					parcurge -> prev = jucator;
					return;
				}
				if(parcurge -> next == NULL){
					
					parcurge -> next = jucator;
					jucator -> prev = parcurge;
					jucator -> next = NULL;
					return;	
				}
			prec -> next = jucator;
			jucator -> prev = prec;
			jucator-> next = parcurge;
			parcurge -> prev = jucator;
				return;
			}
		
		}
	
	}
		
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
	if(exclub(clubs,club_name) == 0)
		return;
int l;
FootballClub *club;
club = clubs;
while(strcmp(club -> name , club_name) != 0 )
	club = club -> next;
if(explayer(club,player_name) == 0)
	if(explayerac(club,player_name) == 0)
		return;
	else
		l=0;
else
	l=1;
Player *aux,*prec,*eliberez;

if(l == 1){
	aux = club -> players;

	while(strcmp(aux -> name,player_name ) != 0){
		prec = aux;
		aux = aux -> next;

	}

		if(aux -> next == NULL && aux -> prev == NULL){
			free(club -> players);
			club -> players = NULL;
			return;
		}

		if(aux -> prev == NULL){
			eliberez = aux;
			aux = aux -> next;
			aux -> prev = NULL;
			club -> players =  aux;
			
			free(eliberez);
			return;
		}

		if(aux -> next == NULL){

			prec -> next = NULL;
			
			free(aux);
			return;
		}
			eliberez = aux;	
			aux = aux -> next;
			prec -> next = aux;
			aux -> prev = prec;
			
			free(eliberez);
}
else{
		aux = club -> injured_players;

	while(strcmp(aux -> name,player_name ) != 0){
		prec = aux;
		aux = aux -> next;

	}
		if(aux -> next == NULL && aux -> prev == NULL){
			free(club -> injured_players);
			club -> injured_players = NULL;
			return;
		}

		if(aux -> prev == NULL){
			eliberez = aux;
			aux = aux -> next;
			aux -> prev = NULL;
			club -> injured_players =  aux;
			free(eliberez);
			return;
		}

		if(aux -> next == NULL){
			prec -> next = NULL;
			free(aux);
			return;
		}
			eliberez = aux;	
			aux = aux -> next;
			prec -> next = aux;
			aux -> prev = prec;
			free(aux);
}

}

void insert_injured(FootballClub *club,Player *player){
	
	Player* jucator;
	jucator =(Player*)calloc(1,sizeof(Player));
	if(jucator == NULL){
		printf("calloc fail\n");
		return;
	}
	jucator -> name = player -> name;
	jucator -> position=player -> position;
	jucator -> score = player -> score;
	jucator -> injured = 1;
	jucator -> prev = NULL;
	jucator -> next = NULL;
	
	if(club -> injured_players == NULL){
		club -> injured_players = jucator;
		return;
	}
	else{
			Player *aux,*prec;
			aux = club -> injured_players;
			if(strcmp( jucator -> name , aux -> name) < 0){
				jucator -> next = aux;
				aux -> prev = jucator;
				jucator -> prev = NULL;
				club  -> injured_players = jucator;
			return;
			}
			
			while(strcmp(jucator -> name,aux -> name) > 0 && aux != NULL){
				
				prec = aux;
				aux = aux -> next;
			if(aux == NULL)
				break;
			}
			
			if(aux == NULL){
				prec -> next = jucator;
				jucator -> prev = prec;
				jucator -> next = NULL;
				return;
			}


		prec -> next = jucator;
		jucator -> prev = prec;
		aux -> prev = jucator;
	}


}

void delete_injured(FootballClub *club ,char *name){
	Player* aux,*prec = NULL;
	aux = club -> injured_players;
	while( aux != NULL && strcmp(aux -> name , name)!= 0 ){
		prec = aux;
		aux = aux -> next;
	}

	if(aux == NULL){
		printf("Error : Not found\n");
		return;
	}
	if(strcmp(club -> injured_players -> name,name) == 0){
		prec = club -> injured_players;
		/*if(club  -> injured_players -> next == NULL){
			free(prec);
		}*/
		if(club->injured_players->prev != NULL)
			club  -> injured_players -> prev = NULL;
		club  -> injured_players = club  -> injured_players -> next;
		free(prec);
		return;
	}
	if(aux -> next == NULL){
		prec -> next = NULL;
		free(aux);
		return;
	}
	prec -> next = aux -> next;
	aux  -> next -> prev = prec;
	free(aux);
}


void transfer_player(FootballClub *clubs, char *player_name, 
					char *old_club, char *new_club) {


if(exclub(clubs,old_club) == 0)
	return;
if(exclub(clubs,new_club) == 0)
	return;
		
FootballClub *club;
club  = clubs;
while(strcmp(club -> name , old_club) != 0 )
	club = club -> next;
int ok=0;
if(explayer(club,player_name) == 0)
	if (explayerac(club ,player_name) == 0)
		return;
	else
		ok=0;
else
	ok=1;
if( ok == 1){
	Player *parcurge;
	parcurge = club -> players;

	while(parcurge != NULL){

		if(strcmp(parcurge -> name,player_name) == 0){

			add_player(clubs,new_club, parcurge -> name , parcurge -> position , parcurge -> score);
			remove_player(clubs,old_club,player_name);
			return;
		}

	parcurge = parcurge -> next;
	}
}
else {

	Player *parcurge;
	parcurge = club -> injured_players;
	FootballClub *aux = clubs;
	while(strcmp(aux -> name,new_club) != 0)
		aux = aux -> next;
	while(parcurge != NULL){

		if(strcmp(parcurge -> name,player_name) == 0){
			insert_injured(aux,parcurge);
			delete_injured(club,player_name);
			return;
		}

	parcurge = parcurge -> next;
	}
}

}




void update_score(FootballClub *clubs, char *club_name, 
					char *player_name, int score) {
int ok=0;
if(exclub(clubs,club_name) == 0)
	return;
FootballClub *club;
club = clubs;
while(strcmp(club -> name , club_name) != 0)
	club = club -> next;
if(explayer(club,player_name) == 0)
	if (explayerac(club ,player_name) == 00)
		return;
	else
		ok=0;
else
	ok=1;
if( ok == 1){
	Player *aux;
	char *position;
	position = (char*)calloc(10,sizeof(char));
	if(position == NULL){
		printf("calloc fail\n");
		return;
	}

	aux = club -> players;
	while(strcmp(aux -> name,player_name)!= 0)
	aux = aux -> next;
	strcpy(position , aux -> position);
	remove_player (clubs,club_name,player_name);
	add_player(clubs,club_name,player_name,position,score);
	free(position);
	}
else{
	Player* aux;
	aux = club -> injured_players;
	while(aux != NULL){
		if(strcmp(player_name , aux -> name) == 0)
			aux -> score = score;
	aux = aux -> next;
	}
}

}

void update_game_position(FootballClub *clubs, char *club_name, 
							char *player_name, char *position, int score) {

int ok=0;
if(exclub(clubs,club_name) == 0)
	return;
FootballClub *club;
club = clubs;
while(strcmp(club -> name , club_name) != 0)
	club = club -> next;
if(explayer(club,player_name) == 0)
	if (explayerac(club ,player_name) == 00)
		return;
	else
		ok=0;
else
	ok=1;

if(ok == 1){
	remove_player(clubs,club_name,player_name);
	add_player(clubs,club_name , player_name , position ,score);
	return;

}
else{
	Player* aux;
	aux = club -> injured_players;
	while(aux != NULL){
		if(strcmp(player_name , aux -> name) == 0)
			strcpy(aux -> position , position);
	aux = aux -> next;
	}
return;
}

}

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
if(exclub(clubs,club_name) == 0)
	return;
FootballClub* club;
club = clubs;
while(strcmp(club -> name,club_name) != 0 )
	club = club  -> next;

if(explayer(club,player_name) == 0)
	return;

Player *parcurge;
parcurge = club -> players;


while(strcmp(parcurge -> name , player_name) != 0 )
	parcurge = parcurge -> next;
///////////Calcul scor//////////////////
parcurge->score = parcurge->score - 0.1*days_no;
	if(parcurge->score < -100)
		parcurge->score = -100;
	if(parcurge->score > 100)
		parcurge->score = 100;
//////////////////////////////////////////
insert_injured(club,parcurge);
remove_player(clubs,club_name,player_name);

}

void recover_from_injury(FootballClub *clubs, char *club_name, 
							char *player_name) {

if(exclub(clubs,club_name) == 0)
	return;


FootballClub* club;
club = clubs;
while(strcmp(club -> name,club_name) != 0 )
	club = club  -> next;

if(explayerac(club,player_name)==0){

	return;
}

Player *accidentati,*prec,*el;
accidentati = club->injured_players;
if(accidentati == NULL)
	return;
while(strcmp(accidentati -> name ,player_name) != 0){
	prec = accidentati;
	accidentati = accidentati -> next;
}
add_player(clubs,club_name,player_name,accidentati -> position ,accidentati -> score);

if(accidentati -> next == NULL && accidentati -> prev == NULL){
	club -> injured_players = NULL;
	free(accidentati);
	return;
}
if(accidentati -> prev == NULL){
	el = accidentati;
	accidentati = accidentati -> next;
	accidentati -> prev = NULL;
	club -> injured_players = accidentati;
	free(el);
	return;
}
if(accidentati -> next == NULL){
	prec -> next = NULL;
	free(accidentati);
	return;
}
prec -> next = accidentati -> next;
el = accidentati;
accidentati = accidentati -> next;
accidentati -> prev = prec;
free(el);
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {

Player *aux2,*el;
aux2 = player;

while(aux2 != NULL){
	free(aux2 -> name);
	free(aux2 -> position);
	el = aux2;
	aux2 = aux2 -> next;
	free(el);
}

}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
FootballClub *aux,*el;
aux = clubs;
while(aux != NULL){
	destroy_player_list(aux -> players);
	destroy_player_list(aux -> injured_players);
	free(aux -> name);
	el=aux;
	aux= aux -> next;
	free(el);
	
	}


}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	while (player) {
		fprintf(f, "(%s, %s, %d, %c) ", 
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	if (player) {
		while (player->next) {
			player = player->next;
		}
		while (player) {
			fprintf(f, "(%s, %s, %d, %c) ", 
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}


// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
	fprintf(f, "FCs:\n");
	while (clubs) {
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}

#endif // FOOTBALL_CLUB_H_INCLUDED
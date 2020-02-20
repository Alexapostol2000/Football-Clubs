
#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

Player *Sorteaza1(Player* first){
	Player *a,*b,*interschimba;
	for(a = first; a -> next != NULL ; a = a -> next){
		for (b = a -> next; b != NULL ; b = b -> next)
		{
			if(a -> score < b -> score){
				interschimba = (Player*)calloc(1,sizeof(Player));
				interschimba -> name = (char*)calloc(10,sizeof(char));
				interschimba -> position = (char*)calloc(10,sizeof(char));
				strcpy(interschimba -> name , a -> name);
				strcpy(interschimba -> position , a-> position);
				interschimba -> score = a -> score;	
				interschimba -> injured = a -> injured;
				strcpy(a -> name,b -> name);
				strcpy(a -> position , b -> position);
				a -> score = b -> score;
				a -> injured = b -> injured;
				strcpy(b -> name,interschimba -> name);
				strcpy(b -> position,interschimba -> position);
				b -> score = interschimba -> score;	
				b -> injured =  interschimba -> injured;
				free(interschimba);
			}
		}
	}
	for(a = first; a -> next != NULL ; a = a -> next){
		for (b = a -> next; b != NULL ; b = b -> next)
		{
			if(a -> score == b -> score && strcmp(a -> name,b -> name) > 0){
				interschimba = (Player*)calloc(1,sizeof(Player));
				interschimba -> name = (char*)calloc(10,sizeof(char));
				interschimba -> position = (char*)calloc(10,sizeof(char));
				strcpy(interschimba -> name , a -> name);
				strcpy(interschimba -> position , a-> position);
				interschimba -> score = a -> score;	
				strcpy(a -> name,b -> name);
				strcpy(a -> position , b -> position);
				a -> score = b -> score;
				strcpy(b -> name,interschimba -> name);
				strcpy(b -> position,interschimba -> position);
				b -> score = interschimba -> score;	
				free(interschimba);
			}
		}
	}
return first;

}



Player *copylist(Player* list){
	Player* copy,*aux,*first,*aux2;
	copy= (Player*)calloc(1,sizeof(Player));
	copy -> name = (char*)calloc(10,sizeof(char));
	copy -> position = (char*)calloc(10,sizeof(char));
	aux=list;
	strcpy(copy -> name , aux -> name);
	strcpy(copy -> position , aux -> position);
	copy -> score = aux -> score;
	copy -> injured = aux -> injured;
	copy -> prev = NULL;
aux = aux -> next;
	if( aux == NULL){
		copy -> next = NULL;
		return copy;
	}
first = copy;
while(aux){
	aux2= (Player*)calloc(1,sizeof(Player));
	aux2 -> name = (char*)calloc(10,sizeof(char));
	aux2 -> position = (char*)calloc(10,sizeof(char));

	strcpy(aux2 -> name , aux -> name);
	strcpy(aux2 -> position , aux -> position);
	aux2 -> score = aux -> score;
	aux2 -> injured = aux -> injured;
copy -> next = aux2;
aux2 -> prev = copy;
copy = copy -> next;
aux = aux -> next;
}
copy ->next = NULL;
return first;
}


Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
if(exclub(clubs,club_A) == 0)
	return NULL;
if(exclub(clubs,club_B) == 0)
	return NULL;
FootballClub* aux,*club1,*club2;
aux =  clubs;
while(aux != NULL){
	if(strcmp(aux -> name,club_A) == 0)
		club1 = aux;
	if(strcmp(aux -> name,club_B) == 0)
		club2 = aux;
aux = aux -> next;
}

aux = (FootballClub*)calloc(1,sizeof(FootballClub));
aux -> name = (char*)calloc(10,sizeof(char));
strcpy(aux -> name,"union");
Player *a,*b;
a = club1 -> players;
b = club2 -> players;
while(a != NULL){
	add_player(aux,"union",a -> name,a -> position ,a -> score);
	a = a-> next;
}

while(b != NULL){
	add_player(aux,"union",b -> name,b -> position ,b -> score);
	b = b-> next;
}
return aux -> players;
	return NULL;
}

Player *get_best_player(FootballClub *clubs, char *position) {
	Player* best;
	best = (Player*)calloc(1,sizeof(Player));
	best -> name = (char*)calloc(30,sizeof(char));
	best -> position = (char*)calloc(10,sizeof(char));
	best -> next = NULL;
	best -> prev = NULL;
	best -> injured = 0;
	int max = -101;
	FootballClub *club=clubs;
	while(club != NULL){

			if(expos(club,position) == 0 ){
				club = club -> next;
				if(club == NULL)
					break;
			}
		Player* jucatori = club -> players;
		

		while(jucatori != NULL){
			if(strcmp(jucatori -> position,position) == 0){
				
				if(jucatori -> score == max){
					if( strcmp(best -> name,jucatori -> name) > 0){
					strcpy(best -> name,jucatori -> name);
					strcpy(best -> position , jucatori -> position);
					best -> score = jucatori -> score;
					}
				}
				if(jucatori -> score > max){
					max= jucatori -> score;
					strcpy(best -> name,jucatori -> name);
					strcpy(best -> position , jucatori -> position);
					best -> score = max;
				}
		}
		jucatori = jucatori-> next;
		}
	club = club -> next;
	
	}
	
	return best;
}

Player *get_top_players(FootballClub *clubs, int N) {

Player *list,*first,*jucatori;
int nr;
FootballClub* club;
list = (Player*) calloc(1,sizeof(Player));
list -> name = (char*)calloc(10,sizeof(char));
list -> position = (char*)calloc(10,sizeof(char));
first = list;
list -> prev = NULL;
club = clubs;
while(club != NULL){
	nr = 0;
	int ok = 0;
	jucatori = club ->players;
	while(jucatori){
		nr++;
		jucatori = jucatori -> next;
	}
	if(N == 1 && nr >=1){
		Player* auxl;
		auxl = copylist(club -> players);
		Sorteaza1(auxl);
		
	 Player* aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,auxl -> name);
			strcpy(aux -> position,auxl -> position);
			aux -> score = auxl -> score;
			aux -> injured = 0;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
	ok=1;
	}
	if(ok == 0){

	jucatori = club ->players;
	
	if(nr <= N){
		
		while(jucatori){
			Player* aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,jucatori -> name);
			strcpy(aux -> position,jucatori -> position);
			aux -> score = jucatori -> score;
			aux -> injured = 0;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
			
			jucatori = jucatori -> next;
			if(jucatori == NULL && club -> next == NULL)
				list -> next = NULL;
		}
	
	}

	else{nr = N;
		Player *auxlist;
		auxlist = copylist(jucatori);

		while(nr != 0){
			int poz = 0,contor = 0,max = -100;
			Player* parcurge = auxlist;
			while(parcurge){
				contor++;
				if(parcurge -> score > max){
					char* nume = (char*) calloc(10,sizeof(char));
					strcpy(nume,parcurge -> name);
					max = parcurge -> score;	
					poz = contor;
					if(parcurge -> next != NULL)
					parcurge = parcurge -> next;
					
					while(parcurge != NULL){
						contor++;

						if(parcurge -> score == max){
							if(strcmp(parcurge -> name , nume) < 0){
								strcpy(nume,parcurge -> name);
								poz = contor;
							}
						}
					parcurge = parcurge -> next;
					}
					if(N == 1)
						printf("%s\n",nume );
				free(nume);
				}
				if(parcurge == NULL)
					break;
			parcurge = parcurge -> next;
			}
			

			parcurge = auxlist;
			contor = 0;
			while(parcurge != NULL){
				contor ++;
				if(contor == poz){
					Player* aux = (Player*)calloc(1,sizeof(Player));
					aux -> name = (char*)calloc(10,sizeof(char));
					aux -> position = (char*)calloc(10,sizeof(char));

					strcpy(aux -> name,parcurge -> name);
					strcpy(aux -> position,parcurge -> position);
					aux -> score = parcurge -> score;
					aux -> injured = 0;
					
					list -> next = aux;
					aux ->prev = list;
					list = list -> next;
					parcurge -> score = -101;
					break;
					}
			parcurge = parcurge -> next;
			}

			nr--;
		}
		destroy_player_list(auxlist);
	}
}
club = club -> next;
}
list -> next = NULL;
Player* elibereaza;
elibereaza = first;
first = first -> next;
first -> prev = NULL;
free(elibereaza -> name);
free(elibereaza -> position);
free(elibereaza);
first = Sorteaza1(first);
return first;
}


Player *get_players_by_score(FootballClub *clubs, int score) {
FootballClub *club;
club = clubs;
Player* l,*list,*aux,*first;
list = (Player*) calloc(1,sizeof(Player));
list -> name = (char*)calloc(10,sizeof(char));
list -> position = (char*)calloc(10,sizeof(char));
first = list;
list -> prev = NULL;
while(club){
l = club -> players;
while(l){
	if(l -> score >= score){
		aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = 0;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
	}
l = l -> next;
}
l = club -> injured_players;
while(l){
	if(l -> score >= score){
		aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = l -> injured;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
	}
l = l -> next;
}
club = club -> next;
}	
list -> next = NULL;
Player* elibereaza;
elibereaza = first;
first = first -> next;
first -> prev = NULL;
free(elibereaza -> name);
free(elibereaza -> position);
free(elibereaza);
first = Sorteaza1(first);
elibereaza = first;


return first;
}

Player *get_players_by_position(FootballClub *clubs, char *position) {
Player *list,*first,*parcurge;
list = (Player*)calloc(1,sizeof(Player));
first = list;
FootballClub* club = clubs;
while(club){
	parcurge = club -> players;
	while(parcurge){
		if(strcmp(parcurge -> position,position)==0){
			Player* aux;
			aux = (Player*)calloc(1,sizeof(Player));
			aux -> name =(char*)calloc(1,sizeof(char));
			aux -> position = (char*)calloc(1,sizeof(char));
			strcpy(aux -> name , parcurge -> name);
			strcpy(aux  -> position , parcurge -> position);
			aux  -> score = parcurge -> score;
			aux  -> injured = parcurge -> injured;
			list -> next = aux;
			aux -> prev = list;
			list = list -> next;
		}
	parcurge = parcurge -> next;
	}
parcurge = club -> injured_players;
	while(parcurge){
		if(strcmp(parcurge -> position,position)==0){
			Player* aux;
			aux = (Player*)calloc(1,sizeof(Player));
			aux -> name =(char*)calloc(1,sizeof(char));
			aux -> position = (char*)calloc(1,sizeof(char));
			strcpy(aux -> name , parcurge -> name);
			strcpy(aux  -> position , parcurge -> position);
			aux  -> score = parcurge -> score;
			aux  -> injured = parcurge -> injured;
			list -> next = aux;
			aux -> prev = list;
			list = list -> next;
		}
	parcurge = parcurge -> next;
	}
club = club  -> next;
}

list -> next = NULL;
//Player* elibereaza;
//elibereaza = first;
first = first -> next;
first -> prev = NULL;
//free(elibereaza -> name);
//free(elibereaza -> position);
//free(elibereaza);
first = Sorteaza1(first);

return first;

}

Player *get_best_team(FootballClub *clubs) {

FootballClub *club,*nou;
if(clubs == NULL)
	return NULL;
Player *aux;
club = clubs;
nou = (FootballClub*)calloc(1,sizeof(FootballClub));
nou -> name = (char*)calloc(10,sizeof(char));
strcpy(nou -> name , "Best");

while(club){
aux = club -> players;
while(aux){
	add_player(nou,"Best",aux -> name , aux -> position , aux -> score);
aux = aux -> next;
}
club = club -> next;
}



Player *list,*first,*jucatori,*l;
list = (Player*)calloc(1,sizeof(Player));
first = list;
int nr;	
jucatori = nou -> players;

if(jucatori != NULL){

	 l = get_players_by_position(nou,"atacant");
nr = 3;

		 	while(nr != 0 && l != NULL){
		 	
		 	aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = l -> injured;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
			nr -- ;
		
			l = l -> next;
			}
	

	Player *l = get_players_by_position(clubs, "fundas");
	
	nr = 4;
		
		 	while(nr != 0 && l != NULL){
		 		
		 	aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = l -> injured;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
			nr -- ;
		
				l = l -> next;
		
			}

l = get_players_by_position(nou,"mijlocas");
nr = 3;

		 	while(nr != 0 && l != NULL){
		 		
		 	aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = l -> injured;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
			nr -- ;
		
			l = l -> next;
			}
	
l = get_players_by_position(nou,"portar");
nr=1;

		 	while(nr != 0 && l != 0){
		 		
		 	aux = (Player*)calloc(1,sizeof(Player));
			aux -> name = (char*)calloc(10,sizeof(char));
			aux -> position = (char*)calloc(10,sizeof(char));

			strcpy(aux -> name,l -> name);
			strcpy(aux -> position,l -> position);
			aux -> score = l -> score;
			aux -> injured = l -> injured;
			
			list -> next = aux;
			aux ->prev = list;
			list = list -> next;
			nr -- ;

			l = l -> next;
			}
	

}

list -> next = NULL;
Player* elibereaza;
elibereaza = first;
first = first -> next;
first -> prev = NULL;
free(elibereaza -> name);
free(elibereaza -> position);
free(elibereaza);
destroy_club_list(nou);
first = Sorteaza1(first);



return first;


}

#endif // TEAM_EXTRACTOR_H_INCLUDED
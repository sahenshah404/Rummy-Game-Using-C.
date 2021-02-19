#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct deck
 {
 	char suit[11];
 	char rank[5];
 }deck;

typedef struct node
{
	char suit[10];
	char rank[10];
   	struct node *next;
   	struct node *prev;
}node;


 char suits[4][10]={"clover","spades","hearts","diamonds"};
 char ranks[13][5]={"a","2","3","4","5","6","7","8","9","10","j","q","k"};



deck* rawdeck()
{
	int i,j,cardno=0;
	deck *newdeck,*cards;



	cards=(deck*)malloc(52*sizeof(deck));
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 13; ++j)
		{


			strcpy(cards[cardno].suit,suits[i]);
			strcpy(cards[cardno].rank,ranks[j]);
			cardno++;

		}
	}
		newdeck=cards;



	return newdeck;
};

deck* leftdeck()
{
	deck *cards;

	cards=(deck*)malloc(26*sizeof(deck));

	return cards;

};

node* createnode(char rank[10],char suit[10])
{
    node *newnode;

    newnode=(node*)malloc(sizeof(node));
    newnode->next=NULL;
    newnode->prev=NULL;
    strcpy(newnode->rank,rank);
    strcpy(newnode->suit,suit);

    return newnode;

};
displaycards(node *head)
{
	int count=0;
	printf("\n-----------------\nyour cards are \n------------------\n");
	while(1)
	{
		count++;
		printf("no.%d\t%s %s\n",count,head->rank,head->suit);
		if(head->next!=NULL)
    		{
    			head=head->next;
    		}
    		else
    		{
    			printf("---------------\n");
    			break;
    		}
	}

};

displaydeck(deck *deck,int size)
{
	int i;
	printf("\n---- deck is-----\n");
	for(i = 0; i < size; ++i)
	{
		printf("%s %s\n",deck[i].rank,deck[i].suit);
	}
};

 deck* shuffle(deck *rawdeck,int size)
{
	deck temp,*newdeck;
	int random1,random2,i;

	for (i = 0; i < size; ++i)
	{
		random1=rand();
		random1=random1%size;
		random2=rand();
		random2=random2%size;

		temp=rawdeck[random1];
		rawdeck[random1]=rawdeck[random2];
		rawdeck[random2]=temp;

	}
	newdeck=rawdeck;
	return newdeck;



};

dealing(deck *newdeck,node **p1,node **p2)
{
	node *pl1,*pl2,*newnode;
	char rank[10];
	char suit[10];
	int first=1,count=0;


	for (int i = 0; i < 13; ++i)
	{

		strcpy(rank,newdeck[count].rank);
		strcpy(suit,newdeck[count].suit);

		newnode=createnode(rank,suit);
		if(first==1)
		{
			*p1=newnode;
			pl1=*p1;

		}
		else
		{
			pl1->next=newnode;
			newnode->prev=pl1;
			pl1=newnode;
		}

		count++;

		strcpy(rank,newdeck[count].rank);
		strcpy(suit,newdeck[count].suit);
		newnode=createnode(rank,suit);
		if(first==1)
		{
			*p2=newnode;
			pl2=*p2;
		}
		else
		{
			pl2->next=newnode;
			newnode->prev=pl2;
			pl2=newnode;
		}
		first++;
		count++;
	}



};
swap(node *cards)
{
	int card1,card2,i;
	node *temp1,*temp2,*temp3;

	system("cls");

	displaycards(cards);
	printf("\nselect the two card no. to be swapped\n");
	printf("first card no.--\n");
	scanf("%d",&card1);
	printf("second card no.--\n");
	scanf("%d",&card2);
	card2--;
	card1--;
	temp1=cards;
	temp2=cards;
	for (i = 0; i < card1; ++i)
	{
		temp1=temp1->next;
	}
	for (i = 0; i < card2; ++i)
	{
		temp2=temp2->next;
	}

	temp3=createnode(temp1->rank,temp1->suit);


	strcpy(temp1->rank,temp2->rank);
	strcpy(temp1->suit,temp2->suit);

	strcpy(temp2->rank,temp3->rank);
	strcpy(temp2->suit,temp3->suit);


	printf("\ndo you want to swap or sort more cards y/n\n" );
	if (getch()=='y')
	{
		swap(cards);
	}
}

node* keepremaining(deck *deckremaining, deck *newdeck)
{
	int j=0,i;
	for (i = 26; i < 52; ++i)
	{
		deckremaining[j]=newdeck[i];
		j++;
	}
	return deckremaining;
};

node* todeck(deck *deckremaining, deck *droppedcards)
{
	int i;
	for (i = 0; i < 26; ++i)
	{
		deckremaining[i]=droppedcards[i];

	}
	return deckremaining;
};


deck* insertdeck(deck *card, node *cards,deck *droppedcards, int tablecards)
{
	int no,i;
	node *temp=cards;


	system("cls");
	displaycards(cards);

	printf("\n\npicked up card is -- %s %s\n",card[0].rank,card[0].suit );
	printf("enter the  card no. which you want to drop\n");
	scanf("%d",&no);
	no--;
	for (i = 0; i < no; ++i)
	{
		temp=temp->next;
	}

	strcpy(droppedcards[tablecards].rank,temp->rank);
	strcpy(droppedcards[tablecards].suit,temp->suit);

	strcpy(temp->rank,card[0].rank);
	strcpy(temp->suit,card[0].suit);



	return droppedcards;



};
int strtoint(char str[5])
{
	if(str!="a" && str!="k" && str!="q" && str!="j")
	{
		return atoi(str);
	}


		if(str=="a")
			 return 14;

		if(str=="k")
			return 13;

		if(str=="q")
			return 12;

		if(str=="j")
			return 11;


};

int wincheck(node *cards)
{
	node *head;
	int seq=0,set=0,triplet=0,a,count=0,j,i,total;

	head=cards;



		head=head->next;
		count++;

		for (int i = 0; i < 3; ++i)
		{

			if((strcmp(head->prev->rank,"a")==0) && (((strcmp(head->rank,"2")==0) && (strcmp(head->next->rank,"3")==0)) ))
			{
				seq++;
			}

			else if((strtoint(head->prev->rank)+1==strtoint(head->rank)) && ((strtoint(head->rank)+1==strtoint(head->next->rank))
) )
					{
						seq++;
					}


			else if(strcmp(head->prev->suit,head->suit)==0 && (strcmp(head->suit,head->next->suit)==0))
					{
							set++;
					}

					 else if(strcmp(head->prev->rank,head->rank)==0)
					{
						if(strcmp(head->rank,head->next->rank)==0)
						{
							triplet++;
						}
					}



			for(j=0;j<3;j++)
			{
				head=head->next;



			}


		}




		if(strcmp(head->prev->rank,"a")==0)
		{
			if((strcmp(head->rank,"2")==0) && (strcmp(head->next->rank,"3")==0))
			{
				if(strcmp(head->next->next->rank,"4")==0)
				{
					seq++;
					goto esc2;
				}
			}
		}

			 if(strtoint(head->prev->rank)+1==strtoint(head->rank) )
				{
					if(strtoint(head->rank)+1==strtoint(head->next->rank))
					{
						if(strtoint(head->next->rank)+1==strtoint(head->next->next->rank))
						{
							seq++;
							goto esc2;
						}
					}
				}

		 if(strcmp(head->prev->rank,head->rank)==0)
			{
				if(strcmp(head->rank,head->next->rank)==0)
				{
					if(strcmp(head->next->rank,head->next->next->rank)==0)
					{
						triplet++;
						goto esc2;
					}
				}
			}

		 if(strcmp(head->prev->suit,head->suit)==0)
				{
					if(strcmp(head->suit,head->next->suit)==0)
					{
						if(strcmp(head->next->suit,head->next->next->suit)==0)
						{
							set++;
							goto esc2;
						}
					}
				}








    esc2:
    total=set+seq+triplet;
    printf("\nyour score is %d\n",total );
    getch();
    if(total>=4 && seq>=2)
		{return 1;}
	else
		{return 0;}
};



void main()
{
	int i=0,turn=1,choice,choice2,tablecards=0,tabledecktop=0,win=0;
	deck *newdeck,*droppedcards,*deckremaining,card[1];
	node *p1,*p2,*head;
	char player1[10],player2[10];

	srand(time(0));

	printf("----Hello Players to the game RUMMY---\n");
	printf("player 1 enter your name\n");
	scanf("%s",player1);
	printf("player 2 enter your name\n");
	scanf("%s",player2);
	printf("player1 is-%s\nplayer2 is-%s\n",player1,player2 );

	newdeck=rawdeck();

	droppedcards=leftdeck();		//for the dropped cards on table
	deckremaining=leftdeck();		//for the cards remaining in the deck after dealing

	newdeck=shuffle(newdeck,52);	//shuffling the deck


	dealing(newdeck,&p1,&p2);		//dealing the deck

	deckremaining=keepremaining(deckremaining,newdeck);	//transferring the remaining 26 cards in new deck


	while(1)
	{
		if(turn==1)
		{
			turn++;
			system("cls");

			printf("this is %s turn\n", player1);
			printf("press any key to continue...\n");
			getch();
			printf("your cards are\n" );
			displaycards(p1);
			printf("options:-- \n1-swap or sort your cards\n");
			printf("2-pick up a card\n3-surrender and exit\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1: swap(p1);
				case 2: printf("\npress 1 to pick up card from deck \n");
						if(tablecards!=0)
							printf("\npress 2 to pick up card from table \n");
						scanf("%d",&choice2);
						if(choice2==1)
						{
							card[0]=deckremaining[tabledecktop];
							tabledecktop++;
							printf("the card is\n%s %s\n", card[0].rank,card[0].suit);
							printf("you want to take this card or drop it  y/n\n");
							if(getch()=='y')
							{
								droppedcards=insertdeck(card,p1,droppedcards,tablecards);
								tablecards++;

							}
							else
							{
								strcpy(droppedcards[tablecards].rank,card[0].rank);
								strcpy(droppedcards[tablecards].suit,card[0].suit);
								tablecards++;

							}
						}
						else if (choice2==2)
						{
							card[0]=droppedcards[tablecards-1];
							droppedcards=insertdeck(card,p1,droppedcards,tablecards-1);
						}

						break;
					case 3: printf("%s surrendered %s wins\n",player1,player2);
						exit(0);

				};

			if(tablecards>25)
						{
							droppedcards=shuffle(droppedcards,26);
							deckremaining=todeck(deckremaining,droppedcards);
							tablecards=0;
							tabledecktop=0;
						}


						win=wincheck(p1);
						if(win){
							printf("player %s wins \n",player1);
							displaycards(p1);
							getch();
							exit(0);
						}

		}




		else if(turn==2)
		{
			turn--;
			system("cls");
			printf("this is %s turn\n", player2);
			printf("press any key to continue...\n");
			getch();
			printf("your cards are\n");
			displaycards(p2);

			printf("options:-- \n1-swap or sort your cards\n");
			printf("2-pick up the a card\n3-surrender and exit\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1: swap(p2);
				case 2: printf("\npress 1 to pick up card from deck \n");
						if(tablecards!=0)
							printf("\npress 2 to pick up card from table \n");
						scanf("%d",&choice2);
						if(choice2==1)
						{
							card[0]=deckremaining[tabledecktop];
							tabledecktop++;
							printf("the card is\n%s %s\n", card[0].rank,card[0].suit);
							printf("you want to take this card or drop it  y/n\n");
							if(getch()=='y')
							{
								droppedcards=insertdeck(card,p2,droppedcards,tablecards);
								tablecards++;

							}
							else
							{
								strcpy(droppedcards[tablecards].rank,card[0].rank);
								strcpy(droppedcards[tablecards].suit,card[0].suit);
								tablecards++;

							}
						}
						if (choice2==2)
						{
							card[0]=droppedcards[tablecards-1];
							droppedcards=insertdeck(card,p2,droppedcards,tablecards-1);
						}

						break;
						case 3: printf("%s surrendered %s wins\n",player2,player1);
						exit(0);


			};


			if(tablecards>25)
						{
							droppedcards=shuffle(droppedcards,26);
							deckremaining=todeck(deckremaining,droppedcards);
							tablecards=0;
							tabledecktop=0;
						}



			win=wincheck(p2);
						if(win){
							printf("player %s wins \n",player2);
							displaycards(p2);
							getch();
							exit(0);
						}
		}

	}
}


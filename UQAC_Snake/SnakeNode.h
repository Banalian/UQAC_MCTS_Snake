#pragma once
#include"SnakeStruct.h"
#include<iostream>
#include<algorithm>

class SnakeNode
{
public:	
	//constructor
	SnakeNode(SnakeNode * par,int moves, unsigned char d, int num, Snake oldseg[600], Fruit f, int v=0, int w=0);
	~SnakeNode();

	//add the child(ren)
	void addchildren(void);
	void add1child(int);

	void expendTree(void);//fill the entire sub-tree

	//update the fruit pos and length of the snake
	void updateFruit(int number, unsigned char fruitx, unsigned char fruity);

	//MCTS-related functions
	void addVisitsOrWins(int, int);
	int getVisits(void);
	int getWins(void);
	//Also MCTS :  input is void because they update based on the child's informations
	int updateVisits(void);
	int updateWins(void);

	//old function
	//bool killedHimself(int, Snake);

	//not working at the moment, the recursive function isn't correct
	//you can fix it if needed, to check how much moves are needed at least to get to a fruit, if possible
	int postorderTraversal(void);
		
	bool assertchildren(void);
	bool assertchild(int);

	//informations on the current game :  direction, positions, is it the end ? and other things
	unsigned char dir;
	int movesSinceLastFruit;
	bool eatHimself, eatAppleThisMove;
	//length of the snake
	int numb;
	
	SnakeNode *parent;
	SnakeNode *children[3];
	//get a pointer to the start of the array keeping tracks of the segments
	Snake *getsnakesseg();
private : 
	Snake snakeseg[600];
	Fruit fruitpos;
	//informations for the MCTS
	int visits, wins;
};





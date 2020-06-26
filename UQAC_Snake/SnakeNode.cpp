#include "SnakeNode.h"

SnakeNode::SnakeNode(SnakeNode * par, int moves, unsigned char d,int num, Snake oldseg[600], Fruit f, int v, int w)
{

	parent = par;
	movesSinceLastFruit = moves;
	dir = d;
	numb = num;

	//make the imaginary move
	for (char i = 0; i < num+1; i++)snakeseg[i] = oldseg[i];
	//snakehead = oldhead;

	for (char i = num; i>0; --i)
	{
		snakeseg[i].x = snakeseg[i - 1].x; snakeseg[i].y = snakeseg[i - 1].y;
	}

	if (dir == 0) snakeseg[0].y += 1;
	if (dir == 1) snakeseg[0].x -= 1;
	if (dir == 2) snakeseg[0].x += 1;
	if (dir == 3) snakeseg[0].y -= 1;
	
	/*
	if (dir == 0) snakehead.y += 1;
	if (dir == 1) snakehead.x -= 1;
	if (dir == 2) snakehead.x += 1;
	if (dir == 3) snakehead.y -= 1;
	*/
	//OOB
	
	if (snakeseg[0].x>30 - 1) snakeseg[0].x = 0; 
	if (snakeseg[0].x<0) snakeseg[0].x = 30 - 1;

	if (snakeseg[0].y>20 - 1) snakeseg[0].y = 0; 
	if (snakeseg[0].y<0) snakeseg[0].y = 20 - 1;
	/*
	if (snakehead.x>30 - 1) snakehead.x = 0;  if (snakehead.x<0) snakehead.x = 30 - 1;
	if (snakehead.y>20 - 1) snakehead.y = 0;  if (snakehead.y<0) snakehead.y = 20 - 1;
	*/

	// get the apple pos
	fruitpos.x = f.x;
	fruitpos.y = f.y;

	//did this move killed him ?

	
	for (char i = 1; i<num; i++)
		//If Snake eats its tail, cut it
		if (snakeseg[0].x == snakeseg[i].x && snakeseg[0].y == snakeseg[i].y)  eatHimself = true ; else eatHimself =false ;
	/*
	if (parent != nullptr) {
		if (parent->killedHimself(numb, snakehead))eatHimself = true; else eatHimself = false;
	}
	else {
		eatHimself = false;
	}
	*/


	
	if ((snakeseg[0].x == fruitpos.x) && (snakeseg[0].y == fruitpos.y))
	{
		w+=1; eatAppleThisMove = true;
	}
	else {
		eatAppleThisMove = false;
	}
	/*
	if ((snakehead.x == fruitpos.x) && (snakehead.y == fruitpos.y))
	{
		w++; eatAppleThisMove = true;
	}
	else {
		eatAppleThisMove = false;
	}
	*/

	//init visit and wins

	visits = v;
	wins = w;

	
	for (char i = 0; i < 3; i++)children[i] = nullptr;
}

SnakeNode::~SnakeNode()
{

	for (char i = 0; i < 3; i++) {
		delete children[i];
		children[i] = nullptr;
	} 
	//delete [] children;
	parent = nullptr;
}

//add the child(ren)
void SnakeNode::addchildren(void)
{
	//if ((!eatHimself) /*&& (movesSinceLastFruit <150)&& (!eatAppleThisMove)*/) {
		for (int i = 0; i < 3; i++)if (assertchild(i))delete children[i];
		switch (dir) {
		case 0:
			children[0] = new SnakeNode(this, movesSinceLastFruit + 1, 1, numb, snakeseg, fruitpos, 0, 0);
			children[1] = new SnakeNode(this, movesSinceLastFruit + 1, 2, numb, snakeseg, fruitpos, 0, 0);
			children[2] = new SnakeNode(this, movesSinceLastFruit + 1, 0, numb, snakeseg, fruitpos, 0, 0);
			break;
		case 1:
			children[0] = new SnakeNode(this, movesSinceLastFruit + 1, 1, numb, snakeseg, fruitpos, 0, 0);
			children[1] = new SnakeNode(this, movesSinceLastFruit + 1, 3, numb, snakeseg, fruitpos, 0, 0);
			children[2] = new SnakeNode(this, movesSinceLastFruit + 1, 0, numb, snakeseg, fruitpos, 0, 0);
			break;
		case 2:
			children[0] = new SnakeNode(this, movesSinceLastFruit + 1, 2, numb, snakeseg, fruitpos, 0, 0);
			children[1] = new SnakeNode(this, movesSinceLastFruit + 1, 3, numb, snakeseg, fruitpos, 0, 0);
			children[2] = new SnakeNode(this, movesSinceLastFruit + 1, 0, numb, snakeseg, fruitpos, 0, 0);
			break;
		case 3:
			children[0] = new SnakeNode(this, movesSinceLastFruit + 1, 1, numb, snakeseg, fruitpos, 0, 0);
			children[1] = new SnakeNode(this, movesSinceLastFruit + 1, 2, numb, snakeseg, fruitpos, 0, 0);
			children[2] = new SnakeNode(this, movesSinceLastFruit + 1, 3, numb, snakeseg, fruitpos, 0, 0);
			break;
		
		}
		//if (movesSinceLastFruit<10) std::cout << "added childrens at layer " << movesSinceLastFruit << std::endl;

	//}
	//else {

		//std::cout << "can't add children, end of the tree" << std::endl;

	//}
	
		
	
}

//add the child(ren)
void SnakeNode::add1child(int newdir)
{
	if ((!eatHimself) && (!eatAppleThisMove)) {

		children[0] = new SnakeNode(this, movesSinceLastFruit + 1, newdir, numb, snakeseg, fruitpos, visits, wins);
		
		if (movesSinceLastFruit<10) std::cout << "added childrens at layer " << movesSinceLastFruit << std::endl;

	}
	else {

		//std::cout << "can't add children, end of the tree" << std::endl;

	}
}

//fill the entire sub-tree
void SnakeNode::expendTree(void)
{
	addchildren();
	for (char i = 0; i < 3; i++) {
		if (assertchild(i))children[i]->expendTree();
	}

	for (char i = 0; i < 3; i++) {
		if (assertchild(i)) {
			if (children[i]->getWins() == 0) {
				delete children[i];
				children[i] = nullptr;
			}
		} 
	}
}

//update the fruit pos and length of the snake
void SnakeNode::updateFruit(int number, unsigned char fruitx, unsigned char fruity)
{
	numb = number;

	fruitpos.x = fruitx;
	fruitpos.y = fruity;

}

//MCTS-related functions
void SnakeNode::addVisitsOrWins(int v, int w = 0)
{

	visits += v;
	wins += w;
	return;
}

//MCTS-related functions
int SnakeNode::getVisits(void)
{
	return visits;
}

//MCTS-related functions
int SnakeNode::getWins(void)
{
	//int tempwins = wins;
	//for (char i = 0; i < 3; i++) if (children[i] != nullptr) tempwins = children[i]->getWins();
	return wins;
}

//MCTS-related functions
//input is void because they update based on the child's informations
int SnakeNode::updateVisits(void)
{
	int tempvisits = 0;

	for (char i = 0; i < 3; i++) if(assertchild(i))tempvisits+=children[i]->updateVisits();

	visits = ++tempvisits;

	return visits;

}

//MCTS-related functions
//input is void because they update based on the child's informations
int SnakeNode::updateWins(void)
{
	int tempwins = 0;

	for (char i = 0; i < 3; i++) if (assertchild(i))tempwins += children[i]->updateWins();

	wins = tempwins;

	return wins;
}


//old function
/*bool SnakeNode::killedHimself(int cpt, Snake head)
{
	if(cpt<=0)return false;
	if (parent == nullptr) return false;
	if ((head.x == snakehead.x) && (head.x == snakehead.x))return true;
	

	return parent->killedHimself(cpt - 1,head);
	
}*/

//not working at the moment, the recursive function isn't correct
//you can fix it if needed, to check how much moves are needed at least to get to a fruit, if possible
int SnakeNode::postorderTraversal(void)
{

	int bestmove = 999;

	for (char i = 0; i < 3; i++) {
		if (assertchild(i)) if (children[i]->eatAppleThisMove) {
			bestmove = std::min(children[i]->postorderTraversal(), movesSinceLastFruit);
		}
		else {
			children[i]->postorderTraversal();
		} 

	} 
	return bestmove;

}

//test/assert to be sure that there are children so we don't have any nullptr error
bool SnakeNode::assertchildren(void)
{
	for (int i = 0; i < 3; i++) {
		if (children[i] == nullptr)return false;
	}
	return true;
}

//test/assert to be sure that there are children so we don't have any nullptr error
bool SnakeNode::assertchild(int i)
{
	if (children[i] == nullptr)return false;
	return true;
}

//get a pointer to the start of the array keeping tracks of the segments
Snake * SnakeNode::getsnakesseg()
{
	return snakeseg;
}

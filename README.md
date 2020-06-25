# UQAC_MCTS_Snake
Snake Game with a MCTS to predict your next move


This code use a Monte Carlo Tree Search algorithm to predict what move the player will choose based on which move leads to victory.
The code can be modified, and has comments to understand how it works. If needed, you can contact me to understand the code better.

YOU NEED VS 2017 TO RUN THIS.
Don't forget to check if the SFML library is correctly added (follow to tutorial on their website to check)


Made by Lilian "Banalian" Pouvreau
For any questions/help with this code
Mail    : lilian.pouvreau@free.fr
Discord : Banalian#0584
Open source code :can be used and modified by anyone at anytime as long as credit is given


for any french programmer :
tout les commentaires de ce code sont en anglais,
car j'ai pour habitude de coder en anglais,et si j'ai besoin d'aide,
il est plus simple de partager des morceaux de code déjà en anglais


useful tips imo :
- when deleting a object via a pointer using "delete" make sure to make it a nullptr afterward, for the assertions to work
- remember to check the project's settings to be sure that sfml is correctly installed(check their tutorial to be sure)

Things that can be done :
- keep the tree in a file to re-use it :use serialization via the boost library (Big things to do, IMO)
- switch arrays for vectors (should be done quickly, just adapt the code)
- create a vector to have multiples fruits at once(should be done quickly, just adapt the code)
- fix the postorderTraversal function (no idea of how easy it can be to fix)
- make the MCTS better by saying that a move is better if it gets us closer to a fruit (mostly useful with one fruit)
 

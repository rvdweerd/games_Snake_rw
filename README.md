# games_Snake_rw
Naive Snake Game implementation. </br>
An array[fieldHeight*fieldWidth] holds integer values representing the number of timesteps that particular cell should be printed. This can be used to 
* move the snake (next cell in direction of travel = value of head cell+1), (all cells in array -= 1)
* grow the snake (all cells in array > 0: +=1)


This README will serve as the documentation and an introduction to my project.  
  
This is a Connect 4 game made for the STM32F429I. It was based on an already implemented setup for LCD touch screen but everything else was created by myself.
More functions were added to the LCD_Driver fileset to display the game board, start screen, win screen, and to detect touches on the screen. The actual Connect 4 logic such as
dropping pieces and checking for wins can be found in the aptly titled Game_Logic fileset. With this as the structure, the rest of the gameplay experience is located in the 
ApplicationCode fileset, which goes through the game states, controls the screen, and receives input.  
  
The code can be set up in an existing STM32CubeIDE project, given that there's already HAL drivers configured.  
  
The first screen allows the user to choose to play in 1 player or 2 player mode. 1 player mode involves playing against a computer, in this case one that is at least
semi-intelligent, as per the extra credit opportunity. This "intelligence" allows the computer to see and play winning moves, to see if the player can win in the next turn and 
if so stops them, and only then if it sees none of these does it choose a random move biased toward the middle. This means that winning takes more than just naively placing 4 in a row.
Instead, the only two ways I've found to win are to create two opportunites to win at the same time so that the computer can only block one, or for the computer to mistakenly 
set up a win opportunity for the player in its turn. The screen needs to be tapped for the computer to play its move. 2 player mode just alternates between the two players. 
After a win or tie a scoreboard is shown with the time the game took at the bottom, and another game in the same game mode can be played by pressing the button. The game is played
by tapping on the left side of the screen to move the piece to the left and on the right to move the piece to the right. Then press the button to drop the piece. If you try to 
drop a piece in an already full column nothing will happen.  
  
I hope you liked my project :)

# BullCowGame

This is a texted based game where the user must guess the isogram, a word with no repeating characters. First the user enters how many 
letters they want in isogram there guessing. Then once they have chosen the amount of letters, they try and guess what the isogram is in a 
certain amount of tries. The amount of tries changes with the amount of letters. If the user does not enter an isogram, a word with 
symbols or upper case letters, or a word with letters unequal to that of the hidden word, they are thrown an error and their current
amount of tries does not increase. Once the user enters a word following those guidelines they will recieves their number of bulls and 
cows. Getting bulls means the user has letters of the hidden word in the correct location. For example, if the hidden word is "plan" and
the user guessed "pain" they would have 2 bulls for the 'p' and the 'n'. However they do not know what the letters they got right are. 
Getting cows means the user got letters in the hidden word, but in the wrong location. Using the example above they would get 1 cow for 
the letter 'a', but again they would not be given what that letter is. The game ends in two ways. First, the user is able to figure out 
the word, so they win. The second is the user runs out of chances, so they lose. The user is then asked if they want to play again. If 
yes the process repeats, if no the game ends.

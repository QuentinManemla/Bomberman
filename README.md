# Bomberman
 
Everybody loves playing Bomberman. Good news. The goal of this project is to create
a full implementation of a 3D Bomberman video game.
 
## Objectives
 
There are several distinct objectives in this project.
 
• Being able to produce a full video game, not just a pedagogical project. This means,
that the final product should be usable by tiers, not just the students group who
wrote it. One should not think "this is some early access crap" when playing your
game.
 
• Learning the low level use of OpenGL without the help of modern game engines, and
why not start your own (tiny) little one ?
 
• Learning team work on a full scale project. Everybody can’t work on everything,
so it’s an excellent opportunity to discover that communication, management and
documentation are keys to success.
 
## Generic instructions
 
• This project must be in C++.
 
• You are free to use any compiler you like.
 
• Your code must compile with: -Wall -Wextra -Werror.
 
• You are free to use any C++ version you like.
 
• You must use the last available version of OpenGL for anything related to graphics.
 
• You are free to use any additional library you like, but NOT full game engines
like Ogre for instance.
 
• You must provide a Makefile with the usual rules.
 
• Any class that declares at least one attribute must be written in canonical form.
Inheriting from a class that declares attributes does not count as declaring attributes.
Exceptions don’t have to be canonical.
 
• It’s forbidden to implement any function in a header file, except for templates and
the virtual destructor of a base class.
 
• The “keyword” "using namespace" is forbidden.
 
 
## Generalities
 
So, here we are. You must code a 3D version of Bomberman, functional, and complete
with graphics, animations and levels. Your version being a solo game, we expect at least:
 
• The player can access a main menu allowing him to start a new game, load a save,
adjust game settings and exit the game.
 
• In game, the feeling, pace and difficulty must be as close as possible from the original
game.
 
• To beat the game, the player must win at least 3 different levels. It’s up to you to
code a longer game, but 3 levels is the minimum acceptable.
 
• If the player loses, the game must state it clearly and behave like a game should,
like restarting the current level, or issuing a game over for instance. Likewise, if
the player beats the game, it must also be stated clearly and offer a reasonable
behaviour like displaying credits and getting back to the main menu.
 
• Sounds ! Musics ! A silent video game is a crappy one ! The main menu and the 3
levels must have their own music. Also, every relevant events must trigger a sound,
like a bomb exploding, picking up a power up, killing an enemy, dying, etc.
 
## Technical aspects
 
• Your game MUST use the last version of OpenGL for anything related to graphics.
 
• The visual assets must be 3D, but the gameplay must stay 2D like the original
game. For instance, if the player dies, the camera may shift its angle and spin
around him while the death animation plays, or at the beginning of a level, the
camera may fly around the level before focusing above the player. A good exemple
of a 3D game with a 2D gameplay might be Mario Wii.
 
• Free animated 3D models of a bomberman and its enemies might be hard to find
online. As a consequence, you can skin your game as you wish and use any animated
3D model you like. The gameplay and visual feeling must be a Bomberman at first
sight, but the actual models and textures can be anything.
 
• As stated in the previous section, your main menu must allow to customize the
game settings. It must be possible to customize at least:
 
  ◦ The screen resolution
  
  ◦ Windowed or full screen mode
  
  ◦ Key bindings
  
  ◦ Music and sounds volumes
  
• The game must offer a way to save the player’s progression and restore it on demand.
It could be a regular save system or a campaign mechanic. As long as the feature
is present, it’s up to you to integrate it in your game. Anyway, This persistence
MUST remain even if the game is exited completely and executed again.
 
## To set up on WeThinkCode_ Mac OS
 
• Have Xquartz installed through Management Software Center
 
• Have brew installed ( sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)" )
 
• Have cmake installed ( brew install cmake )
 
## To set up on Linux OS
 
• Make sure cmake v3.11 or higher is installed (https://cmake.org/install/)
 
• Make sure boost is installed (https://www.boost.org/users/download/)
    • make sure it is added to your path
 
## To compile and run
 
• generate the Makefile with "cmake -B./tmp -H."
 
• compile with "make -C tmp"
 
• run with "./BomberMan"
 
![alt text](https://raw.githubusercontent.com/QuentinLucyyd/Bomberman/master/1.png)
![alt text](https://raw.githubusercontent.com/QuentinLucyyd/Bomberman/master/2.png)

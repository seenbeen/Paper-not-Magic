# Paper, not Magic

Welcome to Paper, not Magic(PnM), a small turn-based dungeon crawler produced by a pair of students.
### Premise
In PnM, you will take control of Levi, a professor and now-retired ~~magician~~ card knight. An ancient dungeon was uncovered and you were tasked by your colleagues to explore it and see what secrets it holds.

###
Levi utilizes an ancient form of ~~magic~~ fighting that involves invoking powers sealed on parchments. These parchments used to deteriorate after use but thanks to years of research, Levi has developed a method to restore power to them.

In PnM, you will be exploring a dungeon that has many floors. Unfortunetly, Levi no longer has any of his equipment from his knighting days, but he still has his trusty ~~staff~~ duel disk. In the dungeon, you will be able to find various.

### The Gameplay

You will be exploring a dungeon seperated by floors. The dungeon has enemies inside of it that you will encounter and to fight these enemies, you will be utilizing card magic.

Due to the way that taking turns work in this game, you will be required to predict what the various enemies you encounter will behave.

The gameplay is split into exploration and combat.

### Exploration
During exploration, you will wander the halls of an ancient dungeon and explore rooms. Some rooms may contain treasure such as a new magic robe for Levi, or a brand new card that he can add to his arsenal.

### Combat
During combat, the game will be put on a square grid for both you and any enemies. You will begin each combat with 6 cards in your hand.

#### Cards
You will always have a card used for walking around in your hand. 
You are limited to the actions depicted by each card.
Each card will have a mana cost, and a effect. 
Many effects will require you to target a square on the grid, or an enemy. 
Cards are consumed after the effect takes place, and you will draw new cards from your deck at the beginning of each turn.

You can take as many actions as you want as long as you have the mana required to do so.

###### Example Card:
```
Fireball
Mana cost 6

Effect: 
Target a 4x4 square on the ground and deal 10 damage to all enemies inside the square.
The targeted squares will ignite, lighting it on fire for 3 turns.
Any enemy that walks over an ignited square will take 2 damage.
```


#### Turn Order

Turns are done in an alternating fashion based on actions, starting with the player and followed by the enemies.

For Example, You are in combat with 2 enemies:
- You play the following actions: Walk Up, Shoot Fireball, Drink health potion
- Enemy A does the following: Walk Left, Fire Bow left
- Enemy B does the following: Swing Sword Up, Defend
- Turn order would be:
  1. Player: Walk Up
  2. Enemy A: Walk Left
  3. Enemy B: Swing Sword Up
  4. Player: Shoot Fireball
  5. Enemy A: Fire Bow Left
  6. Enemy B: Defend
  7. Player: Drink Health Potion








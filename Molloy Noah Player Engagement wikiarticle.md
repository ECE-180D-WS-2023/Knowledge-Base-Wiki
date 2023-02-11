#Player Engagement

**Player engagement** (sometimes called **player retention, player churn, player attrition, or player turnover**) is
a measure of how players positively or negatively experience a game. High amounts of player engagement translates to
longer play sessions and more player satisfaction. Conversely, low amounts of player engagement results in shorter playtime
and an overall negative gameplay experience.

The most popular games are marked by their ability to capture players' attention. Long and frequent play sessions are characteristic
of games with good player engagement. 

##Engagement Methods

There are several ways to provide players with an engaging experience. These center around the idea that players want to experience
some aspect of a game, usually chasing some sort of goal. These goals can be fairly abstract or more concrete with clearly communicated
objectives given to the player by the game. 

###Goals

Developing a game with a focus on player engagement starts in the deisgn of the gameplay loop. Developers should carefully consider
what experiences they have to offer to the player. There are a variety of things developers can give players to pursue during their 
time with the game. These pursuits can be categorized into two fields, intrinsic objectives and extrinsic objectives[2]. 
Intrinsic objectives are player-imposed objectives that offer no direct in-game benefit. Extrinsic objectives are goals set by the 
game for the player to attempt to achieve. For example, how a player might build a house in the popular game Minecraft is an 
intrinsic objective. Players can fashion their house to whatever style they may like or might not feel the need to build a house 
at all.  In the extrinsic case, something like collecting all the coins in a Super Mario level is a goal set by the developers for 
the player to do. In either case, the player is actively pursuing some kind of goal with the pay-off being some sort of satisfaction
from playing the game.


###Real-time Analytics
After core gameplay elements are developed and in-place, it may be difficult to optimize player engagement if a certain strategy 
did not yield the desired results. Player engagement may be restored by the use of real-time analytics to fine tune parameters in 
specific engagement scenarios. When attempting to integrate real-time analytics, it is essential to establish which metrics are 
important and what weight should be assigned to each category. While every game is different in how they are structured, there 
are a few core metrics that should be recorded and acted on. 

###Win/Success Rate

Contrary to what intuitively seems to make the most sense, players winning in a game too much may end up less engaged than other 
players. While it's obvious that players that are constantly losing will want to stop playing, players that continue to win may 
end up feeling unsatisfied with the game[1]. They might feel that they have already mastered the mechanics of the game and 
that there is no reason to invest their time to improve at the game.

In a scenario where players participate in a game set where the outcome can either be a win, draw, or loss, the most likely 
string of game outcomes to cause a player to stop playing is three straight losses in a row. Interestingly, the second most 
likely string of game outcomes to cause a player to stop is two consecutive wins and an ending loss. In general, if the last 
game in the set is a loss, there is a higher chance of a player becoming disinterested with the game. The strings of game 
outcomes to least likely cause a player to stop playing are combinations of wins, draws, and losses where the last game in a set 
is either a win or a draw. Infact, a player who experienced two consecutive losses and an ending win is actually more likely to 
continue to play versus the two wins one loss case.

###Fixed Random Chance

During gameplay, random events with set probabilities can have the likeliness of certain events occurring modified in such a 
way to drive up player satisfaction[3]. With real-time analytics, a game can recognize that a player has had a string of bad luck 
or experienced multiple consecutive losses outside or within their control. The game can then act upon that trend of negative 
experiences by forcing the probability of a positive event occurring to keep the player interested in the game. This can take 
form in things like random loot chests found in the game world that might contain rare equipment or a random chance of a 
critical hit during combat that results in the enemy taking a larger than normal amount of damage. This fixing of chance can be
either visible to the player or hidden, depending on what the developer is attempting to accomplish. Most of the time it should
not be noticible to the player that the game is fixing things in the background but there are times where showing the game is
adjusting odds can have a positive effect. For example, if a player has a chance to open a crate with a low chance of obtaining 
a rare item, the game might show that the chance of obtaining a rare item has increased over the last time. This will encourage
the player to continue to engagae with the game so that they can try to find an additional source of loot and have an improved
chance of obtaining the rare item.  

[1] https://web.cs.ucla.edu/~yzsun/papers/WWW17Chen_EOMM
[2] http://www.digra.org/wp-content/uploads/digital-library/11307.06025.pdf
[3] https://opensiuc.lib.siu.edu/cgi/viewcontent.cgi?article=1395&context=gs_rp
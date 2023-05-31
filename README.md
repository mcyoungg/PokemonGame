# PokemonGame

A “simulation” game that involves Pokemon 
battles consisting of objects located in a two-dimensional world that move around and behave in
various ways. The user enters commands to tell the objects what to do, and they behave in
simulated time. Simulated time advances one “tick” or unit at a time. Time is “frozen” while the
user enters commands. When the user commands the program to “go”, time will advance one
tick of time. When the user commands the program to “run”, time will advance several units of
time until some significant event happens. This inlcudes when a Pokemon Center runs out of potions,
when a trainer arrives at their destination, or when a pokemon faints. 

How to Play:
You are a Pokemon Trainer. You are trying to defeat the gyms but you need your Pokemon to
stay healthy. You must go to gyms and earn experience by battling. However, you also need to
periodically get potions if you want to make sure your Pokemon don’t faint. You “win” the game
by defeating all the gyms without having your Pokemon faint. You can compare games with
other students by seeing who completes all the gyms the fastest.

New features:
* The inclusion of a Wild Pokemon. Wild Pokemon are
on the game board and if a Trainer comes “into contact” with them, they lose
health points faster twice as fast. They will follow the player until it faints, on its own. 
* Arrays were replaced with STL linked lists. 
* Added Exceptions.

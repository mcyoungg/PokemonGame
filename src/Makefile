# in EC327, we use the g++ compiler
# therefore, we define the GCC variable 

GCC = g++ -std=c++11
# a target to compile the main which depends on all object-files # and which links all object-files into an executable

game: main.o Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o View.o WildPokemon.o
	$(GCC) main.o Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o  View.o  WildPokemon.o -o game
# a target to compile the main.cpp into an object-file
main.o: main.cpp
	$(GCC) -c main.cpp
# a target to compile the Point2D.cpp into an object-file
Point2D.o: Point2D.cpp
	$(GCC) -c Point2D.cpp
# a target to compile the Vector2D.cpp into an object-file
Vector2D.o: Vector2D.cpp
	$(GCC) -c Vector2D.cpp
# a target to compile the GameObject.cpp into an object-file	
GameObject.o: GameObject.cpp
	$(GCC) -c GameObject.cpp
# a target to compile the Building.cpp into an object-file
Building.o: Building.cpp
	$(GCC) -c Building.cpp
# a target to compile the PokemonCenter.cpp into an object-file
PokemonCenter.o: PokemonCenter.cpp
	$(GCC) -c PokemonCenter.cpp
# a target to compile the PokemonGym.cpp into an object-file
PokemonGym.o: PokemonGym.cpp
	$(GCC) -c PokemonGym.cpp
# a target to compile the Trainer.cpp into an object-file
Trainer.o: Trainer.cpp
	$(GCC) -c Trainer.cpp
# a target to compile the Model.cpp into an object-file
Model.o: Model.cpp
	$(GCC) -c Model.cpp
# a target to compile the GameCommand.cpp into an object-file
GameCommand.o: GameCommand.cpp
	$(GCC) -c GameCommand.cpp
# a target to compile the View.cpp into an object-file
View.o: View.cpp
	$(GCC) -c View.cpp
# a target to compile the WildPokemon.cpp into an object-file
WildPokemon.o:
	$(GCC) -c WildPokemon.cpp
# a target to delete all object-files and executables
clean:
	rm main.o Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o View.o WildPokemon.o game 
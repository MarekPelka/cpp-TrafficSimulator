# cpp-TrafficSimulator

!!! WORK IN PROGRESS !!!

TO DO
----------
1. Zaprojektować miasto
	- Dodawanie ulic
		- Chodniki
		- Skrzyżowania
			- O: Światła
		- Ulice zabronione dla ciężarówek
	- Budynków
	- Parkingów
	- Kamer
	- O: Realistyczny rozkład ruchu miejskiego wg pory dnia
2. Samochody
	- Cięzarówki i Osobowe
		- Inne przyśpieszenia
		- Vmax dla danej ulicy
		- Długość
	- Przyśpieszanie, zwalnianie
	- Skręty n skrzyżowaniach
	- Max speed dla ulicy
	- O: Hamowanie przed przeszkodami - światła, inne wariaty
	- Kolory dlaa przędkości
3. Skrzyżowania
	- 5 typów skrzyrzowań
		- ograniczenia prędkości w zależności od skrętów
		- O: światła
		- O: Pasy dla pieszych na skrzyrzowaniach

	- 4 typy skrętów - inne prędkości
4. Kamery
	- w dowolnym miejscu
	- kąt widzenia, dokładność, kierunek obserwacji
	- budynki zasłaniają widok
	- próbkowane co 1s
	- podaje współrzędne zaobserwowanego obiektu
5. Piesi
	- Chodzą po chodnikach
	- Stała predkość + zatrzymywanie
	- O: Zwracaja uwage na swiatła
	- Poruszaja sie od korpo do korpo
6. Budynki
	- Przesłaniają kamery
	- Współrzędne
7. Parkingi
	- Węzły w grafie
	- Punkty końcowe
	- Dwa typy: Domowe i Pracowe
	- Określone rozmiary
	- Zajętość
	- O: Rozkład losowości chęći przyjazdu (Wiecej osób do centrum)
	- !Odpowwiedzialy za stworzenie samochodu i pieszych!
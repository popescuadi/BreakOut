Tema proiect:Break It

Gandire algoritm:
-este desenata scena(tabla de joc) prin intermediul unei matrici in care codificam elementele (caramizile,peretii,bara)
-este desenata bara in pozitia de repaus
-se verifica daca este apasata orice tasta ; in cazul in care este apasata tasta 'a' sau 'd' se redeseneaza bara ,aparand astfel efectul de miscare
-bila este desenata in pozitia de repaus
-bia este o structura in care salvam coordonatele ei, sensul si directia pe care se deplaseaza
-starea bilei este de miscare , modificandu-se coordonatele ei dupa traiectorii predefinite de sens si directie
-exista 4 directii :vertical cu sensurile sus-jos si 3 directii diagonale cu 4 sensuri fiecare(dreapta-sus,dreapta-jos,stanga-sus,stanga-jos)
-bila isi modifica statusul (directia si sensul) la ciocnirile cu peretii,caramizile si bara
-la ciocnirile cu peretii, bila este deviata cu un unghi de reflexie egal cu unghiul de incidenta
-la ciocnirile cu bara se tine cont de deplasarea barii
-la ciocnirile cu caramizile , bila este deviata la fel ca in cazul peretilor si caramizile se sparg astfel(sunt folosite functii care detecteaza coliziunile si distrug caramizie in cazul unei astfel de coliziuni):
	*caramizile gri se comporta la fel ca peretii
	*caramizile orange se sparg si cresc scorul cu 1
	*caramizile maro devin orange si cresc scorul cu 1
	*caramizile verzi genereaza un bonus(structura in care avem coordonatele , efectul si statusul de existenta pe harta al acestui bonus)
-in cazul in care prinzi cu bara un bonus , acesta devine activ:
	*inima rosie ofera o viata in plus
	*triunghiul galben ofera 3 incarcaturi laser(incarcaturile laser sunt vazute ca bila , pentru care este deja definita distrugerea)
	*bara albastra mareste bara de jos
-exista 9 harti
-castigi daca ai completat toate cele 9 harti
-pierzi jocul daca pierzi toate vietile 
-pierzi o viata daca linia bilei si linia barii coincid
-jocul poate fi intrerupt prin apasarea tastei space, care functioneaza ca un switch(verifica  daca o variabila are valoarea 0 si o schimba in 1 , altfel daca este 1 o schimba in 0)
-la pierderea sau castigarea jocului , numele si scorul jucatorului sunt salvate intr-un fisier
-la fiecare 3 nivele se schimba melodia de fundal (functia Playsound() din <windows.h>)
-este folosit un meniu principal unde avem posibilitatea sa alegem sa ne jucam,sa vedem instructiunile sau scorurile altor jucatori
 
Optimizare si implementare:
-s-a renuntat la utilizarea functiei "System("cls")" si redesenarea intregului spatu de joc in favoarea utilizarii functiei "SetConsoleCursorPosition()" din biblioteca <windows.h>,
functie care ne deplaseaza cursorul in cadrul consolei(consola este vazuta ca o matrice) la coordonatele precizate, obtinandu-se astfel un efect de continuitate
-matricea este folosita doar pentru a detecta coliziunile si a distruge caramizile
-codificare caramizi:1(caramida gri)
		     2(caramida orange)
		     3(caramida maro)
		     4,5,6(caramizi bonus)
-jocul se desfasoara in cadrul unui gameloop care are ca si conditii existenta a cel putin unei vieti si faptul ca nu am castigat
-functia SetConsoleTextAttribute din <windows.h> actioneaza asupra caracterelor astfel : ne modifica culoarea caracterului si culoarea backgroundului caracterului(avem 15 culori la dispozitie si 255 de combinatii culoare text-culoare background text)
-la fiecare miscare a bilei verificam daca aceasta se ciocneste cu un obstacol
-in cele 9 nivele este precizata doar codificarea caramizilor

IMPORTANT!!!!
Pentru ca jocul sa ruleze este nevoie ca fisierele .in  si .wav sa se afle in caleasi director cu executabilul
Jocul folseste doar tastele (W,A,S,D si space)
In meniu-W,S navigare,space selectare submeniu si intoarcere la meniul principal din submeniu
In joc-A,D deplasare bara , space pauza/rezumare joc
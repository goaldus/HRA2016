Projekt do p�edm�tu ICP: HRA2016
------------------------------------------
Auto�i: Vil�m Jelen (xjelen09), Ond�ej Moln�r (xmolna05)
------------------------------------------
Popis:	
	Implementace hry Reversi (Othello) pro p��kazovou ��dku i s grafick�m rozhran�m. 
	Slo�ka examples obsahuje uk�zkov� ulo�en� hry. Zdrojov� soubory jsou v src.	
------------------------------------------
P�eklad:	
	p��kazem make, v�stupem jsou spustiteln� soubory hra2016-cli a hra2016
	make doxygen vygeneruje dokumentaci
------------------------------------------
Spu�t�n�:
 	hra2016-cli nem� ��dn� parametry zad�van� p�i spu�t�n� (pouze ./hra2016-cli)
------------------------------------------
Ovl�d�n� CLI verze:
	new [easy|hard] [6|8|10|12] 		- vytvori novou hru		
		- volitelne mo�nosti jsou v�b�r AI obt�nosti a velikosti hern� desky		
		- bez parametr� se pou�ije velikost 8 a protihr��em je �lov�k
	[put|p] x y                 		- polozi disk na souradnice x, y
		- nejm�n� n�ro�n� pokl�d�n� lze ps�t nap��klad takto: 4 5 (polo�� na sou�adnice 4 a 5)
		- osa x je vertik�ln�, y horizont�ln� 
	open                        		- otevre hru v novem okne
		- kvuli komplikacim zat�m neimplementovano
	save [nazev_hry]            		- ulozi hru s volitelnym nazvem
		- pokud nen� zad�n n�zev hry, vygeneruje se automatick� jm�no 
	load nazev_hry              		- nacte hru "nazev_hry"
	
		- zad�vejte pouze n�zev hry, cesta k souboru je pova�ov�na za neplatn� n�zev
	n | next                   		- posune se dop�edu v historii pr�v� hran� hry		
	b | back                   		- posune se zp�t v historii pr�v� hran� hry	
	help                       		- zobraz� tuto n�pov�du b�hem hry

	exit                        		- ukon�� program
-------------------------------------------
Pozn�mky:
	Ulo�en� hry neobsahuj� tahy um�l� inteligence.
	Um�l� inteligence nikdy neza��n� hru prvn�.
	


		
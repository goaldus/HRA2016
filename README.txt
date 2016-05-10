Projekt do předmětu ICP: HRA2016
------------------------------------------
Autoři: Vilém Jelen (xjelen09), Ondřej Molnár (xmolna05)
------------------------------------------
Popis:	
	Implementace hry Reversi (Othello) pro příkazovou řádku. 
	Grafické rozhraní bohužel nefunguje, je pouze rozpracováno. 
	Složka examples obsahuje ukázkové uložené hry. Zdrojové soubory jsou v src.	
------------------------------------------
Překlad:	
	příkazem make, výstupem jsou spustitelné soubory hra2016-cli a hra2016
	make doxygen vygeneruje dokumentaci
	make pack zabalí všechny důležité soubory do archivu pro snadnou distribuci hry
------------------------------------------
Spuštění:
 	hra2016-cli nemá žádné parametry zadávané při spuštění (pouze ./hra2016-cli)
 	hra2016 taktéž (./hra2016)
------------------------------------------
Ovládání CLI verze:
	new [easy|hard] [6|8|10|12] 		- vytvori novou hru		
		- volitelne možnosti jsou výběr AI obtížnosti a velikosti herní desky		
		- bez parametrů se použije velikost 8 a protihráčem je člověk
	[put|p] x y                 		- polozi disk na souradnice x, y
		- nejméně náročné pokládání lze psát například takto: 4 5 (položí na souřadnice 4 a 5)
		- osa x je vertikální, y horizontální 
	open                        		- otevre hru v novem okne
		- kvuli komplikacim zatím neimplementovano
	save [nazev_hry]            		- ulozi hru s volitelnym nazvem
		- pokud není zadán název hry, vygeneruje se automatické jméno 
	load nazev_hry              		- nacte hru "nazev_hry"
	
		- zadávejte pouze název hry, cesta k souboru je považována za neplatný název
	n | next                   		- posune se dopředu v historii právě hrané hry		
	b | back                   		- posune se zpět v historii právě hrané hry	
	help                       		- zobrazí tuto nápovědu během hry

	exit                        		- ukončí program
-------------------------------------------
Poznámky:
	Uložené hry neobsahují tahy umělé inteligence.
	Umělá inteligence nikdy nezačíná hru první.
	


		

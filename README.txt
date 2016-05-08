Projekt do pøedmìtu ICP: HRA2016
------------------------------------------
Autoøi: Vilém Jelen (xjelen09), Ondøej Molnár (xmolna05)
------------------------------------------
Popis:	
	Implementace hry Reversi (Othello) pro pøíkazovou øádku i s grafickým rozhraním. 
	Složka examples obsahuje ukázkové uložené hry. Zdrojové soubory jsou v src.	
------------------------------------------
Pøeklad:	
	pøíkazem make, výstupem jsou spustitelné soubory hra2016-cli a hra2016
	make doxygen vygeneruje dokumentaci
------------------------------------------
Spuštìní:
 	hra2016-cli nemá žádné parametry zadávané pøi spuštìní (pouze ./hra2016-cli)
------------------------------------------
Ovládání CLI verze:
	new [easy|hard] [6|8|10|12] 		- vytvori novou hru		
		- volitelne možnosti jsou výbìr AI obtížnosti a velikosti herní desky		
		- bez parametrù se použije velikost 8 a protihráèem je èlovìk
	[put|p] x y                 		- polozi disk na souradnice x, y
		- nejménì nároèné pokládání lze psát napøíklad takto: 4 5 (položí na souøadnice 4 a 5)
		- osa x je vertikální, y horizontální 
	open                        		- otevre hru v novem okne
		- kvuli komplikacim zatím neimplementovano
	save [nazev_hry]            		- ulozi hru s volitelnym nazvem
		- pokud není zadán název hry, vygeneruje se automatické jméno 
	load nazev_hry              		- nacte hru "nazev_hry"
	
		- zadávejte pouze název hry, cesta k souboru je považována za neplatný název
	n | next                   		- posune se dopøedu v historii právì hrané hry		
	b | back                   		- posune se zpìt v historii právì hrané hry	
	help                       		- zobrazí tuto nápovìdu bìhem hry

	exit                        		- ukonèí program
-------------------------------------------
Poznámky:
	Uložené hry neobsahují tahy umìlé inteligence.
	Umìlá inteligence nikdy nezaèíná hru první.
	


		
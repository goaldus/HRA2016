# Zadání
<HTML>
<BODY>
<P>  Toto je draft (2016-02-25)
<a href="http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html">Zdroj</a>
<HR>
Navrhněte a implementujte aplikaci Othello (Reversi), která vychází ze stejnojmenné deskové hry.
Pravidla hry jsou <A HREF="https://cs.wikipedia.org/wiki/Othello_%28deskov%C3%A1_hra%29#Pravidla_hry"> zde</A>.

Aplikace implementuje pravidla hry a vyhovuje dalším požadavkům:
<UL>
<LI>  lze zvolit velikost hrací desky (6, 8, 10, 12); implicitní hodnota je 8
<LI>  lze vytvořit a hrát více her současně
<LI>  lze uložit a načíst hru v libovolném stavu
<LI>  součástí každé hry je historie, která se ukládá a načítá současně s hrou a
umožní vracet se zpět, pohybovat se vpřed podle uložené historie nebo
nezávisle na ní (v tomto případě se uložené pokračování hry zruší a tvoří se
nové)
<LI>  lze zvolit soupeře - člověk nebo počítač, v případě počítače implementujte
dva různé (stačí triviální) algoritmy; před hrou se zvolí konkrétní
algoritmus, návrh aplikace musí umožňovat jednoduše přidávat další algoritmy.
</UL>

Jádro aplikace musí být navženo zcela nezávisle na uživatelském rozhraní.
Součástí aplikace bude textové (CLI) i grafické uživatelské rozhraní (GUI)
jasně a přehledně zobrazující
<UL>
<LI>  hrací desku,
<LI>  kdo je právě na tahu,
<LI>  hrací kameny, které má hráč k dispozici,
<LI>  hrací kameny, které jsou vloženy na desku,
<LI>  pruběžné skóre,
<LI>  indikaci proveditelnosti/neproveditelnosti tahu a indikaci konce hry
</UL>
a umožňující
<UL>
<LI>  provést tah,
<LI>  vracet se po jednom tahu zpět nebo vpřed v historii a přitom správně zobrazovat výše uvedené informace,
<LI>  z libovolného historického stavu lze pokračovat buď podle uložené sekvence tahů nebo nezávisle na ní, jak bylo uvedeno výše.
</UL>

Součástí odevzdání bude alespoň jedna uložená rozehraná hra ve stavu bude
těsně před ukončením.

<H3>Další požadavky</H3>

<UL>
<LI> Zadání definuje podstatné vlastnosti aplikace, které musí být splněny.
Předpokládá se, že detaily řešení si doplní řešitelské týmy.

<LI> Při návrhu postupujte tak, aby výsledný program byl dobře použitelný.
Hodnotit se bude nejen to, zda splňuje výše uvedené požadavky, ale také JAK je
splňuje.

<LI> Návrh musí oddělit vlastní model aplikace od GUI (navrhněte vhodné
rozhraní). Demonstrujte to vytvořením testovací aplikace "hra2016-cli" s použitím
stejných (přeložených) modulů bez použití toolkitu a pouze s textovým rozhraním
(použijete pouze ISO C++ streamy cin/cout na terminál ve stylu příkazové řádky).

<LI> Návrh programu zdokumentujte ve zdrojovém kódu ve formátu pro program "doxygen".

<LI> Používejte vhodné návrhové vzory (Design Patterns) - viz literatura.

<LI> Pro vytváření menu, dialogů a dalších komponent grafického uživatelského
     rozhraní (GUI) použijte toolkit <B>QT 5.5</B>
     (nainstalováno v učebnách a na serveru "merlin" v adresáři /usr/local/share/Qt-5.5.1/).
     Pokud pro vývoj použijete verzi novější/starší než je na učebnách,
     předpokládám, že zajistíte zpětnou/dopřednou kompatibilitu vašich
     programů. (V případě problémů, počítejte s nutností předvedení
     překladu/sestavení/běhu aplikace na vašem notebooku. Toto se nedoporučuje.)

     <BR> Protože toolkity jsou přenositelné na více platforem, měly by vaše
     programy fungovat minimálně na Linuxu i na Windows.  (Nejen Java umožňuje
     psaní přenositelných aplikací.)
     Je jedno na které platformě proběhne vývoj aplikací, jen dbejte na
     pravidla psaní přenositelných programů. <BR>
     (Testovat se bude na Linuxu = server merlin, ale Makefile nesmí být
      závislý na konkrétním adresáři s lokální instalací toolkitu.)

     <BR> Na vytvoření GUI dialogů a menu můžete použít interaktivní editory/generátory.

     <!--
     <BR> Serverová část projektu nesmí použít Qt. Zkuste například BOOST/asio.
     -->

<LI> Použijte C++11.
     Doporučuji používat knihovny z BOOST
     (Použité soubory přibalte. Existuje nástroj <A
     HREF="http://www.boost.org/doc/libs/1_60_0/tools/bcp/doc/html/index.html">BCP</A>
     pro výběr podmnožiny Boost.).

<LI> Programy budou vytvořeny zadáním příkazu "make" v adresáři s rozbalenými
zdrojovými kódy projektu (Pozor - bude se automaticky překládat).  Musíte
vytvořit soubor Makefile, který nesmí obsahovat absolutní cesty k souborům.
Výsledné programy se budou jmenovat
"hra2016" 
a
"hra2016-cli" 
.

Pro testovací účely půjde vše spustit použitím "make run".

<LI>Součástí projektu bude programová dokumentace vytvořená programem Doxygen
(konfigurační soubor nastavte na HTML výstup se zahrnutím zdrojových textů:
SOURCE_BROWSER = YES).
Dokumentace se vygeneruje automaticky (= nezabalovat do archivu) při zadání
"make doxygen" a bude uložena v podadresáři doc.

</UL>

<H2>Poznámky k odevzdávání</H2>
<UL>

<LI> Termín odevzdání je uveden v IS.

<LI> Řešení zabalené ve formátu .zip (nebo .tar.gz) odevzdá pouze vedoucí týmu do
     IS a to s dostatečným předstihem před uzávěrkou.
     (Nikdo nebude psát, že neodevzdal, protože *** a posílat to poštou.)
     <BR>
<B>Jméno odevzdaného souboru musí mít tvar: xname01-xname02.zip, kde xname01 je jméno vedoucího. </B>

<LI> <B>POZOR:</B> Archiv může mít maximálně 2MB, aby mohl být vložen do IS.

<LI> Odevzdaný archiv obsahuje minimálně tuto adresářovou strukturu:
<pre>
./src/*       - zdrojové texty
./examples/*  - příklady (pro testování)
./doc/        - dokumentace (bude později generován: "make doxygen")
./README.txt  - základní přehled o co jde, Autoři, poznámky, ...
./Makefile    - zavolá rekurzivně make na src/Makefile, případně
                na generování dokumentace atd
</pre>

<LI> Neodevzdávejte nic, co lze vytvořit pomocí "make"
     (spustitelné programy ani dokumentaci, kterou lze vygenerovat použitím "make doxygen").

     <BR> Poznámka: Příkaz "make clean" všechny produkty překladu smaže,
     "make pack" vytvoří archiv pro odevzdání -
     zkontrolujte, zda obsahuje vše potřebné rozbalením v prázdném adresáři a
     překladem/spuštěním.

<LI> Všechny zdrojové soubory musí obsahovat na začátku komentář se jmény
     autorů daného modulu, popisem obsahu modulu, atd.
     Z komentářů by také mělo být patrné, které části byly napsány ručně a
     které vygenerovány automaticky.

</UL>



<H2>Poznámky k hodnocení </H2>
<ul>
<LI> Projekt je hodnocen na stupnici 0-100 procent/bodů. 

<LI> Po ohodnocení <B>může</B> dojít k přepočtu bodů na jednotlivé
členy týmu podle návrhu vedoucího týmu, který je zakódován do jména
odevzdaného souboru (formát jména pak je: xname01-xname02-AA-BB.zip
součet AA+BB=100, <B>POZOR: pro rovnoměrné rozdělení AA=BB=50% není třeba
 uvádět "-50-50" a je to preferovaná možnost</B>).

<LI>Hodnocení zahrnuje kvalitu OO návrhu, kvalitu implementace v C++, dodržování
stylu psaní programu (odsazování, kvalita komentářů, vhodné identifikátory)
a především funkčnost programu. Pokud budou ve zdrojových textech chybět
podstatné komentáře (zvláště jména autorů), bude projekt hodnocen 0b.

<LI> <B>POZOR:</B> 
<BR> Pokud nepůjde přeložit příkazem make = 0b
nebo předvedete na svém notebooku <b>a vysvětlíte kde byl problém</b>,
<BR> pokud nebudou komentáře se jmény autorů = 0b.
<BR> Zcela nevhodně formátovaný a nečitelný kód = 0b.
<BR> Plagiáty atd. = 0b + návštěva u disciplinární komise.

</ul>

<HR>
<ADDRESS>
    Poslední modifikace: <!-- begin flastmod -->
24. February 2016<!-- end --> 
<BR>
Pokud naleznete na této stránce chybu, oznamte to dopisem na adresu
peringer AT fit.vutbr.cz
</ADDRESS>
</BODY>
</HTML>


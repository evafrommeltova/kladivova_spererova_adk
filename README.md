# kladivova_spererova_adk
Repozitář k předmětu Algoritmy digitální kartografie a GIS

Úloha 1: Geometrické vyhledávání bodu:
Výsledná aplikace má několik funkcionalit. 
Umí pomocí tlačítka Draw point/polygon nakreslit polygon a bod a jejich vzájemnou polohu analyzovat. 
Stejně tak dokáže stiknutím tlačítka Import polygons importovat soubor se souřadnicemi polygonů a 
tyto polygony pak vůči zadanému bodu analyzovat. Další variantou získání polygonu je automatické vygenerování polygonu, 
který může být dále také analyzován vůči vybranému bodu. 

Úloha 2: Konvexní obálky:
V rámci úlohy byla vytvořena aplikace, která je schopna na vygenerovaných bodech zkontruovat konvexní obálku, a to hned několika metodami. Zároveň je možné v rámci aplikace generovat 6 různých typů množin. Součástí úlohy je i testování doby výpočtu algoritmů pro různé typy vstupních množin. 

Úloha 3: Digitální model terénu a jeho analýzy:
Aplikace umí generovat vybrané terénní tvary (kupa, údolá, hřbet, spočinek, sedlo), importovat soubor se souřadnicemi i kreslit body kursorem myši. Nad všemi těmito množinami dokáže zkonstruovat Delaunayho triangulaci, jejíž trojúhelníky jsou ztěžejní při následném generování vrstevnic a provádění analýz sklonu a expozice. Pro sklon i expozici jsou naprogramovány barevné palety. Hlavní vrstevnice jsou zesílené a automaticky popsané. Kartografické zásady popisu nejsou uplatněny.

Úloha 4: Množinové operace s polygony:
Výsledná aplikace má několik funkcionalit. Umí importovat textový soubor se souřadnicemi dvou polygonů, nebo tyto polygony ručně naklikat v obrazovém okně. Následně je možné zobrazit výsledek vybrané množinové operace. V comboboxu si můžeme vybrat z následujících množinových operací: průnik, sjednocení, rozdíl A-B a rozdíl B-A. Výsledné hrany patřící do výsledku jsou zvýrazněny červenou barvou. V aplikaci bylo zapotřebí ošetřit případy, kdy výsledkem je linie nebo bod. Tyto případy byly testovány skrze speciální textové soubory, na kterých si může uživatel sám vyzkoušet funkčnost aplikace. Pokud je výsledkem linie - je vyznačena, bohužel pokud je výsledkem pouze bod (případy A, B, C na obrázku \ref{fig:problem}) průnik v bodě není zřetelně vyznačen. Tato skutečnost může být pro uživatele matoucí. Žádné bonusové úlohy v rámci této úlohy řešeny nebyly. 


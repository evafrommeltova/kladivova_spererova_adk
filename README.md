# kladivova_spererova_adk
Repozitář k předmětu Algoritmy digitální kartografie a GIS

Úloha 1: Geometrické vyhledávání bodu:
Výsledná aplikace má několik funkcionalit. 
Umí pomocí tlačítka Draw point/polygon nakreslit polygon a bod a jejich vzájemnou polohu analyzovat. 
Stejně tak dokáže stiknutím tlačítka Import polygons importovat soubor se souřadnicemi polygonů a 
tyto polygony pak vůči zadanému bodu analyzovat. Další variantou získání polygonu je automatické vygenerování polygonu, 
který může být dále také analyzován vůči vybranému bodu. 

Úloha 1: Konvexní obálky:
V rámci úlohy byla vytvořena aplikace, která je schopna na vygenerovaných bodech zkontruovat konvexní obálku, a to hned několika metodami. Zároveň je možné v rámci aplikace generovat 6 různých typů množin. Součástí úlohy je i testování doby výpočtu algoritmů pro různé typy vstupních množin. 

Úloha 3: Digitální model terénu a jeho analýzy:
Aplikace umí generovat vybrané terénní tvary (kupa, údolá, hřbet, spočinek, sedlo), importovat soubor se souřadnicemi i kreslit body kursorem myši. Nad všemi těmito množinami dokáže zkonstruovat Delaunayho triangulaci, jejíž trojúhelníky jsou ztěžejní při následném generování vrstevnic a provádění analýz sklonu a expozice. Pro sklon i expozici jsou naprogramovány barevné palety. Hlavní vrstevnice jsou zesílené a automaticky popsané. Kartografické zásady popisu nejsou uplatněny.

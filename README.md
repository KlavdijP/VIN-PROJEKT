# VIN-PROJEKT
VODNA ZALIVALKA

# Ideja
Za projektno nalogo pri predmetu VIN sem se odločil izdelati vodno zalivako za rože.
Sistem bi glede na vlažnost zemlje zalival rožo dokler ne doseže željene vrednosti, ki jo nastavimo sami (ali je v opisu izdelka).
Za lažji pregled se vse prikazuje še na spletni strani.

# Shema
![image](https://user-images.githubusercontent.com/61451323/177049809-55b238b4-aa4b-4657-b089-a11f9fa192bd.png)

# Komponente!

<ul>
<li>
ESP32
</li>
 
<li>
Vodna črpalka
</li>

 <li>
Ultrazvočni senzor
</li>

 <li>
Senzor za merjenje vlažnosti zemlje
</li>
 
  <li>
Ostalo:
izolacijsko mehkejšo žico, izolacijski lepilni trak, cin, spajkalnik, ploščo za spajkanje, 100 Ω upor, diodo, NPN tranzistor
</li>
</ul>

# Opis posameznih komponent
## ESP32
ESP32 predstavlja glaven del izdelka. Vse komponente, ki jih bom naštel so povezane na ta mikrokrmilnik in se povezujejo med seboj. Največja izhodna napetost, kadar je mikrokrmilnik priklopljen prek USB kabla, je 5 V, zato zadošča za napajanje vseh komponent. Zanj sem se odločil zato, ker omogoča povezavo z računalnikom preko Wi-Fi modula. V program moramo le vpisati ime in geslo omrežja.

## Vodna črpalka
Vodna črpalka deluje z napetostjo 5 V, zato je bila uporaba zelo enostavna. Pozoren sem moral biti, da sem črpalko zvezal pravilno, saj bi lahko po pomoti obremenil mikrokrmilnik in ga s tem uničil. Zato sem moral uporabiti 100 Ω upor, NPN tranzistor in diodo.

## Ultrazvočni senzor
S pomočjo ultrazvočnega senzorja sem lahko izračunal volumen vode, ki je ostal v rezervoarju. Senzor je sestavljen iz dveh delov. En del pošilja zvočne impulze (“echo” priklop), drugi pa jih sprejema (“trig” vklop). Na podlagi formule, ki je v kodi, se izračuna razdalja med senzorjem in gladino vode v rezervoarju. S tem sem lahko omejil delovanje vodne črpalke, da se v primeru, ko je vode premalo, ne vklaplja.

## Senzor za merjenje vlažnosti zemlje
Kapacitivni senzor za merjenje vlage v tleh deluje na principu merjenja upornosti med anodo in katodo. Izkaže se, da bolj kot je mokra zemlja, manjša je upornost. Za delovanje potrebuje napajanje 5 V in analogni vhod na mikrokrmilniku.

# Videoposnetek delovanja
https://youtube.com/shorts/emgbvPJWQ4I?feature=share
## Opis delovanja
 -Če je razdalja v rezervoarju vode večja od 14, pumpa ne bo več delovala, ker to pomeni, da vode ni. </br>
 -Če je vlažnost zemlje manjša od 1500, se bo pumpica vžgala za 1 sekundo in to ponavljala na intervalu 5 sekund.

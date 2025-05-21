# A választott feladat
 - A választásom egy harmadik személy nézetes platformer játékra esett, amely többnyire egy előre felépített világban játszódik asseteket használva.
 - Maga a projekt inkább egy interaktív(abb) élményként készült.
 - A játékban a harmadik személyi kamera mozgatása az egérrel történik (a bal egérgomb letartása közbeni csúsztatással).
 - A mozgás a W,A,S,D billentyűk lenyomásával, valamint a SPACE (szóköz) gombbal történik.
    - A mozgás maga homázs a régi játékokra a "Tank control" néven is ismert formában.
    - A SPACE (szóköz) hosszan lenyomva tartásával egy hosszú ugrás érhető el (long jump); a másodszori megnyomásával, miközben a játékos a levegőben van pedig egy második ugrás (double jump) érhető el.
 - Az ütközésvizsgálat egyszerű AABB (Axis-Aligned Bounding Box)-al működik.
 - A játékban állítható a fényerő a numpadon lévő "+, -" gombok megnyomásával.
    - "+" : Felveszi a fényerőt,
    - "-" : Leveszi a fényerőt.
 - Bekapcsolható / Kikapcsolható a köd a "CTRL és K" gombok lenyomásával.
 - A játék többnyire a [The Models Resource](https://www.models-resource.com) weboldalra feltöltött modelleket és textúrákat használja fel.
    - _MEGJEGYZÉS:_ Az mtl fájlok helyett bake-elt textúrázást (vagy textúra atlaszt) használok annak érdekében, hogy ne kelljen újraírni az obj betöltő könyvtárat.

# Miért pont egy platformer?
   - A platformer zsanra az egyik kedvenc játékfajtáim közé tartozik, ez egy nagy indok volt, viszont egy másik befolyásoló tényező az más játékok voltak, névileg az újonnan felszínre tört "Movement shooter"-ek, valamint "Zoomer Shooter"-ek.
   - Noha az én játékomnak semmi köze ezekhez a fajta játékokhoz, nem is a "Shooter" aspektusa volt az, ami inspirált engem, hanem a szabadság, amit ezek a játékok nyújtanak a játékos számára a mozgás terén, továbbá a reszponszivitás, az, hogy bármit csinál a játkos, a játék tud rá reagálni.
   - Tehát a beadandóm célja az, hogy jobban megismerjem ezeknek a mozgás-technikáknak a hátterét és, hogy megkíséreljek egy olyan játékot (vagy tech-demo-t) készíteni, amit csak jó irányítani.

# Mi kell ahhoz, hogy használjam?
 - A játékhoz szükséges asseteket megtalálod a [DropBoxomon](https://www.dropbox.com/scl/fo/obyodmsezp6fg3ffemp86/ANnxk1vAxdVVESFW4cn_0T0?rlkey=2purfvqxr9n0daeijp36d9ro0&st=q6mpo48z&dl=0)
 - Valamint a könyvtárak, amiket használtam:
   - OpenGL
   - SDL2
   - SDL2_image
   - obj, amit [Piller Imre repoján](https://gitlab.com/imre-piller/me-courses/-/tree/master/grafika/utils/obj?ref_type=heads) megtalálhattok

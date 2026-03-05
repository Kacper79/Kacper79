# Projekty personalne

## Potencjalne przyszłe pomysły:
- Własny kompilator oparty na LLVM dla własnego języka programowania w C++, wykorzystujący wydajność LLVM oraz pewne nowsze konstrukcje języków programowania z tych obecnie wychodzących.
- Emulator + VM dla jakiegoś chipa IC do networkingu np. Microchip VSC7514
- Kontyunuacja zajęć z administracji Linuksem + Cisco na GNS3 + dołączenie razem całego stacku: <br> VM Linuka w roli routera, wirtualne switche Cisco z GNS3, wirtualny firewall FortiGate, Integracja Wazuh SIEM, Backup Restic, IDS (Sutricata), Email, AD (Samba)
- Aplikacja IDE (C++/Java) z porządnym GUI do generowania kodu z diagramów UML i vice versa i integracją LLM dla polepszenia jakości kodu czyli taki mały Enterprise Architect tylko darmowy
- Algotytm heurystyczny w C++ do klasyfikacji zagrożeń w małym systemie IDS
- Mały firewall na linuksie oparty na eBPF (ale już istnieją takie) w C/C++
- Może kiedyś stworzenie małej własnej bazy danych

# Obecnie zaczęte pomysły (najczęściej do MVP)
Lista ta pomija własne pomysły jakie realizowałem w [pracach dyplomowych](./README.md#-prace-dyplomowe)

## Projekt własnej płytki PCB do własnego switcha (H2 2025 do obecnie)
Po zajęciach związanych z administracją sieci zainteresowałem się stworzeniem własnego ethernet swicha. Postanowiłem że zaprojektuje płytkę PCB dla kilkunasto portowego switcha. Głównym sercem switcha jest układ Microchip VSC7514 (który w przyszłości można zamienic na lepsze modele VSC), który zawiera PHY (dla 4 portów maks) + obsługę MAC dla wszystkich portów oraz switching fabric, który zajmuje się na poziomie hardware dokonywaniem decyzji switchingowych (jak przekazać ramkę) z minimalnymi opóźnieniami bez blokowania portów. Głowny ukłąd ma także zintegrowany procesor MIPS, który powinno dać się oprogramować po swojemu (choć wspierany jest także niezależny MCU jako master dla VSC7514) oraz wymaga pamięci DDR3L (ja biorę kości od Micron). Do tego oczywiście potrzebną są inne układy IC - PHY dla pozostałych portów RJ45, magnetyka dla RJ45 (chyba że się zdecyduje na porty magjack), układy PMIC do zasilania, porty USB,power jack, header pins oraz opcjonalnie myślałem o zastosowaniu FPGA od Lattice z ohsługą SERDES (Ethernetu) do przyśpieszania pewnych operacji sprzętowych na switchu - np. elementów hardware firewall. Obecnie mam wybrane i zkosztorysowane najważniejsze komponenty IC, prawie dokończyłęm rysunek schematic połączeń pomiędzy układami. Będę przystępował do walidacji schematic oraz już faktycznego rozstawiania ścieżek i komponentów na płytce. Ceny za produkcje 4 warstwowej płytki PCB trochę przerażają poza JCPPCB, z drugiej strony sprowadzanie komponentów, których nie ma fabryka wymaga zapłacenia cła w chinach, więc faktyczna produkcja switcha moze być pewnym wyzwaniem logistycznym. Mam nadzieje, że w perspektywie tego lub następnego roku będę już mieć projekt gotowy w bardziej skończonym stanie, który będę mógł zweryfikować z inżynierem.

## Gra multiplayer w Unity - DT (H1 2024 do obecnie)
Celem jest **stworzenie prototypu gry wielosobowej z gatunku horror survival** (konkurencja do tytułów: Dead By Daylight, Evil Dead The Game), rozwiązując pewne problemy gameplay'owe względem konkurencji. Prototyp został napisany w Unity i oskryptowany w C# z wykorzystaniem biblioteki FishNet do networkingu i funkcji RPC. 

Celem było zrobić własną grę wieloosobową (realny przypadek gry do testów), za pomocą istniejącej biblioteki a potem optymalizować (w miare możliwości)  wydajność gry w Unity, przepustowość serwera i zbierać informacje jak wykorzystywany jest hardware przy obciążeniu plus testować kod na networking. 
<br>

Ponieważ uczelnia zajmowała większość mojego czasu na zaliczenia i projekty poświeciłem na to może realnie z 5 miesięcy (czas na wakacjach) max, więc wiele nie osiągnałem podczas tego czasu. Na stan obecny (Marzec 2025) posiadam wszystkie najważniejsze mechaniki potrzebne dla prototypu, potrzebuje naprawić bugi, a potem mogę się zajać doskonaleniem gry i optymalizacją.

Tworzenie tej gry było całkiem edukacyjne, nawet jak korzystałem z gotowych bibliotek bo uświadomiło mi jak bardzo potrafi (czasami) leżeć DX i jak uciążliwe potrafią być silniki gier, co kiedyś gdy bardziej interesowałem się grami stanowiło motywacje do napisania własnego małego silnika 3D w OpenGL. Własne silniki dają  możliwość pełnej kontroli nad kodem oraz przyszłych możliwości optymalizacji. <br>
Nie ukrywam, że jakbym kiedyś wrócił do pisania silników gier / dem graficznych to bym wykorzystał moją wiedzę tzw. "pain points" jakie doświadczyłem z komercyjnymi silnikami czy bibliotekami do networkingu (tutaj też miałem mieszane uczucia), żeby usprawnić te obszary.

## Serwer matchmaking do DT w C++ (H1 2026)
Projekt ten został zaczęty jako poboczny dla głównego projektu gry. Głowna gra została zaprojektowana na zasadzie łączności P2P, która wymaga nawiązania pierwszej łączności pomiędzy serwerem (najczęściej jednym z graczy) a pozostałymi graczami poprzez jakiegoś pośrednika (np. własny serwer matchmaking i/lub biblioteki Steamworks) oraz utrzymywania ruchu sieciowego w obie strony (to akurat już robi serwer w Unity), tak aby gracze bez konieczności ustawiania port forwardingu, DDNS mogli razem uczestniczyć w wspólnym meczu. 

Aby zacząć mecz P2P serwer matchmakingowy będzie wykonywał tymczasowe otwieranie portów poprzez techniki NAT hole punching oraz (potem) UPNP. Ewentualnie można poszerzyć serwer o funkcjonalność Relay ruchu sieciowego w przypadku, gdy obie strony posiadają symetryczny NAT i/lub konfiguracja ISP/Routera nie pozwala na prawidłowe zastosowanie powyższych technik.

Poza samym nawiązywaniem pierwszej łaczności dla P2P, serwer powinien mieć także rolę matchmaking'ową, gdzie gracze zgłaszają w lobby zapytanie o dołączenie do meczu a serwer na podstawie kolejki oczekujących graczy, ich doświadczeniu w grze w zdecentralizowany sposób próbuje znaleźć optymalne mecze dla graczy. W tym projekcie zauważam okazję aby przećwiczyć wiedzę z systemów rozproszonych oraz integracji z bazą danych (tranzakcjami i zdarzeniami), shardingu baz danych, implementacji redundecji oraz load balancing w praktycznym przypadku. Serwer dodatkowo zbiera informacje pod koniec meczu o jego statusie od serwera (ale takżę potencjalnie innych użytkowników w trybie rozproszonej odpowiedzialności) i aktualizuje stan konta gracza do bazy danych (na razie bez Steamworks). Można też tutaj spokojnie przećwiczyć konteneryzacje oraz hostowanie tego w chmurze.

Potencjalnie także widzę możliwość aby opracować system Anti Cheat działający na podobnej zasadzie jak systemy SIEM, które w trakcie meczu zbierały by od użytkowników co jakiś czas logi wydarzeń serwerowych (interakcji sieciowych w grze wykonywanych przez RPC) oraz cały czas sprawdzały pozycje graczy (kontrując speed hacking, teleportacja, latanie lub nawet aim-bot) i konstrowały z tego pewien model jak ten mecz się odbył i próbował oszacować (np. poprzez integracje sieci neuronowych) czy ktoś oszukiwał czy nie, ale też potencjalnie analizował poziom umiejętności graczy (jakie zagrania zostały wykorzystane) lub zbierał analitykę do analizy zachowań graczy oraz mierzenia czasu grania (Churn analysis). 

## Mały silnik graficzny OpenGL w C++ (2022)
Jeden z moich pierwszych projektów, które sprawiło, że zainteresowałem się nisko-poziomowym programowaniem. Gry komputerowe potrzebując zapewniać pewną minimlaną i raczej stabilną wydajność (wymagania 30-120 FPS) stanowią idealne środowisko do eksperymentowania nad optymalizacją wydajności oraz komunikacji z sterownikiem karty graficznej poprzez API OpenGL.

Silnikami graficznymi zajmowałem się jeszcze w liceum przed studiami i obecnie zmieniły się raczej moje obszary zainteresowań na bardziej związane z cyberbezpieczeństwem, networkingiem oraz rynkiem embedded, ale ten projekt stanowił dla mnie taki gateway do technik niskopoziomowych i optymalizacji wydajności.

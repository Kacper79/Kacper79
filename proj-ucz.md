# Projekty uczelniane (stopniowo uzupełniane):

## 0. Projekt z aplikacji mobilnych (H2 2026) - TBA
## 0.Projekt z optymalizacji biznesowej (H2 2026) - WIP
Celem projektu jest użycie solvera ograniczeń IBM ILOG CPLEX do zamodelowania matematycznie oraz zaimplementowania problemu produkcyjnego oraz dystrybucyjnego.

## 0. Implementacja NER z Przetwarzania języka naturalnego (H2 2026) - WIP

# 1. Język DSL Robot2D (H1 2026)
**Na przedmiocie "Semantyka i Weryfikacja Programów"** trzeba było przygotować własny interpreter w narzędziu [SLANG](https://www3.risc.jku.at/research/formal/software/SLANG/) opartym na Java, który miał realizować poruszanie się robota (np. roomby) w dwuwymiarowej przestrzeni, za pomocą [specyfikacji](./robot2d-dokumentacja.pdf) SLANG.

Robot mógł się poruszać w cztery strony świata oraz obracać się (dokonywać rotacji o 90 stopni w lewo lub prawo) zmieniając kolejność kierunków. W dokumentacji projektu należało sprecyzować semantykę naturalną oraz denotacyjną dla tego problemu oraz żeby pokazać poprawność programu, pokazać że obie semantyki zwracają te same wyniki.

Narzędzie SLANG było nietypowe, bo generowało gotowy interpreter języka DSL jako kod źrodłowy Java za pomocą biblioteki ANTLR na podstawie specyfikacji języka we własnym formacie tekstowym.

[**SLANG**](https://www3.risc.jku.at/research/formal/software/SLANG/) &emsp;&emsp; [**Dokumentacja Robot2D**](./robot2d-dokumentacja.pdf) 

# 2. Skaner amplifikacji do testowania podatności na DDOS (H2 2025)
**Na przedmiocie "Systemy rozproszone i przetwarzanie równoległe"** miałem za zadanie przygotować skaner amplifikacji w C++, który wykorzystuje wyznaczone **protokoły (DNS, NTP, SNMP)** a konkretnie podatności w konfiguracji ich serwerów aby dokonać amplifikacji, na której można **oprzeć przyszłe ataki DDoS.** Projekt został zrealizowany jako prosty konsolowy program, gdzie można mu podać jako argumenty wybrany protkół oraz adres IP/ domenę DNS.

[**Prezentacja**](./AmplificationScanner.pdf) &emsp;&emsp; [**Projekt na GitHub**](https://github.com/Kacper79/ddos-tools)

# 3. Implementacja algorytmu genetycznego (H2 2025)
**Na przedmiocie "Algorytmy Inspirowane Naturą"** zajmowałem się tworzeniem algorytmów genetycznych dla problemów jednokryterialnych oraz wielokryterialnych (wykorzystując algorytm **NSGA-II**). Eksperymentowałem z parametrami algorytmu dla funkcji benchmarkowych - ZDT1-3 + ZDT4 + ZDT6 dla funkcji wielokryterialnych oraz funkcji Rosenbrock, Whitley, Solomon dla jednokryterialnej.

[**Sprawozdanie Jednokryterialne**](./alin-kol1-sprawozdanie-ks.pdf) &emsp;&emsp; [**Sprawozdanie wielokryterialne**](./ALIN-KOL2-Wyniki.pdf)

# 4. Administracja systemem komputerowym - Linux + Cisco (2025)
**Na przedmiocie "Administrowanie Systemami i Sieciami Komputerowymi"** zajmowałem się administracją małej sieci komputerów roboczych i dwóch serwerów Dell w postaci Rack mających symulować infrastrukturę średniej firmy. Na serwerach postawiłem Ubuntu Linux i ustawiłem je w roli software routera stanowiących gateway. Serwery mialy postawione usługi DHCP, DNS, VPN, Keepalived (protokól VRRP) dla redundencji routerów. Na switchach cisco ustawiłem zabezpieczenia w tym odpowiednią segmentacje sieci za pomocą VLAN. Finalnym efektem było, że przepięcie kabla ethenet stacji roboczej do switcha pomiędzy portami należącymi do innego VLANu powodowało przydzielenie innego adresu IP - adresu IP z puli danej podsieci DHCP. Udało się podpiąć wcześniej istniejące maszyny wirtualne Active Directory pod moją sieć, tak aby użytkownicy mogli się logować przez stacje robocze do AD i otrzymywali odpowiednią adresacje IP. Ustawiłem odpowiedni DNS Relay, zabezpieczyłem przeciwko DHCP Snooping, ustawiłem Broadcast Storm, Sticky MAC.

[**Prezentacja postępów (przykładowa 3 Kwietnia)**](./assk-sprawozdanie-03.04.pdf) &emsp;&emsp; [**Dokumentacja projektu**]() &emsp;&emsp; [**Zdjęcia**]()

# Implementacją algorytmu Simplex - Nelder-Mead (H2 2025)
Na przedmiocie "Metody Numeryczne" miałem za zadanie przygotować implementacje algorytmu simplex (Nelder-Mead) w C++.

[**Prezentacja**](./NELDER-MEAD.pptx)

## 5. Implementacja strony WWW z Backend (Spring) + Frontend (Thymeleaf) w Java (H1 2025)

## 6. Projekt z chmury obliczeniowej (H1 2025)
Celem projektu było zaprojektowanie skomplikowanego systemu - w tym przypadku platformy e-learning do wykonania za pomocą technologii chmurowej (chmura GCP).
Projekt należało opisać w wymaganiach technicznych i biznesowych, spisać listę wykorzystywanych/planowanych technologia chmurowych oraz skosztorysować z grubsza koszt uruchomienia takiej aplikacji webowej.
Po wypełnieniu dokumentacji przystąpiono do implementacji usługi w chmurze GCP. Na sam koniec wykonano testy wydajnościowe oraz bezpieczeństwa.

## 7. Projekt zespołowy - Gra komputerowa "Escape Within Reach" w Unity (H2 2024)
Na projekcie zespołowym znalazłem się w grupie zamującej się grą komputerową - grze fabularna pierwszoosobowej w 3D (na Windowsa) polegająca na ucieczce gracza z
więzienia (czysty prison break). Aby uciec z więzienia trzeba się do tego przygotować poprzez wykonanie zadań (questów) dających przedmioty potrzebne do ucieczki oraz przekonanie pewnych więźniów, żeby nam pomogli. W finalnej ucieczce w ucieczce będą przeszkadzali strażnicy, a dostęp do niektórych stref więzienia będzie utrudniony i patrolowany. Gra będzie odzwierciedlała realia więzienne i realizować niektóre z
czynności/problemy jakie tam się dzieją np. bójki więźniów, hazard, przemycanie przedmiotów czy handlowanie nimi. Gra zostanie udostępniana jako release na githubie.

[**Projekt na GitHub**](https://github.com/Kacper79/UKSW_Escape_Within_Reach_Gr_1) &emsp;&emsp; [**Board Trello**](https://trello.com/b/6qdRppMN/uksw-escape-within-reach-gr1)  &emsp;&emsp; [**Dokumentacja techniczna projektu**](./proj-zesp1-gr1.pdf)

## 8. Zaliczenie Technik Cyfrowych z Arduino (H1 2024)

## 9. Zaliczenie Inżynierii Oprogramowania - System Informatyczny dla Czytelni (H1 2024)
Celem było przygotowanie prostego systemu obsługi czytelni z wykorzystaniem C++, UML oraz wzorców projektowych.

[**Projekt na GitHub**](https://github.com/Kacper79/INCzytelnia) &emsp;&emsp; [**Dokumentacja**](./in-oprog-proj-dok.pdf)

## 10. Projekt indywidualny w Java - nakładka GUI na Sniffer z lipcap (H1 2024)
Jako projekt indywidualny postanowiłem zrobić własny uproszczony klon Wireshark w Java na podstawie biblioteki libpcap. GUI zostało zaimplementowane z biblioteką Swing w Java oraz użyciem buildsystemu Gradle.

[**Projekt na GitHub**](https://github.com/UKSWPI2024LatoD/sniffer-java)  &emsp;&emsp; [**Dokumentacja techniczna projektu**](./proj-ind-dokumentacja.pdf)

## 11. Projekt na programowanie obiektowe - gra logiczna Quoridor w C++ z TUI (H2 2023)
Jako projekt zaliczający programowanie obiektowe miałem za zadanie przygotować implementacje gry logicznej - [Quoridor](https://en.wikipedia.org/wiki/Quoridor) w C++ w terminalu. Można grać w wariancie od jednym do czterech graczy, z czego pozostali gracze są obsługiwani przez komputer.
Aby urozmaicić sobie ten projekt, zaprojektowałem elementy TUI jako oddzielne klasy (dla widoków różnych - menu, gra, tworzenie gry) oraz dodałem wygodne sterowanie z klawiatury oraz wyświetlanie kolorów.

[**Projekt na GitHub**](https://github.com/Kacper79/Quoridor) [**Dokumentacja techniczna**](./manual_PO.pdf)

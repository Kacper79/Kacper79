# Projekty uczelniane (Work In Progress):

# 1. Język DSL Robot2D (H1 2026)
**Na przedmiocie "Semantyka i Weryfikacja Programów"** trzeba było przygotować własny interpreter w narzędziu [SLANG](https://www3.risc.jku.at/research/formal/software/SLANG/) opartym na Java, który miał realizować poruszanie się robota (np. roomby) w dwuwymiarowej przestrzeni, za pomocą [specyfikacji](./robot2d-dokumentacja.pdf) SLANG.

Robot mógł się poruszać w cztery strony świata oraz obracać się (dokonywać rotacji o 90 stopni w lewo lub prawo) zmieniając kolejność kierunków. W dokumentacji projektu należało sprecyzować semantykę naturalną oraz denotacyjną dla tego problemu oraz żeby pokazać poprawność programu, pokazać że obie semantyki zwracają te same wyniki.

Narzędzie SLANG było nietypowe, bo generowało gotowy interpreter języka DSL jako kod źrodłowy Java za pomocą biblioteki ANTLR na podstawie specyfikacji języka we własnym formacie tekstowym.

[**SLANG**](https://www3.risc.jku.at/research/formal/software/SLANG/) &emsp;&emsp; [**Dokumentacja Robot2D**](./robot2d-dokumentacja.pdf) 

# 2. Skaner amplifikacji do testowania podatności na DDOS (H2 2025)
**Na przedmiocie "Systemy rozproszone i przetwarzanie równoległe"** miałem za zadanie przygotować skaner amplifikacji w C++, który wykorzystuje wyznaczone **protokoły (DNS, NTP, SNMP)** a konkretnie podatności w konfiguracji ich serwerów aby dokonać amplifikacji, na której można **oprzeć przyszłe ataki DDoS.** Projekt został zrealizowany jako prosty konsolowy program, gdzie można mu podać jako argumenty wybrany protkół oraz adres IP/ domenę DNS.

[**Prezentacja**](./AmplificationScanner.pptx) &emsp;&emsp; [**Projekt na GitHub**](https://github.com/Kacper79/ddos-tools)

# 3. Implementacja algorytmu genetycznego (H2 2025)
**Na przedmiocie "Algorytmy Inspirowane Naturą"** zajmowałem się tworzeniem algorytmów genetycznych dla problemów jednokryterialnych oraz wielokryterialnych wykorzystując algorytm **NSGA-II**. Eksperymentowałem z parametrami algorytmu dla funkcji benchmarkowych - ZDT1-3 + ZDT4 + ZDT6 dla funkcji wielokryterialnych oraz funkcji Rosenbrock, Whitley, Solomon dla jednokryterialnej.

[**Sprawozdanie Jednokryterialne**]() &emsp;&emsp; [**Sprawozdanie wielokryterialne**]()

# 4. Administracja systemem komputerowym - Linux + Cisco (2025)
**Na przedmiocie "Administrowanie Systemami i Sieciami Komputerowymi"** zajmowałem się administracją małej sieci komputerów roboczych i dwóch serwerów Dell w postaci Rack mających symulować infrastrukturę średniej firmy. Na serwerach postawiłem Ubuntu Linux i ustawiłem je w roli software routera stanowiących gateway. Serwery mialy postawione usługi DHCP, DNS, VPN, Keepalived (protokól VRRP) dla redundencji routerów. Na switchach cisco ustawiłem zabezpieczenia w tym odpowiednią segmentacje sieci za pomocą VLAN. Finalnym efektem było, że przepięcie kabla ethenet stacji roboczej do switcha pomiędzy portami należącymi do innego VLANu powodowało przydzielenie innego adresu IP - adresu IP z puli danej podsieci DHCP. Udało się podpiąć wcześniej istniejące maszyny wirtualne Active Directory pod moją sieć, tak aby użytkownicy mogli się logować przez stacje robocze do AD i otrzymywali odpowiednią adresacje IP. Ustawiłem odpowiedni DNS Relay, zabezpieczyłem przeciwko DHCP Snooping, ustawiłem Broadcast Storm, Sticky MAC.

# Implementacją algorytmu Simplex - Nelder-Mead (H2 2025)
Na przedmiocie "Metody Numeryczne" miałem za zadanie przygotować implementacje algorytmu simplex.

[**Prezentacja**](./NELDER-MEAD.pptx)

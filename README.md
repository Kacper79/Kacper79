# 👋 Cześć, jestem Kacper !

Obecnie studiuje Informatykę na UKSW (studia magisterskie). Od zawsze interesowały mnie komputery jak działają od samych podstaw - od strony krzemu, systemu operacyjnego do wspólczesnych aplikacji. Nic dziwnego więc że **interesuje mnie niskopoziomowe programowanie, wchodzenie w szczegóły abstrakcji czy okazjonalne wynajdywania koła na nowo**. Mam wiele obszarów zainteresowań, które staram się poszerzać z własnej ciekawości a może w przyszłości zmonetyzować. Moje ciągłe poszerzanie wiedzy i pewne doświadczenie życiowe sprawiło że nie boję się sprostać wyzwaniom lub cięższym projektom.

[LinkedIn](https://www.linkedin.com/in/kacper-smykla-1a1344359/) &emsp;&emsp;  [Google Skills](https://www.skills.google/public_profiles/f45865be-b1e5-48ef-bbb6-3f2c64acdc77) &emsp;&emsp; [Prace dyplomowe](#-prace-dyplomowe) &emsp;&emsp; [Projekty uczelniane](./proj-ucz.md) &emsp;&emsp; [Projekty personalne](./proj-person.md) <br> [Kontakt mailowy](mailto:kacper@smykla.pl)

**Języki programowania:** C, C++, Java, Python
# Obszary zainteresowań:
## 🛡️ Cybersecurity
Jednym z moich obszarów zainteresowań jest obszar cyberbezpieczeństwa i związanej z nią prywatności. Rozwiązywałem zadania z poprzednich CTF i analizowałem programy w C i C++, które zawierały podatności na nieprawidłowe korzystanie z funkcji bibliotecznych i wykorzystywałem w praktyczny sposób piszać exploity. Eksperymentowałem z gotowymi narzędziami do ekspolitacji podatności w Acitve Directory (AD).
Na studiach przygotowałem w ramach projektu mały skaner podatności na ataki DDoS mierzącą amplifikacje jaką da się otrzymać od danego źródła i sprawdzajacego podatności w kilku protokołach. Pisałem [pracę licencjacką](#-prace-dyplomowe) związaną z cyberbezpieczeństwem - klasyfikacją ruchu sieciowego oraz miałem kilka [projektów uczelnianych](./projekty-uczelniane.md) z tym związanych.

## 🔌 Embedded 
Embedded jest obszarem gdzie najłatwiej spełnić się w niskopoziomowym programowaniu i gdzie chciałbym pogłębiać moje kompetencje. Na uczelni zajmowałem się prostym projektem z Arduino, który mnie zainteresował i zwrócił w stronę rynku urządzeń wbudowanych. 
Dodatkowo po zajęciach z administracją sieci zacząłem się interesować stworzeniem własnego switcha - zaprojektowaniem własnej płytki PCB w KiCAD z wybranymi komponentami (Microchip) oraz FPGA (Lattice) na pokładzie. Częściowa weryfikacja poprawności płytki PCB (schematic) to jest temat jaki zamierzam rozważać na [pracy magisterskiej](#-prace-dyplomowe).

## 🐧  Administracja Linux + Networking
Od kilku lat jestem użytkownikiem **Arch Linuxa**. W związku z tym nabyłem umiejętności instalacji, naprawiania i konfigurowania linuksów, co bardzo mi się przydało na uczelni na przedmiocie zwiazanym z administracją sieciami komputerowymi. **Odpowiadałem za ustawianie prawidłowej segmentacji sieci i zabezpieczeń na switchach Cisco, przydzielaniem puli adresów IP z oddzielną adresacją przez DHCP i powiązaniem ich z każdym VLAN (każdej grupy).** Ustawiałem dwa serwery Rack w roli software routera na linuksie, gdzie postawiłem i skonfigurowałem usługi DHCP, DNS, VPN, firewalla (iptables), Keepalived (VRRP) dla redundencji pomiędzy dwoma serwerami. **Udało mi się dodać do tego integrację z obecnie postawionym Active Directory i NPS (802.1X).** Po wszystkich tych rzeczach osiągnałem stan, w którym **przepięcie kabla ethernet (wybranej stacji roboczej) pomiędzy różnymi portami z różnymi przypisanymi VLAN pozwalało na przydzielenie nowego adresu IP z odpowiednią adresacją od DHCP i podłączenie się do AD.** Planuje w przyszłości odtworzyć podobny scenariusz w zwirtualizowanym środowisku z GNS3 i VMWare.

# 🎓 Prace dyplomowe:
## Licencjat - klasyfikacja szkodliwości ruchu sieciowego
Na [licencjacie](./licencjat.pdf) zająłem się tematem związanym z cyberbezpieczeństwem - **klasyfikacją ruchu sieciowego jako szkodliwy lub nie.** Klasyfikacja odbywała się za pomocą sieci neuronowych - **połączenia sieci CNN + LSTM, gdzie sam pakiet był przetwarzany z pliku ruchu sieciowego (.pcap) do postaci raw byte array oraz wydobywane dane z nagłówków.** Połączenie CNN + LSTM było testowane z różnymi alternatywami modelami: CNN,Transformer, zwykłej sieci głębokiej - DNN oraz metodami klasycznymi z SVM oraz Random Forest. Wykorzystałem popularny **zbior danych CIC-IDS-2017, CTU-13 oraz generowania własnych danych syntetycznych** dla scenariusza DDoS do wyćwiczenia modelu.

## Magister - wykorzystanie LLM do znajdywania błędów w płytkach PCB
Obcenie zaczynam pisać pracę magisterską związaną z wykrywaniem błędów w podawanych przez użytkownika diagramów schematic dla płytek PCB. **Chciałbym poprawić jakość LLM w rozumieniu płytek PCB, aby móc je wykorzystać do wychwytywania oczywistych błędów. Praca składa się trzech elementów: walidatora, RAG oraz LLM.**

Formaty precyzowania połączeń pomiędzy układmi IC (netlists albo schematic) są mało czytelne dla człowieka i strasznie długie co powoduje że LLM nie radzą sobie dobrze z ich przetwarzaniem. **Moim rozwiązaniem jest stworzenie własnego formatu tekstowego opisującego PCB, który ma za zadanie w czytelny, prostszy i bardziej ustrukturyzowany sposób wyrażać połączenia pomiędzy pinami**.

**Aby uniknąć halucynacji napisze własny walidator (parsing + sprawdzenie semantyki) w C++ dla mojego formatu tekstowego**, który by w deterministyczny sposób sprawdzał poprawność składniową (czy AI poprawnie się posługuje moim formatem tekstowym, który narzuca strukturę) oraz semantyczną (czy sprecyzowane połączenia wydają się łamać jakieś reguły a więc być mało sensowne i wymagać zmian). Walidator służy do weryfikacji swojej odpowiedzi - oceny swoich poprawek oraz oceny płytki PCB podanej przez użytkownika.

Na poczatku odpalany jest potok przetwarzania, który z wybranych linków pobiera albo przyjmuje z podanych plików pdf dokumentacje technicznej dla układów IC. **Na dokumentacji odpalany jest RAG, który wydobywa użyteczne informacje z dokumentacji i produkuje graf wiedzy, który może być wykorzystany przez LLM proponujący zmiany.** Potem wykorzystuje jakiś gotowy pre-trained model VLLM do analizy płytki PCB podanej w moim formacie oraz ewentualnie opisu użytkownika. **Model LLM może częściowo sprawdzać poprawność swojej odpowiedzi poprzez wykonywanie walidatora oraz wydobytych informacji z grafu wiedzy wyprodukowanego przez RAG.**
Jest też możliwość zastosowania technik RL - RLVR lub GRPO.

Wydajność mojego LLM z RAG + walidatorem jest testowana przeciw komercyjnym modelom LLM, zwykłemu SLM na benchmarkach związanych z płytkami PCB (PCB Bench) oraz wybranym projektom małych płytek PCB z zweryfikowanymi błędami / sugestiami poprawy.


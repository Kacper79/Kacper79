#include <iostream>
#include <string>
#include <cstdlib>

#ifndef _WIN32
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#else
// link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <algorithm> // Dla std::max

// Stale konfiguracyjne
#define PORT 8080
#define IP_ADDRESS "127.0.0.1"
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// Uzywamy tego wskaznika do obslugi bledow
void error_exit(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Funkcja pomocnicza: Oblicza kwadrat
int calculate_square(int n) {
    return n * n;
}

/**************************************************
 * ZADANIE 4.2: Klient/Serwer na gniezdzie niepodlaczonym (UDP)
 **************************************************/

void server_udp() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    int n, number, result;

    std::cout << "--- Serwer UDP: Start ---" << std::endl;

    // Tworzenie gniazda
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_exit("Blad tworzenia gniazda UDP");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Wypelnianie informacji o serwerze
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bindowanie gniazda
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        error_exit("Blad bindowania gniazda UDP");
    }

    std::cout << "Serwer UDP nasluchuje na porcie " << PORT << std::endl;

    while (true) {
        // Odbior danych od klienta
        n = recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&cliaddr, &len);
        if (n < 0) {
            perror("Blad recvfrom");
            continue;
        }
        buffer[n] = '\0'; // zakonczenie odebranego bufora

        // Konwersja odebranej wiadomosci na liczbe
        try {
            number = std::stoi(std::string(buffer));
            result = calculate_square(number);

            std::cout << "Odebrano od klienta (" << inet_ntoa(cliaddr.sin_addr) << ":" << ntohs(cliaddr.sin_port) << "): "
                << number << ". Wynik: " << result << std::endl;

            // Przygotowanie odpowiedzi
            std::string response = std::to_string(result);
            const char* response_c_str = response.c_str();

            // wysylanie odpowiedzi
            sendto(sockfd, response_c_str, response.length(), 0, (const struct sockaddr*)&cliaddr, len);

        }
        catch (const std::exception& e) {
            std::cerr << "Blad konwersji danych: " << e.what() << ". Odebrano: " << buffer << std::endl;
        }
    }

    close(sockfd);
}

void client_udp(const char* number_str) {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    int n;

    std::cout << "--- Klient UDP: Start ---" << std::endl;

    // Tworzenie gniazda
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_exit("Blad tworzenia gniazda UDP");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Wypelnianie informacji o serwerze
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP_ADDRESS, &servaddr.sin_addr) <= 0) {
        error_exit("Bladny adres IP serwera");
    }

    std::cout << "wysylanie liczby: " << number_str << " do " << IP_ADDRESS << ":" << PORT << std::endl;

    // wysylanie danych do serwera (uzywamy sendto, bo gniazdo nie jest polaczone)
    if (sendto(sockfd, number_str, strlen(number_str), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        error_exit("Blad sendto");
    }

    // Odbiór odpowiedzi (uzywamy recvfrom)
    n = recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&servaddr, &len);
    if (n < 0) {
        error_exit("Blad recvfrom przy odbieraniu odpowiedzi");
    }
    buffer[n] = '\0';

    std::cout << "Odebrana odpowiedz (kwadrat): " << buffer << std::endl;

    close(sockfd);
}

/**************************************************
 * ZADANIE 4.3: Klient/Serwer na gniezdzie polaczonym (TCP, pojedyncze polaczenie)
 **************************************************/

void server_tcp_single() {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[BUFFER_SIZE];
    int number, result;

    std::cout << "--- Serwer TCP (Pojedynczy): Start ---" << std::endl;

    // Tworzenie gniazda
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_exit("Blad tworzenia gniazda TCP");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bindowanie i nasluchiwanie
    if (bind(listenfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        error_exit("Blad bindowania TCP");
    }
    if (listen(listenfd, 5) < 0) {
        error_exit("Blad nasluchiwania TCP");
    }

    std::cout << "Serwer TCP nasluchuje na porcie " << PORT << ". Czekam na pojedynczego klienta..." << std::endl;

    while (true) {
        len = sizeof(cliaddr);
        // Akceptacja nowego polaczenia
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        if (connfd < 0) {
            perror("Blad akceptacji");
            continue;
        }

        std::cout << "Zaakceptowano polaczenie od klienta (" << inet_ntoa(cliaddr.sin_addr) << ":" << ntohs(cliaddr.sin_port) << ")" << std::endl;

        // Odbiór danych (read)
        ssize_t n = read(connfd, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            buffer[n] = '\0';
            try {
                number = std::stoi(std::string(buffer));
                result = calculate_square(number);

                std::cout << "Odebrano: " << number << ". Wynik: " << result << std::endl;

                // Wyslanie odpowiedzi (write)
                std::string response = std::to_string(result);
                write(connfd, response.c_str(), response.length());

            }
            catch (const std::exception& e) {
                std::cerr << "Blad konwersji danych: " << e.what() << std::endl;
            }
        }
        else if (n == 0) {
            std::cout << "Klient rozlaczyl sie." << std::endl;
        }
        else {
            perror("Blad odczytu z gniazda");
        }

        // Zamkniecie polaczenia z klientem
        close(connfd);
        std::cout << "Zamknieto polaczenie z klientem. Czekam na nastepne..." << std::endl;
    }

    close(listenfd); // Ten kod nie zostanie osiegniety w petli while(true)
}

// Funkcja klienta TCP (uzywana dla 4.3 i 4.4)
void client_tcp(const char* number_str) {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    int number;

    std::cout << "--- Klient TCP: Start ---" << std::endl;

    // Sprawdzenie, czy to jest poprawna liczba
    try {
        number = std::stoi(std::string(number_str));
    }
    catch (const std::exception& e) {
        std::cerr << "Blad: Argument nie jest poprawna liczba." << std::endl;
        return;
    }

    // Tworzenie gniazda
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_exit("Blad tworzenia gniazda TCP");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP_ADDRESS, &servaddr.sin_addr) <= 0) {
        error_exit("Bladny adres IP serwera");
    }

    // Laczenie z serwerem (connected socket)
    if (connect(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        error_exit("Blad polaczenia z serwerem TCP");
    }

    std::cout << "polaczono z serwerem. Wysylam liczbe: " << number_str << std::endl;

    // Wyslanie danych
    if (write(sockfd, number_str, strlen(number_str)) < 0) {
        error_exit("Blad zapisu do gniazda");
    }

    // Odbiór odpowiedzi
    ssize_t n = read(sockfd, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "Odebrana odpowiedz (kwadrat): " << buffer << std::endl;
    }
    else if (n == 0) {
        std::cout << "Serwer zamknal polaczenie." << std::endl;
    }
    else {
        perror("Blad odczytu z gniazda");
    }

    close(sockfd);
}

/**************************************************
 * ZADANIE 4.4: Zarzadzanie wieloma polaczeniami (TCP, select())
 **************************************************/

void handle_tcp_client(int connfd, char* buffer) {
    // Odbiór danych
    ssize_t n = read(connfd, buffer, BUFFER_SIZE - 1);
    int number, result;

    if (n > 0) {
        buffer[n] = '\0';
        try {
            number = std::stoi(std::string(buffer));
            result = calculate_square(number);

            std::cout << "Odebrano (fd " << connfd << "): " << number << ". Wynik: " << result << std::endl;

            // Wyslanie odpowiedzi
            std::string response = std::to_string(result);
            write(connfd, response.c_str(), response.length());

        }
        catch (const std::exception& e) {
            std::cerr << "Blad konwersji danych: " << e.what() << std::endl;
        }
    }
    else if (n == 0) {
        // Klient zamknal polaczenie
        std::cout << "Klient (fd " << connfd << ") rozlaczyl sie." << std::endl;
        close(connfd);
    }
    else {
        perror("Blad odczytu/zapisu z gniazda");
        close(connfd);
    }
}


void server_tcp_select() {
    int master_socket, addrlen, new_socket, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[BUFFER_SIZE];
    int client_socket[MAX_CLIENTS];

    std::cout << "--- Serwer TCP (Select): Start ---" << std::endl;

    // Inicjalizacja tablicy gniazd
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }

    // Tworzenie glownego gniazda nasluchujacego
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        error_exit("Blad tworzenia gniazda master");
    }

    // Opcjonalne: Ustawienie opcji, aby uniknac Bladu "Address already in use"
    int opt = 1;
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
    }

    // Ustawienia adresowe
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bindowanie
    if (bind(master_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        error_exit("Blad bindowania TCP");
    }

    // Nasluchiwanie
    if (listen(master_socket, 5) < 0) {
        error_exit("Blad nasluchiwania TCP");
    }

    addrlen = sizeof(address);
    std::cout << "Serwer TCP (Select) nasluchuje na porcie " << PORT << ". Czekam na polaczenia..." << std::endl;

    while (true) {
        // Wyczysc zestaw gniazd (file descriptor set)
        fd_set readfds;
        FD_ZERO(&readfds);

        // Dodaj gniazdo master do zestawu
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // Dodaj gniazda podlaczonych klientów do zestawu
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }
            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // Uzycie funkcji select() - czeka na aktywnosc na jednym z gniazd
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL); // NULL timeout = czekanie w nieskonczonosc

        if ((activity < 0) && (errno != EINTR)) {
            printf("Blad select\n");
        }

        // Jesli aktywnosc jest na gniezdzie master, to jest to nowe polaczenie
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Blad accept");
            }
            else {
                std::cout << "Nowe polaczenie, gniazdo fd " << new_socket
                    << ", IP: " << inet_ntoa(address.sin_addr)
                    << ", Port: " << ntohs(address.sin_port) << std::endl;

                // Dodaj nowe gniazdo do tablicy
                for (i = 0; i < MAX_CLIENTS; i++) {
                    if (client_socket[i] == 0) {
                        client_socket[i] = new_socket;
                        std::cout << "Dodano do listy gniazd na pozycji " << i << std::endl;
                        break;
                    }
                }
            }
        }

        // Sprawdz pozostale gniazda klientów pod katem danych do odczytu
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                // Jest aktywnosc na tym gniezdzie
                handle_tcp_client(sd, buffer);

                // Sprawdz, czy gniazdo zostalo zamkniete w handle_tcp_client
                // Jesli read zwróci 0 (zamkniecie) lub <0 (Blad), gniazdo jest zamkniete
                // W tym przykladzie po prostu zerujemy wpis, poniewaz zamkniecie jest juz obsluzone w funkcji
                // W bardziej zlozonym przypadku, to samo gniazdo bedzie mialo nowa wartosc sd po obsludze
                if (close(sd) == 0) {
                    client_socket[i] = 0; // Usun z listy
                }
                else {
                    // Poniewaz handle_tcp_client tez zamyka, ponowne close() moze sie nie udac
                    // W profesjonalnym kodzie nalezaloby to lepiej obsluzyc
                    client_socket[i] = 0;
                }
            }
        }
    }

    // Zamkniecie gniazda master - kod nieosiagalny
    close(master_socket);
}


// Glówna funkcja programu, parsujaca argumenty
int main(int argc, char* argv[]) {
    // Uzycie: ./socket_programming <tryb> [liczba]
    // Tryby: server_udp, client_udp, server_tcp_single, server_tcp_select, client_tcp
    // Przyklad:
    // Serwer UDP: ./socket_programming server_udp
    // Klient UDP: ./socket_programming client_udp 15
    // Serwer TCP (select): ./socket_programming server_tcp_select
    // Klient TCP: ./socket_programming client_tcp 4
    if (argc < 2) {
        std::cerr << "Uzycie: " << argv[0] << " <tryb> [liczba]" << std::endl;
        std::cerr << "Dostepne tryby serwera: server_udp, server_tcp_single, server_tcp_select" << std::endl;
        std::cerr << "Dostepne tryby klienta: client_udp <liczba>, client_tcp <liczba>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string mode = argv[1];

    if (mode == "server_udp") {
        server_udp();
    }
    else if (mode == "client_udp") {
        if (argc < 3) {
            std::cerr << "Blad: Brak liczby dla klienta UDP." << std::endl;
            return EXIT_FAILURE;
        }
        client_udp(argv[2]);
    }
    else if (mode == "server_tcp_single") {
        server_tcp_single();
    }
    else if (mode == "server_tcp_select") {
        server_tcp_select();
    }
    else if (mode == "client_tcp") {
        if (argc < 3) {
            std::cerr << "Blad: Brak liczby dla klienta TCP." << std::endl;
            return EXIT_FAILURE;
        }
        client_tcp(argv[2]);
    }
    else {
        std::cerr << "Nieznany tryb: " << mode << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

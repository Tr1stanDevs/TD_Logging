#include "TD_Logging.hpp"
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    // ========== KONFIGURATION ==========
    // Aktiviere alle Features
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BLINKING;
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_PREFIX;
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BOLD;
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_TIME;
    TD_Logging::Settings |= TD_Logging::LoggingLevels::LogLevel_ALL;
    
    TD_Logging::Init();
    
    std::cout << "\n========== TEST 1: GRUNDLEGENDE AUSGABEN ==========\n" << std::endl;
    
    // Einfache Nachrichten
    TD_Logging::print("Einfache Nachricht\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("Erfolgsmeldung\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS);
    TD_Logging::print("Warnung\n", TD_Logging::LoggingLevels::LogLevel_WARN);
    TD_Logging::print("Fehler aufgetreten\n", TD_Logging::LoggingLevels::LogLevel_ERROR);
    
    std::cout << "\n========== TEST 2: FORMATIERTE AUSGABEN ==========\n" << std::endl;
    
    // Mit Formatierung
    int zahl = 42;
    double pi = 3.14159;
    std::string name = "Alice";
    
    TD_Logging::print("Zahl: %d, Pi: %.2f\n", TD_Logging::LoggingLevels::LogLevel_INFO, zahl, pi);
    TD_Logging::print("Benutzer %s hat sich angemeldet (ID: %d)\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, name.c_str(), 1001);
    TD_Logging::print("Warnung: Speichernutzung bei %d%%\n", TD_Logging::LoggingLevels::LogLevel_WARN, 85);
    TD_Logging::print("Kritischer Fehler in Modul %s: Code 0x%X\n", TD_Logging::LoggingLevels::LogLevel_ERROR, "AuthModule", 0xDEADBEEF);
    
    std::cout << "\n========== TEST 3: MEHRERE PARAMETER ==========\n" << std::endl;
    
    // Viele Parameter
    TD_Logging::print("%d + %d = %d\n", TD_Logging::LoggingLevels::LogLevel_INFO, 10, 20, 30);
    TD_Logging::print("Werte: %f, %f, %f\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, 1.1, 2.2, 3.3);
    TD_Logging::print("String: %s, Char: %c, Int: %d, Hex: %X\n", 
                      TD_Logging::LoggingLevels::LogLevel_INFO, 
                      "Test", 'X', 255, 255);
    
    std::cout << "\n========== TEST 4: LOGLEVEL FILTERUNG ==========\n" << std::endl;
    
    // Teste verschiedene Loglevel-Kombinationen
    TD_Logging::remove_setting(TD_Logging::LoggingLevels::LogLevel_ALL);
    
    // Nur INFO und ERROR aktivieren
    TD_Logging::Settings |= TD_Logging::LoggingLevels::LogLevel_INFO;
    TD_Logging::Settings |= TD_Logging::LoggingLevels::LogLevel_ERROR;
    
    TD_Logging::print("Diese INFO wird angezeigt\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("Diese WARN wird NICHT angezeigt\n", TD_Logging::LoggingLevels::LogLevel_WARN);
    TD_Logging::print("Dieser ERROR wird angezeigt\n", TD_Logging::LoggingLevels::LogLevel_ERROR);
    TD_Logging::print("Diese SUCCESS wird NICHT angezeigt\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS);
    
    std::cout << "\n========== TEST 5: ALLE LEVEL AKTIVIEREN ==========\n" << std::endl;
    
    // Alle Level aktivieren
    TD_Logging::Settings |= TD_Logging::LoggingLevels::LogLevel_ALL;
    
    TD_Logging::print("INFO Level Test\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("SUCCESS Level Test\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS);
    TD_Logging::print("WARN Level Test\n", TD_Logging::LoggingLevels::LogLevel_WARN);
    TD_Logging::print("ERROR Level Test\n", TD_Logging::LoggingLevels::LogLevel_ERROR);
    
    std::cout << "\n========== TEST 6: VERSCHIEDENE TEXTLAENGEN ==========\n" << std::endl;
    
    // Kurze und lange Texte
    TD_Logging::print("Kurz\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("Ein etwas längerer Text um zu testen wie das System mit längeren Nachrichten umgeht und ob der Puffer gross genug ist\n", 
                      TD_Logging::LoggingLevels::LogLevel_INFO);
    
    // Sehr langer Text (Puffergrenze testen)
    std::string long_text(800, 'A');  // 800 'A's
    TD_Logging::print("Langer Text: %s\n", TD_Logging::LoggingLevels::LogLevel_WARN, long_text.c_str());
    
    std::cout << "\n========== TEST 7: SPEZIALZEICHEN ==========\n" << std::endl;
    
    // Sonderzeichen testen
    TD_Logging::print("Sonderzeichen: !@#$%%^&*()_+{}[]|\\:;\"'<>,.?/~`\n", 
                      TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("Unicode: äöüß€\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("Tabulator\tTest\nNeue\nZeile\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    std::cout << "\n========== TEST 8: ZAHLENFORMATE ==========\n" << std::endl;
    
    // Verschiedene Zahlenformate
    TD_Logging::print("Dezimal: %d\n", TD_Logging::LoggingLevels::LogLevel_INFO, -12345);
    TD_Logging::print("Unsigned: %u\n", TD_Logging::LoggingLevels::LogLevel_INFO, 4294967295U);
    TD_Logging::print("Hexadezimal: %X\n", TD_Logging::LoggingLevels::LogLevel_INFO, 0xFF00FF);
    TD_Logging::print("Oktal: %o\n", TD_Logging::LoggingLevels::LogLevel_INFO, 0755);
    TD_Logging::print("Fliesskomma: %f\n", TD_Logging::LoggingLevels::LogLevel_INFO, 123.456);
    TD_Logging::print("Wissenschaftlich: %e\n", TD_Logging::LoggingLevels::LogLevel_INFO, 12345.6789);
    TD_Logging::print("Prozentzeichen: %%\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    std::cout << "\n========== TEST 9: KOMBINATIONEN DER FLAGS ==========\n" << std::endl;
    
    // Nur bestimmte Features testen
    TD_Logging::Settings = 0;  // Reset
    TD_Logging::Settings |= TD_Logging::LoggingLevels::LogLevel_ALL;
    
    // Nur Prefix (keine Zeit, kein Bold, kein Blinking)
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_PREFIX;
    TD_Logging::print("Nur Prefix (keine Zeit, kein Bold)\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    // Prefix + Time
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_TIME;
    TD_Logging::print("Prefix + Zeit\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    // Prefix + Time + Bold
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BOLD;
    TD_Logging::print("Prefix + Zeit + Bold\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    // Prefix + Time + Bold + Blinking
    TD_Logging::Settings |= TD_Logging::LoggingFlags::PRINT_BLINKING;
    TD_Logging::print("Alle Features (Prefix, Zeit, Bold, Blinking)\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    std::cout << "\n========== TEST 10: REMOVE_SETTING FUNKTION ==========\n" << std::endl;
    
    // Teste remove_setting
    TD_Logging::remove_setting(TD_Logging::LoggingFlags::PRINT_BLINKING);
    TD_Logging::print("Nach remove_setting(BLINKING) - kein Blinken mehr\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    TD_Logging::remove_setting(TD_Logging::LoggingFlags::PRINT_BOLD);
    TD_Logging::print("Nach remove_setting(BOLD) - kein Bold mehr\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    TD_Logging::remove_setting(TD_Logging::LoggingFlags::PRINT_TIME);
    TD_Logging::print("Nach remove_setting(TIME) - keine Zeit mehr\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    std::cout << "\n========== TEST 11: PERFORMANCE TEST (1000 AUSGABEN) ==========\n" << std::endl;
    
    // Performance test
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10; i++) {
        TD_Logging::print("Iteration %d von 10\n", TD_Logging::LoggingLevels::LogLevel_INFO, i);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    TD_Logging::print("1000 Ausgaben benoetigten %lld ms\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, duration.count());
    
    std::cout << "\n========== TEST 12: FEHLERFÄLLE ==========\n" << std::endl;
    
    // Leere Strings
    TD_Logging::print("", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    
    // Null-ähnliche Fälle (was passiert bei fehlenden Parametern?)
    TD_Logging::print("%s\n", TD_Logging::LoggingLevels::LogLevel_INFO, "(null)");
    
    // Sehr kurze Nachrichten
    TD_Logging::print("A\n", TD_Logging::LoggingLevels::LogLevel_INFO);
    TD_Logging::print("B\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS);
    TD_Logging::print("C\n", TD_Logging::LoggingLevels::LogLevel_WARN);
    TD_Logging::print("D\n", TD_Logging::LoggingLevels::LogLevel_ERROR);
    
    std::cout << "\n========== TEST 13: PRAKTISCHE ANWENDUNGSFÄLLE ==========\n" << std::endl;
    
    // Simulations-Szenarien
    TD_Logging::print("Server startet auf Port %d\n", TD_Logging::LoggingLevels::LogLevel_INFO, 8080);
    TD_Logging::print("Verbindung zu Datenbank %s:%d hergestellt\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, "localhost", 3306);
    TD_Logging::print("Cache-Hit-Rate: %.1f%%\n", TD_Logging::LoggingLevels::LogLevel_INFO, 87.5);
    TD_Logging::print("Benutzer %s hat das Passwort %d Mal falsch eingegeben\n", TD_Logging::LoggingLevels::LogLevel_WARN, "admin", 3);
    TD_Logging::print("Datei %s nicht gefunden (Fehler %d)\n", TD_Logging::LoggingLevels::LogLevel_ERROR, "config.json", 404);
    TD_Logging::print("Backup abgeschlossen: %zu Bytes kopiert\n", TD_Logging::LoggingLevels::LogLevel_SUCCESS, 1048576);
    
    std::cout << "\n========== TEST 14: PADDING UND FORMATIERUNG ==========\n" << std::endl;
    
    // Formatierte Ausgaben mit Padding
    TD_Logging::print("%-20s %10d %8.2f\n", TD_Logging::LoggingLevels::LogLevel_INFO, "Item", 100, 99.99);
    TD_Logging::print("%-20s %10d %8.2f\n", TD_Logging::LoggingLevels::LogLevel_INFO, "Another", 42, 12.50);
    TD_Logging::print("%-20s %10d %8.2f\n", TD_Logging::LoggingLevels::LogLevel_INFO, "Test", 7, 3.14);
    
    std::cout << "\n========== TEST 15: ZEIGER AUSGEBEN ==========\n" << std::endl;
    
    // Pointer ausgeben
    int test_var = 123;
    int* ptr = &test_var;
    TD_Logging::print("Adresse von test_var: %p\n", TD_Logging::LoggingLevels::LogLevel_INFO, ptr);
    TD_Logging::print("Wert: %d\n", TD_Logging::LoggingLevels::LogLevel_INFO, *ptr);
    
    std::cout << "\n========== ALLE TESTS ABGESCHLOSSEN ==========\n" << std::endl;
    
    return 0;
}
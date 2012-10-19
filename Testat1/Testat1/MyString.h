﻿#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <memory>

class String final { 
	// private Datenstruktur 
	size_t m_len;
	size_t m_start;
	std::shared_ptr<char> m_string;
public:
	// öffentliche Methoden 
	String();
	String(const String &);
	String(const char*);

	// Instanz-Methoden 
	char charAt(size_t index) const; // bei falschem Index: wirft exception 
	int compareTo(const String& s) const; // C++ untypische Funktion: gibt -1, 0, 1 zurück 
	String concat(char c) const; // hängt c ans Ende und gibt neuen String zurück 
	String concat(const String& s) const; 
	size_t length() const; // gibt die Länge des Strings zurück 
	// Substring des Bereichs [beg, end) 
	// falls beg ≥ m_len oder end ≤ beg: gibt leeren String zurück 
	String substring(size_t beg, size_t end) const; 
	// erzeugt 0-terminierten C-String, kopiert Inhalt und gibt Zeigerobjekt zurück 
	std::unique_ptr<char[]> toCString() const;

	// Gleichheitsoperator (Inline-Implementation schon gegeben) 
	bool operator==(const String& s) const { return compareTo(s) == 0; }

	// Ausgabe-Operator für Output-Streams (Inline-Implementation schon gegeben) 
	friend std::ostream& operator<<(std::ostream& os, const String& s) { 
		const size_t end = s.m_start + s.m_len; 
		const char* const sc = s.m_string.get(); 
		for(size_t i=s.m_start; i < end; i++) 
			os << sc[i]; 
		return os; 
	}

	// Klassen-Methode 
	static String valueOf(int i); // erzeugt eine String-Repräsentation von i
};
#endif
#include "MyString.h" 
#include <memory>

String::String() : m_len(0), m_start(0){}

String::String(const String & p_string) {
	m_len=p_string.m_len;
	m_start=p_string.m_start;
	m_string=p_string.m_string;
}

String::String(const char* p_string) : m_len(0), m_start(0) {
	while (p_string[m_len]!='\0') m_len++;
	
	m_string = std::shared_ptr<char>(std::unique_ptr<char[]>(new char[m_len]));

	memcpy(m_string.get(),p_string,m_len);
}

char String::charAt(size_t index) const {
	if (index >= m_len) throw "Index out of bounds!";
	return m_string.get()[m_start+index];
}

int String::compareTo(const String& s) const {
	int i=0;
	while(i<m_len && i<s.m_len) {
		if(m_string.get()[m_start+i] < s.m_string.get()[s.m_start+i]) return -1;
		else if (m_string.get()[m_start+i] > s.m_string.get()[s.m_start+i]) return 1;
		i++;
	}

	if(m_len < s.m_len) return -1;
	else if(m_len > s.m_len) return 1;
	else return 0;
}

String String::concat(char c) const {
	String ret;
	ret.m_len=m_len+1;
	ret.m_string = std::shared_ptr<char>(std::unique_ptr<char[]>(new char[ret.m_len]));
	memcpy(ret.m_string.get(),m_string.get()+m_start,m_len);
	ret.m_string.get()[m_len] = c;
	return ret;
}

String String::concat(const String& s) const {
	String ret;
	ret.m_len=m_len+s.m_len;
	ret.m_string = std::shared_ptr<char>(std::unique_ptr<char[]>(new char[ret.m_len]));
	memcpy(ret.m_string.get(),m_string.get()+m_start,m_len);
	memcpy(ret.m_string.get()+m_len,s.m_string.get()+s.m_start,s.m_len);
	return ret;
}

size_t String::length() const {return m_len;};

String String::substring(size_t beg, size_t end) const {
	if (end >= m_len || beg > end) throw "Index out of bounds!";
	String ret;
	ret.m_len = end-beg+1;
	ret.m_start = m_start+beg;
	ret.m_string = m_string;
	return ret;
}

std::unique_ptr<char[]> String::toCString() const { 
	std::unique_ptr<char[]> r = std::unique_ptr<char[]>(new char[m_len + 1]); 
	const char * const tc = m_string.get();  
	memcpy(r.get(), tc + m_start, m_len); r[m_len] = '\0';
    return move(r); 
}

String String::valueOf(int i) {
	char str[12];
	itoa(i,str,10);
	String ret(str);
	return ret;
}


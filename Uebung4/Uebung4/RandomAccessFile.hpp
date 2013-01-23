#include "RandomAccessFile.h"

// generic members
	template<class T> 
	T RandomAccessFile::read(streampos pos){
		if (pos >= 0) {
			m_file.seekg(pos, ios::beg);
		}
		if (m_file.good()) {
			char* s = new char[sizeof(T)];
			m_file.read(s, sizeof(T));
			return *reinterpret_cast<T*>(s);
		} else {
			throw new RandomAccessFile::IOException("Error reading file!");
		}
	};

	template<class T>
	void RandomAccessFile::write(const T& data, streampos pos) {
		if (pos >= 0) {
			m_file.seekg(pos, ios::beg);
		}

		m_file.write(reinterpret_cast<const char*>(&data), sizeof(T));

		if (m_file.good()) {
			m_file.flush();		
		} else {
			throw new RandomAccessFile::IOException("Error writing file!");
		}
	};
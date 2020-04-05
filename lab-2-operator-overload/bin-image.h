#pragma once
#include <stdio.h>
#include <iostream>
class Image {
		int _lines, _columns;
		bool** _pixel;
		mutable double _fillFactor = -1;
	public:
		Image(const int &lines, const int& columns) noexcept;

		Image(const Image& obj) noexcept;

		Image& operator=(const Image& rhs) noexcept;

		//Image(Image&& rhs) noexcept;
		//
		//Image& operator=(Image&& rhs) noexcept;

		~Image() noexcept;

		int getLines() const noexcept;

		int getColumns() const noexcept;

		Image& operator +=(const Image& rhs);

		Image& operator+=(const bool& term) noexcept;

		Image& operator*=(const Image& rhs);

		Image& operator*=(const bool& multiplier) noexcept;

		bool operator==(const Image& rhs) const noexcept;

		bool operator!=(const Image& rhs) const noexcept;

		const bool operator ()(const int& line, const int& column) const;

		void operator ()(const int& line, const int& column, const bool& newValue);

		Image operator!() noexcept;

		double getFillFactor() const noexcept;

};

std::ostream& operator<< (std::ostream& out, const Image& rhs) noexcept;

Image operator+(const Image& first, const Image& second);

Image operator+(const Image& rhs, const bool& term);

Image operator+(const bool& term, const Image& rhs);

Image operator*(const Image& first, const Image& second);

Image operator*(const Image& rhs, const bool& multiplier);

Image operator*(const bool& multiplier, const Image& rhs);
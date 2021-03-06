#pragma once

#include "tinyspline.h"
#include <vector>
#include <string>

namespace tinyspline {

typedef tsReal real;

class DeBoorNet {
public:
	/* Constructors & Destructors */
	DeBoorNet();
	DeBoorNet(const DeBoorNet &other);
	~DeBoorNet();

	/* Operators */
	DeBoorNet& operator=(const DeBoorNet &other);

	/* Getter */
	real u() const;
	size_t k() const;
	size_t s() const;
	size_t h() const;
	size_t dim() const;
	size_t nPoints() const;
	std::vector<real> points() const;
	std::vector<real> result() const;
	tsDeBoorNet * data();

	/* C++11 features */
#ifndef TINYSPLINE_DISABLE_CXX11_FEATURES
	DeBoorNet(DeBoorNet &&other) noexcept;
	DeBoorNet & operator=(DeBoorNet &&other) noexcept;
	void swap(DeBoorNet &other);
	friend void swap(DeBoorNet &left, DeBoorNet &right)
	{
		left.swap(right);
	}
#endif

private:
	tsDeBoorNet deBoorNet;
};

class BSpline {
public:
    typedef tsBSplineType type;

	/* Constructors & Destructors */
	BSpline();
	BSpline(const BSpline &other);
	explicit BSpline(size_t nCtrlp, size_t dim = 2, size_t deg = 3,
        tinyspline::BSpline::type type = TS_CLAMPED);
	~BSpline();

	/* Operators */
	BSpline & operator=(const BSpline &other);
	DeBoorNet operator()(real u) const;

	/* Getter */
	size_t deg() const;
	size_t order() const;
	size_t dim() const;
	size_t nCtrlp() const;
	size_t nKnots() const;
	std::vector<real> ctrlp() const;
	std::vector<real> knots() const;
	tsBSpline * data();
	DeBoorNet evaluate(real u) const;

	/* Modifications */
	void setCtrlp(const std::vector<real> &ctrlp);
	void setKnots(const std::vector<real> &knots);

	/* Transformations */
	BSpline fillKnots(tsBSplineType type, real min, real max) const;
	BSpline insertKnot(real u, size_t n) const;
	BSpline resize(int n, int back) const;
	BSpline split(real u) const;
	BSpline buckle(real b) const;
	BSpline toBeziers() const;
	BSpline derive() const;

	/* C++11 features */
#ifndef TINYSPLINE_DISABLE_CXX11_FEATURES
	BSpline(BSpline &&other) noexcept;
	BSpline& operator=(BSpline &&other) noexcept;
	void swap(BSpline &other);
	friend void swap(BSpline &left, BSpline &right)
	{
		left.swap(right);
	}
#endif

private:
	tsBSpline bspline;
};

class Utils {
public:
	static BSpline interpolateCubic(
			const std::vector<real> *points, size_t dim);
	static bool fequals(real x, real y);
	static std::string enum_str(tsError err);
	static tsError str_enum(std::string str);

private:
	Utils() {}
};

}

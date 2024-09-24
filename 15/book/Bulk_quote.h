#ifndef BULK_Q_H
#define BULK_Q_H

#include "Disc_quote.h"
using std::string;
using std::cout;
class Bulk_quote : public Disc_quote 
{
private:
    size_t min_qty =0;//最低购买量
    double discount=0.0;//折扣力度

public:

    //
    Bulk_quote* clone() const & override{return new Bulk_quote (*this);}
    Bulk_quote* clone() const && override{return new Bulk_quote (move(*this));}
    //
    Bulk_quote()=default;
    using Disc_quote::Disc_quote;

	// copy constructor
	Bulk_quote(const Bulk_quote& bq) : Disc_quote(bq)
	{
		std::cout << "Bulk_quote : copy constructor\n";
	}

	// move constructor
	Bulk_quote(Bulk_quote&& bq) : Disc_quote(std::move(bq))
	{
		std::cout << "Bulk_quote : move constructor\n";
	}

	// copy =()
	Bulk_quote& operator =(const Bulk_quote& rhs)
	{
		Disc_quote::operator =(rhs);
		std::cout << "Bulk_quote : copy =()\n";

		return *this;
	}


	// move =()
	Bulk_quote& operator =(Bulk_quote&& rhs)
	{
		Disc_quote::operator =(std::move(rhs));
		std::cout << "Bulk_quote : move =()\n";

		return *this;
	}

    Bulk_quote(const string&book,double price,size_t n,double disc):Disc_quote::Disc_quote(book,price,n,disc){}
    double net_price(size_t n) const override{
        if(n>=min_qty) return n*(1-discount)*price;
        return n*price;
    }

    ~Bulk_quote() override
	{
		std::cout << "destructing Bulk_quote\n";
	}
};
#endif

